#ifndef gameboard_hpp
#define gameboard_hpp

#include "block.hpp"
#include "floor.hpp"
#include "player.hpp"
#include "wall.hpp"
#include <map>
#include <memory>
#include <random>
#include <vector>

enum GameDirection { DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT };

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
  * Requires: same as previous constructor, plus seed, percentWall, and changes
  * Modifies: numBlocksWide, numBlocksHigh, blockWidth, blockHeight, seed,
  * percentWall, and changes map
  * Effects: Creates a new gameboard - used primarly for testing purposes
  */
  GameBoard(int nBlocksWide, int nBlocksHigh, int blockW, int blockH, int s,
            double pWall = -1, map<int, map<int, shared_ptr<Block>>> c = {});

  /**
  * Requires: nothing
  * Modifies: nothing
  * Effects: Returns the respective field
  */
  int getNumBlocksWide() const;
  int getNumBlocksHigh() const;
  int getBlockWidth() const;
  int getBlockHeight() const;
  // These getters are used for testing purposes
  int getSeed() const;
  int getPercentWall() const;
  Player getPlayer() const;
  vector<vector<shared_ptr<Block>>> getBoard() const;
  map<int, map<int, shared_ptr<Block>>> getChanges() const;

  /**
  * Requires: nothing
  * Modifies: nothing
  * Effects: Computes and returns the total pixel width or hight
  */
  int getGamePixelWidth() const;
  int getGamePixelHight() const;

  /**
  * Requires: a valid path to save the file to
  * Modifies: nothing
  * Effects: saves the game to a file, returns save status
  */
  bool saveGame(string filename = "");

  /**
  * Requires: a valid path to an existing game file
  * Modifies: all GameBoard fields
  * Effects: loads the game from a file, returns load status
  */
  bool loadGame(string filename = "");

  /**
  * Requires: a GameDirection
  * Modifies: player
  * Effects: moves the player in the direction specified
  */
  void movePlayer(GameDirection direction);

  /**
  * Requires: nothing
  * Modifies: nothing
  * Effects: Displays the board to the console
  */
  void display() const;

private:
  // Number of blocks to render for the height and for the width -- set at
  // object construction
  int numBlocksWide;
  int numBlocksHigh;
  // The width and height of each block -- set at object construction
  int blockWidth;
  int blockHeight;

  // Store the seed used to generate the board
  int seed;

  // Store the random object
  mt19937 rand;

  // Store the percent (in decimal) for the amount of random wall
  double percentWall;

  // Store the 2D vector of pointers to the blocks on the board
  vector<vector<shared_ptr<Block>>> board;

  // Store a map of changes to the default blocks
  //  Note: changes[column][row] maps to the element at board[column][row]
  map<int, map<int, shared_ptr<Block>>> changes;

  // Store the player object
  Player player;

  /**
  * Requires: nothing
  * Modifies: board
  * Effects: generates the board based on the seed
  */
  void generateBoard();
};

#endif