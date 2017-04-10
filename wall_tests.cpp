#include "wall_tests.hpp"

void wallTests_run() {
  cout << "Running Wall Tests:" << endl;
  cout << "-------------------" << endl;

  // Create a new testing object to keep track of the results of each test
  Testing t;

  // Run all tests
  t.check(wallTests_constants());

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

// Test canMoveOnTop() and getBlockType()
bool wallTests_constants() {
  // Start new testing object
  Testing t("canMoveOnTop() and getBlockType()");

  // Create an object and check its constants are correct
  Wall w;
  t.check(w.canMoveOnTop() == false, "Can move on top of wall");
  t.check(w.getBlockType() == WallBlock, "Wall is not a WallBlock");

  return t.getResult(); // Return pass or fail result
}