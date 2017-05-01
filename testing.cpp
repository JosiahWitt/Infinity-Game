#include "testing.hpp"

/**
* Requires: nothing
* Modifies: nothing
* Effects: Sets default values, enables quiet mode
*/
Testing::Testing() {
  passed = true;
  quiet = true;
  funcName = "";
  numFailed = 0;
  numTested = 0;
}

/**
* Requires: string including functions we are testing
* Modifies: nothing
* Effects: Prints the header and sets default values
*/
Testing::Testing(string newFuncName) : Testing() {
  // Turn off quiet mode and set the function name
  quiet = false;
  funcName = newFuncName;

  cout << "* Testing " << funcName << endl;
}

/**
* Requires: nothing
* Modifies: nothing
* Effects: Prints the footer
*/
Testing::~Testing() {
  // Print passed or failed message if not in quiet mode
  if (!quiet) {
    if (passed) {
      cout << "  Passed " << numTested << " test cases!" << endl;
    } else {
      cout << "  Failed " << numFailed << "/" << numTested << " test case(s). See message(s) above." << endl;
    }
    cout << endl;
  }
}

/**
* Requires: boolean test and failure message
* Modifies: nothing
* Effects: Checks if test is true, if not prints failed message
*/
void Testing::check(bool test, string message) {
  check(test);
  if (!test) {
    cout << "   * Test Case Failed: " << message << endl;
  }
}

/**
* Requires: boolean test
* Modifies: nothing
* Effects: Checks if test is true
*/
void Testing::check(bool test) {
  // Check if the test passed
  numTested++;
  if (!test) {
    passed = false;
    numFailed++;
  }
}

/**
* Requires: nothing
* Modifies: nothing
* Effects: Returns if test passed or failed
*/
bool Testing::getResult() {
  return passed;
}

/**
* Requires: nothing
* Modifies: nothing
* Effects: Returns number of failed cases
*/
int Testing::getNumFailed() {
  return numFailed;
}

/**
* Requires: nothing
* Modifies: nothing
* Effects: Returns number of tested cases
*/
int Testing::getNumTested() {
  return numTested;
}