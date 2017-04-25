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
    numBlocksWide = 30; // Default number of blocks wide
  } else {
    numBlocksWide = nBlocksWide;
  }

  // Set the number of blocks high
  if (nBlocksHigh <= 0) {
    numBlocksHigh = 20; // Default number of blocks high
  } else {
    numBlocksHigh = nBlocksHigh;
  }

  // Set the block width
  if (blockW <= 0) {
    blockWidth = 35; // Default block width
  } else {
    blockWidth = blockW;
  }

  // Set the block height
  if (blockH <= 0) {
    blockHeight = 35; // Default block height
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

  // Set the player's color and alternate color to blue
  player.setColor({66 / 255.0, 134 / 255.0, 244 / 255.0});
  player.setAlternateColor({41 / 255.0, 87 / 255.0, 160 / 255.0});

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
int GameBoard::getGamePixelHeight() const {
  return blockHeight * numBlocksHigh;
}

/**
* Requires: positive vectorX, vectorY, pixelX, or pixelY
* Modifies: nothing
* Effects: Converts the vector coordinate to pixel coordinates or vice versa
*/
int GameBoard::convertVectorXToPixelX(int vectorX) const {
  // Allow only positive coordinates
  if (vectorX < 0) {
    return 0;
  }

  // Calculate the pixelX position
  return vectorX * blockWidth;
}
int GameBoard::convertVectorYToPixelY(int vectorY) const {
  // Allow only positive coordinates
  if (vectorY < 0) {
    return 0;
  }

  // Calculate the pixelY position
  return vectorY * blockHeight;
}
int GameBoard::convertPixelXToVectorX(int pixelX) const {
  // Allow only positive coordinates
  if (pixelX < 0) {
    return 0;
  }

  // Calculate the pixelX position
  return pixelX / blockWidth;
}
int GameBoard::convertPixelYToVectorY(int pixelY) const {
  // Allow only positive coordinates
  if (pixelY < 0) {
    return 0;
  }

  // Calculate the pixelY position
  return pixelY / blockHeight;
}

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

    // Add game version
    gameJson["gameVersion"] = GAME_VERSION;

    // Add time saved
    gameJson["saveTime"] = time(nullptr);

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
* Requires: positive lastX, lastY, currentX, and currentY
* Modifies: board and changes
* Effects: Moves the wall located at the last coordinates to the current
* coordinates, boolean return value signifies if we moved
*/
bool GameBoard::moveWall(int lastX, int lastY, int currentX, int currentY) {
  // Convert to vector coordinates (will make them positive)
  int lastVectorX = convertPixelXToVectorX(lastX);
  int lastVectorY = convertPixelYToVectorY(lastY);
  int currentVectorX = convertPixelXToVectorX(currentX);
  int currentVectorY = convertPixelYToVectorY(currentY);

  // Make sure all the coordinates are within the board
  if (lastVectorX >= board.size() || lastVectorY >= getNumBlocksHigh() ||
      currentVectorX >= board.size() || currentVectorY >= getNumBlocksHigh()) {
    return false;
  }

  // Make sure we aren't moving to the same vector location
  if (lastVectorX == currentVectorX && lastVectorY == currentVectorY) {
    return false;
  }

  // Make sure the old location is a wall
  if (board[lastVectorX][lastVectorY]->getBlockType() != WallBlock) {
    return false;
  }

  // Make sure we can move on top of the new location
  if (!board[currentVectorX][currentVectorY]->canMoveOnTop()) {
    return false;
  }

  // Make sure the player isn't at the current location
  if (player.getVectorX() == currentVectorX &&
      player.getVectorY() == currentVectorY) {
    return false;
  }

  // Create the floor to replace the wall
  shared_ptr<Block> floor = make_shared<Floor>();

  // Grab the pointer to the wall
  shared_ptr<Block> wall = board[lastVectorX][lastVectorY];

  // Save the changes
  changes[lastVectorX][lastVectorY] = floor;
  changes[currentVectorX][currentVectorY] = wall;

  // Update the board
  board[lastVectorX][lastVectorY] = floor;
  board[currentVectorX][currentVectorY] = wall;

  return true;
}

/**
* Requires: nothing
* Modifies: nothing
* Effects: Displays the board to the screen
*/
void GameBoard::display() const {
  // Loop through the board to print it out
  for (int row = 0; row < numBlocksHigh; row++) {
    for (int column = 0; column < numBlocksWide; column++) {
      // Draw the block
      board[column][row]->draw(convertVectorXToPixelX(column),
                               convertVectorYToPixelY(row), getBlockWidth(),
                               getBlockHeight());
    }
  }

  // Draw the player
  player.draw(convertVectorXToPixelX(player.getVectorX()),
              convertVectorYToPixelY(player.getVectorY()), getBlockWidth(),
              getBlockHeight());
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