#include "floor_tests.hpp"

void floorTests_run() {
  cout << "Running Floor Tests:" << endl;
  cout << "--------------------" << endl;

  // Create a new testing object to keep track of the results of each test
  Testing t;

  // Run all tests
  //   t.assert(floorTests_constructors());

  // Display pass or fail result
  if (t.getResult()) {
    cout << "Done testing. All " << t.getNumTested() << " tests passed!"
         << endl;
  } else {
    cout << "Failed " << t.getNumFailed() << "/" << t.getNumTested()
         << " test(s). See message(s) above." << endl;
  }
}

// *** Tests ***

// Test constructors
bool floorTests_constructors() {
  // Start new testing object
  Testing t("constructors");

  // Create an object and assert its default constructor worked
  // t.assert(boolean statement, "Helpful debugging string");

  return t.getResult(); // Return pass or fail result
}