#ifndef wall_hpp
#define wall_hpp

#include "block.hpp"

class Wall : public Block {
public:
  /**
  * Requires: nothing
  * Modifies: nothing
  * Effects: Returns if the player can move on top of the block
  */
  virtual bool canMoveOnTop() const override;

  /**
  * Requires: nothing
  * Modifies: nothing
  * Effects: Returns the type of block
  */
  virtual BlockType getBlockType() const override;

private:
};

#endif