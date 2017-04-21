#ifndef player_hpp
#define player_hpp

#include "block.hpp"

class Player : public Block {
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
  * Effects: returns the alternate color
  */
  Color getAlternateColor() const;

  /**
  * Requires: a color
  * Modifies: alternateColor
  * Effects: Sets the alternate color
  */
  void setAlternateColor(Color c);

  /**
   * Requires: nothing
   * Modifies: nothing
   * Effects: swaps Color of the Player between alternate and block color
   */
  void swapColor();

  /**
  * Requires: an x or y coordinate
  * Modifies: vectorX or vectorY
  * Effects: sets the vectorX or vectorY coordinate
  */
  void setVectorX(int x);
  void setVectorY(int y);

  /**
  * Requires: nothing
  * Modifies: nothing
  * Effects: returns the players vector x or y coordinate
  */
  int getVectorX() const;
  int getVectorY() const;

  /**
  * Requires: nothing
  * Modifies: nothing
  * Effects: Convert the player to json
  */
  virtual json toJson() const override;

  /**
* Requires: json object
* Modifies: alternateColor and vectorX/Y
  * Effects: Convert json to the player
  */
  virtual void fromJson(json j) override;

private:
  Color alternateColor = {0, 0, 0}; // Player color we can swap to
  int vectorX = 0;
  int vectorY = 0;
};

#endif
