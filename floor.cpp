#include "floor.hpp"

/**
* Requires: nothing
* Modifies: nothing
* Effects: Returns if the player can move on top of the block
*/
bool Floor::canMoveOnTop() const { return true; }

/**
* Requires: nothing
* Modifies: nothing
* Effects: Returns the type of block
*/
BlockType Floor::getBlockType() const { return FloorBlock; }