#ifndef gameboard_hpp
#define gameboard_hpp

#include "block.hpp"

class GameBoard {
public:
  /**
  * Requires: nothing
  * Modifies: numBlocksWide, numBlocksHigh, blockWidth, and blockHeight
  * Effects: Creates a new gameboard
  */
  GameBoard();
  /**
  * Requires: number of blocks wide and high, and block width and height to be
  * positive
  * Modifies: numBlocksWide, numBlocksHigh, blockWidth, and blockHeight
  * Effects: Creates a new gameboard
  */
  GameBoard(int nBlocksWide, int nBlocksHigh, int blockW, int blockH);

  /**
  * Requires: nothing
  * Modifies: nothing
  * Effects: Returns the respective field
  */
  int getNumBlocksWide() const;
  int getNumBlocksHigh() const;
  int getBlockWidth() const;
  int getBlockHeight() const;

  /**
  * Requires: nothing
  * Modifies: nothing
  * Effects: Computes and returns the total pixel width or hight
  */
  int getGamePixelWidth() const;
  int getGamePixelHight() const;

private:
  // Number of blocks to render for the height and for the width -- set at
  // object construction
  int numBlocksWide;
  int numBlocksHigh;
  // The width and height of each block -- set at object construction
  int blockWidth;
  int blockHeight;
};

#endif