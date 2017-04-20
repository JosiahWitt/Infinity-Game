#ifndef player_tests_hpp
#define player_tests_hpp

#include "player.hpp"
#include "testing.hpp"

/**
* Requires: nothing
* Modifies: nothing
* Effects: Runs all tests
*/
void playerTests_run();

/**
* Requires: nothing
* Modifies: nothing
* Effects: Tests canMoveOnTop() and getBlockType()
*/
bool playerTests_constants();

/**
 * Requires: nothing
 * Modifies: nothing
 * Effects: Tests getAlternateColor(), setAlternateColor(Color c), and swapColor()
 */
bool playerTests_colors();

/**
* Requires: nothing
* Modifies: nothing
* Effects: Tests setX(), setY(), getX(), getY()
*/
bool playerTests_coordinates();
#endif
