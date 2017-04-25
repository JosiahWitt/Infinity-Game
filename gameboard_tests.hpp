#ifndef gameboard_tests_hpp
#define gameboard_tests_hpp

#include "gameboard.hpp"
#include "testing.hpp"

/**
* Requires: nothing
* Modifies: nothing
* Effects: Runs all tests
*/
bool gameboardTests_run();

/**
* Requires: nothing
* Modifies: nothing
* Effects: Tests constructors
*/
bool gameboardTests_constructors();

/**
* Requires: nothing
* Modifies: nothing
* Effects: Test getGamePixelWidth() and getGamePixelHeight()
*/
bool gameboardTests_getGamePixelWidthAndHeight();

/**
* Requires: nothing
* Modifies: nothing
* Effects: Test convertVectorXToPixelX(), convertVectorYToPixelY(),
* convertPixelXToVectorX(), and convertPixelYToVectorY()
*/
bool gameboardTests_convertCoordinates();

/**
* Requires: nothing
* Modifies: nothing
* Effects: Test saveGame() and loadGame()
*/
bool gameboardTests_saveAndLoad();

/**
* Requires: nothing
* Modifies: nothing
* Effects: Test generateBoard()
*/
bool gameboardTests_generateBoard();

/**
* Requires: nothing
* Modifies: nothing
* Effects: Test movePlayer()
*/
bool gameboardTests_movePlayer();

/**
* Requires: nothing
* Modifies: nothing
* Effects: Test moveWall()
*/
bool gameboardTests_moveWall();

#endif