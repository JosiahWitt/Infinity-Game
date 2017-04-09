#include "wall.hpp"

/**
* Requires: nothing
* Modifies: nothing
* Effects: Returns if the player can move on top of the block
*/
bool Wall::canMoveOnTop() const { return false; }

/**
* Requires: nothing
* Modifies: nothing
* Effects: Returns the type of block
*/
BlockType Wall::getBlockType() const { return WallBlock; }