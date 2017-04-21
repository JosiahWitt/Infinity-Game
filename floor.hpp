#ifndef floor_hpp
#define floor_hpp

#include "block.hpp"

enum TypeOfFloor { GrassFloor, SandFloor, DirtFloor };
class Floor : public Block {
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

  /**
   * Requires: nothing
   * Modifies: nothing
   * Effects: gets type of floor
   */
  TypeOfFloor getTypeOfFloor() const;
  /**
   * Requires: nothing
   * Modifies: nothing
   * Effects: changes type of floor
   */
  void setTypeOfFloor(TypeOfFloor f);

private:
  TypeOfFloor floorType = GrassFloor;
};

#endif
