#ifndef testing_hpp
#define testing_hpp

#include <iostream>
#include <string>

using namespace std;

// Testing class to help test the Matrix class
class Testing {
public:
  /**
  * Requires: nothing
  * Modifies: nothing
  * Effects: Sets default values, enables quiet mode
  */
  Testing();
  /**
  * Requires: string including functions we are testing
  * Modifies: nothing
  * Effects: Prints the header and sets default values
  */
  Testing(string newFuncName);
  /**
  * Requires: nothing
  * Modifies: nothing
  * Effects: Prints the footer
  */
  ~Testing();

  /**
  * Requires: boolean test and failure message
  * Modifies: nothing
  * Effects: Checks if test is true, if not prints failed message
  */
  void assert(bool test, string message);

  /**
  * Requires: boolean test
  * Modifies: nothing
  * Effects: Checks if test is true
  */
  void assert(bool test);

  /**
  * Requires: nothing
  * Modifies: nothing
  * Effects: Returns if test passed or failed
  */
  bool getResult();

  /**
  * Requires: nothing
  * Modifies: nothing
  * Effects: Returns number of failed cases
  */
  int getNumFailed();

  /**
  * Requires: nothing
  * Modifies: nothing
  * Effects: Returns number of tested cases
  */
  int getNumTested();

private:
  // Store if all the tests passed
  bool passed;
  // Store the function name
  string funcName;
  // Store if in quiet mode
  bool quiet;
  // Number of failed cases
  int numFailed;
  // Number of tested cases
  int numTested;
};

#endif // testing_hpp