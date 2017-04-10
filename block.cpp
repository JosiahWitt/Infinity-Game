#include "block.hpp"

/**
* Requires: nothing
* Modifies: color
* Effects: Creates a new block
*/
Block::Block() : Block({0, 0, 0}) {}
/**
* Requires: a valid color
* Modifies: color
* Effects: Creates a new block with a color
*/
Block::Block(Color c) { setColor(c); }

/**
* Requires: nothing
* Modifies: nothing
* Effects: Returns the color
*/
Color Block::getColor() const { return color; }
/**
* Requires: a valid color
* Modifies: color
* Effects: Sets the color
*/
void Block::setColor(Color c) {
  // Truncate each value to be between 0 and 1
  color.r = max(0.0, min(c.r, 1.0));
  color.g = max(0.0, min(c.g, 1.0));
  color.b = max(0.0, min(c.b, 1.0));
}

/**
* Requires: the pixel x and y coordinates to draw the left corner at and the
* width and height of the block
* Modifies: nothing
* Effects: Draws the block to the screen at the specified location
*/
void Block::draw(int pixelX, int pixelY, int width, int height) const {
  // TODO: Implement drawing
}

/**
* Requires: nothing
* Modifies: nothing
* Effects: Convert the block to json
*/
json Block::toJson() const {
  return {{"color", color.toJson()}, {"type", getBlockType()}};
}

/**
* Requires: nothing
* Modifies: nothing
* Effects: Convert json to the block
*/
void Block::fromJson(json j) {
  // Import the color
  setColor({j.at("color").at("r").get<double>(),
            j.at("color").at("g").get<double>(),
            j.at("color").at("b").get<double>()});
}