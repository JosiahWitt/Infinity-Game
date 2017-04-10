#include "floor_tests.hpp"

void floorTests_run() {
  cout << "Running Floor Tests:" << endl;
  cout << "--------------------" << endl;

  // Create a new testing object to keep track of the results of each test
  Testing t;

  // Run all tests
  t.check(floorTests_constants());

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
bool floorTests_constants() {
  // Start new testing object
  Testing t("canMoveOnTop() and getBlockType()");

  // Create an object and check its constants are correct
  Floor f;
  t.check(f.canMoveOnTop() == true, "Cannot move on top of floor");
  t.check(f.getBlockType() == FloorBlock, "Floor is not a FloorBlock");

  return t.getResult(); // Return pass or fail result
}