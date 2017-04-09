#include "player_tests.hpp"

void playerTests_run() {
  cout << "Running Player Tests:" << endl;
  cout << "---------------------" << endl;

  // Create a new testing object to keep track of the results of each test
  Testing t;

  // Run all tests
  t.assert(playerTests_constants());

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
bool playerTests_constants() {
  // Start new testing object
  Testing t("canMoveOnTop() and getBlockType()");

  // Create an object and assert its constants are correct
  Player p;
  t.assert(p.canMoveOnTop() == false, "Can move on top of player");
  t.assert(p.getBlockType() == PlayerBlock, "Player is not a PlayerBlock");

  return t.getResult(); // Return pass or fail result
}