#ifndef block_tests_hpp
#define block_tests_hpp

#include "block.hpp"
#include "testing.hpp"

/**
* Requires: nothing
* Modifies: nothing
* Effects: Runs all tests
*/
bool blockTests_run();

/**
* Requires: nothing
* Modifies: nothing
* Effects: Tests constructors
*/
bool blockTests_constructors();

/**
* Requires: nothing
* Modifies: nothing
* Effects: Tests setColor
*/
bool blockTests_setColor();

/**
* Requires: nothing
* Modifies: nothing
* Effects: Tests toJson and fromJson
*/
bool blockTests_toJsonAndFromJson();

#endif