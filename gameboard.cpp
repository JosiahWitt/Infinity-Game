#include "gameboard.hpp"

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