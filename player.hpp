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
    
    Color getAlternateColor();
    void setAlternateColor(Color c);
    void swapColor();

	void setX(int x);

	void setY(int y);
	

	/**
	* Requires: nothing
	* Modifies: nothing
	* Effects: returns the players x and y coordinates
	*/

	int getX() const;
	int getY() const;

private:
    Color alternateColor;
	int vectorx = 0;
	int vectory = 0;
};

#endif
