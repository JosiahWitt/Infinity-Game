#include "gameboard.hpp"
#include <fstream>
#include <iostream>
#include <regex>
#include <typeinfo>

/**
* Requires: nothing
* Modifies: numBlocksWide, numBlocksHigh, blockWidth, and blockHeight
* Effects: Creates a new gameboard
*/
GameBoard::GameBoard() : GameBoard(0, 0, 0, 0) {}
/**
* Requires: number of blocks wide and high, and block width and height to be
* positive
* Modifies: numBlocksWide, numBlocksHigh, blockWidth, and blockHeight
* Effects: Creates a new gameboard
*/
GameBoard::GameBoard(int nBlocksWide, int nBlocksHigh, int blockW, int blockH) {
  // Set the number of blocks wide
  if (nBlocksWide <= 0) {
    numBlocksWide = 16; // Default number of blocks wide
  } else {
    numBlocksWide = nBlocksWide;
  }

  // Set the number of blocks high
  if (nBlocksHigh <= 0) {
    numBlocksHigh = 12; // Default number of blocks high
  } else {
    numBlocksHigh = nBlocksHigh;
  }

  // Set the block width
  if (blockW <= 0) {
    blockWidth = 50; // Default block width
  } else {
    blockWidth = blockW;
  }

  // Set the block height
  if (blockH <= 0) {
    blockHeight = 50; // Default block height
  } else {
    blockHeight = blockH;
  }

  // Initialize the seed to the current timestamp
  seed = time(nullptr);
  rand.seed(seed);

  // Initialize the percent wall
  percentWall = 0.3;

  // Default the player to (0,0)
  player.setVectorX(0);
  player.setVectorY(0);

  // Set the (0,0) position to a floor
  changes[0][0] = make_shared<Floor>();

  // Generate the board
  generateBoard();
}
/**
* Requires: same as previous constructor, plus seed, percentWall, and changes
* Modifies: numBlocksWide, numBlocksHigh, blockWidth, blockHeight, seed,
* percentWall, and changes map
* Effects: Creates a new gameboard (used primarly for testing purposes)
*/
GameBoard::GameBoard(int nBlocksWide, int nBlocksHigh, int blockW, int blockH,
                     int s, double pWall,
                     map<int, map<int, shared_ptr<Block>>> c)
    : GameBoard(nBlocksWide, nBlocksHigh, blockW, blockH) {
  // If the seed is set, use it
  if (s != 0) {
    seed = s;
    rand.seed(seed);
  }

  // If the wall is set, use it
  if (pWall != -1) {
    percentWall = max(0.0, min(pWall, 1.0));
  }

  // Set the changes if it is not empty
  if (!c.empty()) {
    changes = c;
  }

  // Regenerate the board (since this will only be used in testing, it's fine)
  generateBoard();
}

/**
* Requires: nothing
* Modifies: nothing
* Effects: Returns the respective field
*/
int GameBoard::getNumBlocksWide() const { return numBlocksWide; }
int GameBoard::getNumBlocksHigh() const { return numBlocksHigh; }
int GameBoard::getBlockWidth() const { return blockWidth; }
int GameBoard::getBlockHeight() const { return blockHeight; }
int GameBoard::getSeed() const { return seed; }
double GameBoard::getPercentWall() const { return percentWall; }
Player GameBoard::getPlayer() const { return player; }
vector<vector<shared_ptr<Block>>> GameBoard::getBoard() const { return board; }
map<int, map<int, shared_ptr<Block>>> GameBoard::getChanges() const {
  return changes;
}

/**
* Requires: nothing
* Modifies: nothing
* Effects: Computes and returns the total pixel width or hight
*/
int GameBoard::getGamePixelWidth() const { return blockWidth * numBlocksWide; }
int GameBoard::getGamePixelHight() const { return blockHeight * numBlocksHigh; }

/**
* Requires: a valid path to save the file to
* Modifies: nothing
* Effects: saves the game to a file
*/
bool GameBoard::saveGame(string filename) {
  // Keep track of save status
  bool isSaved = true;

  // If filename is empty, use default filename
  if (filename.empty()) {
    filename = "game.infinity.json";
  }

  // Open session file
  ofstream gameFile(filename);
  if (gameFile) {
    // Create new json object
    json gameJson;

    // Add the game dimensions
    gameJson["numBlocksWide"] = numBlocksWide;
    gameJson["numBlocksHigh"] = numBlocksHigh;
    gameJson["blockWidth"] = blockWidth;
    gameJson["blockHeight"] = blockHeight;

    // Add the seed
    gameJson["seed"] = seed;

    // Add the percentages
    gameJson["percentWall"] = percentWall;

    // Add the player
    gameJson["player"] = player.toJson();

    // Add the changes
    for (map<int, map<int, shared_ptr<Block>>>::iterator i = changes.begin();
         i != changes.end(); i++) {
      for (map<int, shared_ptr<Block>>::iterator j = (i->second).begin();
           j != (i->second).end(); j++) {
        json object = (j->second)->toJson();
        object["column"] = i->first;
        object["row"] = j->first;
        gameJson["changes"].push_back(object);
      }
    }

    // Save to the file in pretty print
    gameFile << setw(4) << gameJson << endl;
  } else {
    // Error opening file
    isSaved = false;
  }

  // Close file
  gameFile.close();

  // Return saved status
  return isSaved;
}

