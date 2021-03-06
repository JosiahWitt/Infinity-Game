#include "player.hpp"

/**
* Requires: nothing
* Modifies: nothing
* Effects: Returns if the player can move on top of the block
*/
bool Player::canMoveOnTop() const {
  return false;
}

/**
* Requires: nothing
* Modifies: nothing
* Effects: Returns the type of block
*/
BlockType Player::getBlockType() const {
  return PlayerBlock;
}

/**
 * Requires: nothing
 * Modifies: nothing
 * Effects: Returns the alternateColor of the Player
 */
Color Player::getAlternateColor() const {
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
 * Effects: swaps Color of the Player between alternate and block color
 */
void Player::swapColor() {
  Color temp = color;
  color = alternateColor;
  alternateColor = temp;
}

/**
* Requires: an x or y coordinate
* Modifies: vectorX or vectorY
* Effects: sets the vectorX or vectorY coordinate
*/
void Player::setVectorX(int x) {
  if (x < 0) {
    x = 0;
  }
  vectorX = x;
}
void Player::setVectorY(int y) {
  if (y < 0) {
    y = 0;
  }
  vectorY = y;
}

/**
* Requires: nothing
* Modifies: nothing
* Effects: returns the players vector x or y coordinate
*/
int Player::getVectorX() const {
  return vectorX;
}
int Player::getVectorY() const {
  return vectorY;
}

/**
* Requires: nothing
* Modifies: nothing
* Effects: Convert the player to json
*/
json Player::toJson() const {
  // Get the parent's json
  json obj = Block::toJson();

  // Add the alternate color
  obj["alternateColor"] = alternateColor.toJson();

  // Add the player's vector positions
  obj["vectorX"] = vectorX;
  obj["vectorY"] = vectorY;

  return obj;
}

/**
* Requires: json object
* Modifies: alternateColor and vectorX/Y
* Effects: Convert json to the player
*/
void Player::fromJson(json j) {
  // Import into the parent
  Block::fromJson(j);

  // Import the alternate color
  setAlternateColor({j.at("alternateColor").at("r").get<double>(), j.at("alternateColor").at("g").get<double>(), j.at("alternateColor").at("b").get<double>()});

  // Import the player's vector positions
  vectorX = j.at("vectorX").get<int>();
  vectorY = j.at("vectorY").get<int>();
}