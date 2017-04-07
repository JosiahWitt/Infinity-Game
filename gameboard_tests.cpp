#include "gameboard_tests.hpp"

void gameboardTests_run() {
  cout << "Running Gameboard Tests:" << endl;
  cout << "------------------------" << endl;

  // Create a new testing object to keep track of the results of each test
  Testing t;

  // Run all tests
  t.assert(gameboardTests_constructors());
  t.assert(gameboardTests_getGamePixelWidthAndHeight());

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
bool gameboardTests_constructors() {
  // Start new testing object
  Testing t("constructors");

  // Create an object and assert its default constructor worked
  GameBoard g1;
  t.assert(g1.getNumBlocksWide() == 16 && g1.getNumBlocksHigh() == 12 &&
               g1.getBlockWidth() == 50 && g1.getBlockHeight() == 50,
           "Default constructor didn't work correctly");

  // Create an object and assert its values were set correctly
  GameBoard g2(20, -1, 40, 2);
  t.assert(g2.getNumBlocksWide() == 20 && g2.getNumBlocksHigh() == 12 &&
               g2.getBlockWidth() == 40 && g2.getBlockHeight() == 2,
           "Constructor with a negative value didn't work correctly");

  // Create an object and assert its values were set correctly
  GameBoard g3(21, 23, 49, 24);
  t.assert(g3.getNumBlocksWide() == 21 && g3.getNumBlocksHigh() == 23 &&
               g3.getBlockWidth() == 49 && g3.getBlockHeight() == 24,
           "Constructor with accepted values didn't work correctly");

  return t.getResult(); // Return pass or fail result
}

// Test getGamePixelWidth() and getGamePixelHight()
bool gameboardTests_getGamePixelWidthAndHeight() {
  // Start new testing object
  Testing t("getGamePixelWidth() and getGamePixelHight()");

  // Create an object and assert the
  GameBoard g1;
  t.assert(g1.getGamePixelWidth() == 800 && g1.getGamePixelHight() == 600,
           "Default constructor with getGamePixelWidth() and "
           "getGamePixelHight() didn't work correctly");

  // Create an object and assert its values were set correctly
  GameBoard g2(21, 23, 49, 24);
  t.assert(g2.getGamePixelWidth() == 1029 && g2.getGamePixelHight() == 552,
           "Constructor with accepted values and getGamePixelWidth() and "
           "getGamePixelHight() didn't work correctly");

  return t.getResult(); // Return pass or fail result
}