/**
* Requires: a valid path to an existing game file
* Modifies: all GameBoard fields
* Effects: loads the game from a file
*/
bool GameBoard::loadGame(string filename) {
  // Keep track of the game load status
  bool isLoaded = true;

  // If filename is empty, use default filename
  if (filename.empty()) {
    filename = "game.infinity.json";
  }

  // Open game file
  ifstream gameFile(filename);
  if (gameFile) {
    // Create new json object
    json gameJson;

    // Try converting file to json object
    try {
      gameFile >> gameJson;
    } catch (exception e) {
      cout << "Error converting file to json..." << endl;
      isLoaded = false;
    }

    // Load game dimensions
    try {
      numBlocksWide = gameJson.at("numBlocksWide").get<int>();
      numBlocksHigh = gameJson.at("numBlocksHigh").get<int>();
      blockWidth = gameJson.at("blockWidth").get<int>();
      blockHeight = gameJson.at("blockHeight").get<int>();
    } catch (exception e) {
      cout << "Syntax invalid for save file... Error loading game dimensions..."
           << endl;
      isLoaded = false;
    }

    // Load game seed
    try {
      seed = gameJson.at("seed").get<int>();
    } catch (exception e) {
      cout << "Syntax invalid for save file... Error loading seed..." << endl;
      isLoaded = false;
    }

    // Create random object using the seed
    rand.seed(seed);

    // Load board percentages
    try {
      percentWall = gameJson.at("percentWall").get<double>();
    } catch (exception e) {
      cout << "Syntax invalid for save file... Error loading percentages..."
           << endl;
      isLoaded = false;
    }

    // Load player
    try {
      player.fromJson(gameJson.at("player"));
    } catch (exception e) {
      cout << "Syntax invalid for save file... Error loading player..." << endl;
      isLoaded = false;
    }

    // Load changed blocks
    try {
      for (json::iterator change = gameJson["changes"].begin();
           change != gameJson["changes"].end(); change++) {
        // Create the type of block
        switch (change->at("type").get<int>()) {
        case WallBlock:
          changes[change->at("column").get<int>()]
                 [change->at("row").get<int>()] = make_shared<Wall>();
          break;
        case FloorBlock:
          changes[change->at("column").get<int>()]
                 [change->at("row").get<int>()] = make_shared<Floor>();
          break;
        }
        // Load the data into the block
        changes[change->at("column").get<int>()][change->at("row").get<int>()]
            ->fromJson(*change);
      }

      // Generate the board
      generateBoard();
    } catch (exception e) {
      cout << "Syntax invalid for save file... Error loading changed blocks..."
           << endl;
      isLoaded = false;
    }
  } else {
    // Couldn't find file
    isLoaded = false;
  }

  // Close file
  gameFile.close();

  // Return loaded result
  return isLoaded;
}

/**
* Requires: a GameDirection
* Modifies: player
* Effects: moves the player in the direction specified
*/
void GameBoard::movePlayer(GameDirection direction) {
  if (direction == DIR_LEFT && player.getVectorX() > 0 &&
      board[player.getVectorX() - 1][player.getVectorY()]->canMoveOnTop()) {
    // We can move to the left (no edge or wall blocking)
    player.setVectorX(player.getVectorX() - 1);
  } else if (direction == DIR_RIGHT &&
             player.getVectorX() < numBlocksWide - 1 &&
             board[player.getVectorX() + 1][player.getVectorY()]
                 ->canMoveOnTop()) {
    // We can move to the right (no edge or wall blocking)
    player.setVectorX(player.getVectorX() + 1);
  } else if (direction == DIR_UP && player.getVectorY() > 0 &&
             board[player.getVectorX()][player.getVectorY() - 1]
                 ->canMoveOnTop()) {
    // We can move up (no edge or wall blocking)
    player.setVectorY(player.getVectorY() - 1);
  } else if (direction == DIR_DOWN && player.getVectorY() < numBlocksHigh - 1 &&
             board[player.getVectorX()][player.getVectorY() + 1]
                 ->canMoveOnTop()) {
    // We can move down (no edge or wall blocking)
    player.setVectorY(player.getVectorY() + 1);
  }
}

/**
* Requires: nothing
* Modifies: nothing
* Effects: Displays the board to the console
*/
void GameBoard::display() const {
  // Loop through the board to print it out
  for (int row = 0; row < numBlocksHigh; row++) {
    for (int column = 0; column < numBlocksWide; column++) {
      if (board[column][row]->getBlockType() == WallBlock) {
        cout << "W "; // Wall is W
      } else if (board[column][row]->getBlockType() == FloorBlock) {
        cout << "F "; // Floor is F
      } else {
        cout << board[column][row]->getBlockType() << " ";
      }
    }
    cout << endl;
  }
}

/**
* Requires: nothing
* Modifies: board
* Effects: generates the board based on the seed
*/
void GameBoard::generateBoard() {
  // Generate a new distribution engine
  uniform_real_distribution<> dist;

  // Clear the current board
  board.clear();

  for (int column = 0; column < numBlocksWide; column++) {
    // Create a new column
    board.push_back(vector<shared_ptr<Block>>());
    for (int row = 0; row < numBlocksHigh; row++) {
      // If there is an existing block for here in the changes map, use it
      if (changes.find(column) != changes.end() &&
          changes[column].find(row) != changes[column].end()) {
        board[column].push_back(changes[column][row]); // Add to the board
        dist(rand); // Eat the random value for this location
      } else {
        // Randomly create a new block for the board
        if (dist(rand) <= percentWall) {
          board[column].push_back(make_shared<Wall>());
        } else {
          board[column].push_back(make_shared<Floor>());
        }
      }
    }
  }
}