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

/**
 * Requires: nothing
 * Modifies: nothing
 * Effects: Returns the alternateColor of the Player
 */
Color Player::getAlternateColor() {
    return alternateColor;
}

/**
 * Requires: Color c
 * Modifies: the color of the Player
 * Effects: Sets the alternateColor of the Player
 */
void Player::setAlternateColor(Color c) {
    // Truncate each value to be between 0 and 1
    alternateColor.r = max(0.0, min(c.r, 1.0));
    alternateColor.g = max(0.0, min(c.g, 1.0));
    alternateColor.b = max(0.0, min(c.b, 1.0));
}

/**
 * Requires: nothing
 * Modifies: nothing
 * Effects: swaps Color of the Player
 */
void Player::swapColor() {
    Color temp = color;
    color = alternateColor;
    alternateColor = temp;
}
