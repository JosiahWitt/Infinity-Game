#ifndef block_hpp
#define block_hpp

#include "lib/json.hpp"
#include <string>

using namespace std;
using namespace nlohmann;

// RGB color values for each block
struct Color {
  double r, g, b;

  // Convert the color to json
  json toJson() const { 
	  return {{"r", r}, {"g", g}, {"b", b}}; }
};

// Type of the block
enum BlockType { PlayerBlock = 1, FloorBlock = 2, WallBlock = 3 };

class Block {
public:
  /**
  * Requires: nothing
  * Modifies: color
  * Effects: Creates a new block
  */
  Block();
  /**
  * Requires: a valid color
  * Modifies: color
  * Effects: Creates a new block with a color
  */
  Block(Color c);

  /**
  * Requires: nothing
  * Modifies: nothing
  * Effects: Returns the color
  */
  Color getColor() const;
  /**
  * Requires: a valid color
  * Modifies: color
  * Effects: Sets the color
  */
  void setColor(Color c);

  /**
  * Requires: the pixel x and y coordinates to draw the left corner at and the
  * width and height of the block
  * Modifies: nothing
  * Effects: Draws the block to the screen at the specified location
  */
  void draw(int pixelX, int pixelY, int width, int height) const;

  /**
  * Requires: nothing
  * Modifies: nothing
  * Effects: Returns if the player can move on top of the block
  */
  virtual bool canMoveOnTop() const = 0;

  /**
  * Requires: nothing
  * Modifies: nothing
  * Effects: Returns the type of block
  */
  virtual BlockType getBlockType() const = 0;

  /**
  * Requires: nothing
  * Modifies: nothing
  * Effects: Convert the block to json
  */
  virtual json toJson() const;

  /**
  * Requires: nothing
  * Modifies: nothing
  * Effects: Convert json to the block
  */
  virtual void fromJson(json j);

protected:
  // The color of the block
  Color color;
};

#endif