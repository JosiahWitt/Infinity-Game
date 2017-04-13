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

  // Initialize the seed to 0
  seed = 0;
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
void GameBoard::saveGame(string filename) {
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

    // Add the player
    gameJson["player"] = player.toJson();

    // Add the changes
    for (map<int, map<int, unique_ptr<Block>>>::iterator i = changes.begin();
         i != changes.end(); i++) {
      for (map<int, unique_ptr<Block>>::iterator j = (i->second).begin();
           j != (i->second).end(); j++) {
        json object = (j->second)->toJson();
        object["row"] = i->first;
        object["column"] = j->first;
        gameJson["changes"].push_back(object);
      }
    }

    // Save to the file in pretty print
    gameFile << setw(4) << gameJson << endl;
  }

  // Close file
  gameFile.close();
}

/**
* Requires: a valid path to an existing game file
* Modifies: all GameBoard fields
* Effects: loads the game from a file
*/
void GameBoard::loadGame(string filename) {
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
    }

    // Load game seed
    try {
      seed = gameJson.at("seed").get<int>();
    } catch (exception e) {
      cout << "Syntax invalid for save file... Error loading seed..." << endl;
    }

    // Create random object using the seed
    rand.seed(seed);

    // Load player
    try {
      player.fromJson(gameJson.at("player"));
    } catch (exception e) {
      cout << "Syntax invalid for save file... Error loading player..." << endl;
    }

    // TODO: Generate board

    // Load changed blocks
    try {
      for (json::iterator change = gameJson["changes"].begin();
           change != gameJson["changes"].end(); change++) {
        switch (change->at("type").get<int>()) {
        case WallBlock:
          changes[change->at("row").get<int>()]
                 [change->at("column").get<int>()] = make_unique<Wall>();
          break;
        case FloorBlock:
          changes[change->at("row").get<int>()]
                 [change->at("column").get<int>()] = make_unique<Floor>();
          break;
        }
        changes[change->at("row").get<int>()][change->at("column").get<int>()]
            ->fromJson(*change);

        // TODO: Import changes on to board
      }
    } catch (exception e) {
      cout << "Syntax invalid for save file... Error loading changed blocks..."
           << endl;
    }
  } else {
    cout << "Couldn't find file... game not loaded..." << endl;
  }

  // Close file
  gameFile.close();
}
