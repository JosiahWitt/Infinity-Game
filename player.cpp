#include "player.hpp"

/**
* Requires: nothing
* Modifies: nothing
* Effects: Returns if the player can move on top of the block
*/
bool Player::canMoveOnTop() const { return false; }

/**
* Requires: nothing
* Modifies: nothing
* Effects: Returns the type of block
*/
BlockType Player::getBlockType() const { return PlayerBlock; }