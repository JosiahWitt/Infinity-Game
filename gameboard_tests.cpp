#include "gameboard_tests.hpp"

bool gameboardTests_run() {
  cout << "Running Gameboard Tests:" << endl;
  cout << "------------------------" << endl;

  // Create a new testing object to keep track of the results of each test
  Testing t;

  // Run all tests
  t.check(gameboardTests_constructors());
  t.check(gameboardTests_getGamePixelWidthAndHeight());
  t.check(gameboardTests_saveAndLoad());
  t.check(gameboardTests_generateBoard());

  // Display pass or fail result
  if (t.getResult()) {
    cout << "Done testing. All " << t.getNumTested() << " tests passed!"
         << endl;
  } else {
    cout << "Failed " << t.getNumFailed() << "/" << t.getNumTested()
         << " test(s). See message(s) above." << endl;
  }

  return t.getResult();
}

// *** Tests ***

// Test constructors
bool gameboardTests_constructors() {
  // Start new testing object
  Testing t("constructors");

  // Create an object and check its default constructor worked
  GameBoard g1;
  t.check(g1.getNumBlocksWide() == 16 && g1.getNumBlocksHigh() == 12 &&
              g1.getBlockWidth() == 50 && g1.getBlockHeight() == 50,
          "Default constructor didn't work correctly");

  // Create an object and check its values were set correctly
  GameBoard g2(20, -1, 40, 2);
  t.check(g2.getNumBlocksWide() == 20 && g2.getNumBlocksHigh() == 12 &&
              g2.getBlockWidth() == 40 && g2.getBlockHeight() == 2,
          "Constructor with a negative value didn't work correctly");

  // Create an object and check its values were set correctly
  GameBoard g3(21, 23, 49, 24);
  t.check(g3.getNumBlocksWide() == 21 && g3.getNumBlocksHigh() == 23 &&
              g3.getBlockWidth() == 49 && g3.getBlockHeight() == 24,
          "Constructor with accepted values didn't work correctly");

  return t.getResult(); // Return pass or fail result
}

// Test getGamePixelWidth() and getGamePixelHight()
bool gameboardTests_getGamePixelWidthAndHeight() {
  // Start new testing object
  Testing t("getGamePixelWidth() and getGamePixelHight()");

  // Create an object and check the
  GameBoard g1;
  t.check(g1.getGamePixelWidth() == 800 && g1.getGamePixelHight() == 600,
          "Default constructor with getGamePixelWidth() and "
          "getGamePixelHight() didn't work correctly");

  // Create an object and check its values were set correctly
  GameBoard g2(21, 23, 49, 24);
  t.check(g2.getGamePixelWidth() == 1029 && g2.getGamePixelHight() == 552,
          "Constructor with accepted values and getGamePixelWidth() and "
          "getGamePixelHight() didn't work correctly");

  return t.getResult(); // Return pass or fail result
}

// Test saveGame() and loadGame()
bool gameboardTests_saveAndLoad() {
  // Start new testing object
  Testing t("saveGame() and loadGame()");

  // Create an object and save it
  GameBoard g1(1, 2, 3, 4);
  g1.saveGame("testing.infinity.json");

  // Create a new object and load it
  GameBoard g2;
  g2.loadGame("testing.infinity.json");

  // Make sure the values were loaded correctly
  t.check(g1.getBlockHeight() == g2.getBlockHeight() &&
              g1.getBlockWidth() == g2.getBlockWidth() &&
              g1.getNumBlocksHigh() == g2.getNumBlocksHigh() &&
              g1.getNumBlocksWide() == g2.getNumBlocksWide() &&
              g1.getSeed() == g2.getSeed(),
          "saveGame() and loadGame() doesn't work with only blockHeight/Width, "
          "and numBlocksHigh/Wide");

  // Create a map of changes
  map<int, map<int, shared_ptr<Block>>> testChanges;
  testChanges[1][1] = make_shared<Wall>();
  testChanges[1][2] = make_shared<Floor>();
  testChanges[3][6] = make_shared<Floor>();

  // Create an game with custom percentWall, seed, and changes, and save it
  GameBoard g3(2, 3, 4, 5, 42, 0.3, testChanges);
  g3.saveGame("testing.infinity.json");

  // Create a new object and load it
  GameBoard g4;
  g4.loadGame("testing.infinity.json");

  // Make sure the values were loaded correctly
  t.check(g3.getBlockHeight() == g4.getBlockHeight() &&
              g3.getBlockWidth() == g4.getBlockWidth() &&
              g3.getNumBlocksHigh() == g4.getNumBlocksHigh() &&
              g3.getNumBlocksWide() == g4.getNumBlocksWide() &&
              g3.getSeed() == g4.getSeed() &&
              g3.getPercentWall() == g4.getPercentWall() &&
              g3.getChanges()[1][1]->getBlockType() == WallBlock &&
              g3.getChanges()[1][2]->getBlockType() == FloorBlock &&
              g3.getChanges()[3][6]->getBlockType() == FloorBlock,
          "saveGame() and loadGame() doesn't work for custom seed, "
          "percentWall, and changes");

  return t.getResult(); // Return pass or fail result
}

// Test generateBoard()
bool gameboardTests_generateBoard() {
  // Start new testing object
  Testing t("generateBoard()");

  // Create an object with a custom seed
  GameBoard g1(2, 3, 20, 20, 42, 0.3);

  // Assert the board is correctly created from that random seed
  t.check(g1.getBoard()[0][0]->getBlockType() == FloorBlock &&
              g1.getBoard()[0][1]->getBlockType() == WallBlock &&
              g1.getBoard()[0][2]->getBlockType() == FloorBlock &&
              g1.getBoard()[1][0]->getBlockType() == FloorBlock &&
              g1.getBoard()[1][1]->getBlockType() == FloorBlock &&
              g1.getBoard()[1][2]->getBlockType() == WallBlock,
          "generateBoard() with no changes, random seed of 42, and percent "
          "wall of 0.3 doesn't work");

  // Create a map of changes
  map<int, map<int, shared_ptr<Block>>> testChanges;
  testChanges[1][1] = make_shared<Wall>();
  testChanges[1][2] = make_shared<Floor>();

  // Create an object with a custom seed and changes
  GameBoard g2(2, 3, 20, 20, 42, 0.3, testChanges);

  // Assert the board is correctly created from that random seed
  t.check(g2.getBoard()[0][0]->getBlockType() == FloorBlock &&
              g2.getBoard()[0][1]->getBlockType() == WallBlock &&
              g2.getBoard()[0][2]->getBlockType() == FloorBlock &&
              g2.getBoard()[1][0]->getBlockType() == FloorBlock &&
              g2.getBoard()[1][1]->getBlockType() == WallBlock &&
              g2.getBoard()[1][2]->getBlockType() == FloorBlock,
          "generateBoard() with changes, random seed of 42, and percent "
          "wall of 0.3 doesn't work");

  return t.getResult(); // Return pass or fail result
}