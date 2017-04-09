#include "block_tests.hpp"

// Create the most basic child of Block, so we can test the abstract class
class BasicBlock : public Block {
public:
  // Foward the constructor to the respective Block constructor
  BasicBlock() : Block() {}
  BasicBlock(Color c) : Block(c) {}
  // These methods will not be tested here, but in the actual children of Block
  virtual bool canMoveOnTop() const { false; }
  virtual BlockType getBlockType() const { return PlayerBlock; }
};

void blockTests_run() {
  cout << "Running Block Tests:" << endl;
  cout << "--------------------" << endl;

  // Create a new testing object to keep track of the results of each test
  Testing t;

  // Run all tests
  t.assert(blockTests_constructors());
  t.assert(blockTests_setColor());

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
bool blockTests_constructors() {
  // Start new testing object
  Testing t("constructors");

  // Create an object and assert its default constructor worked
  BasicBlock b1;
  t.assert(b1.getColor().r == 0 && b1.getColor().g == 0 && b1.getColor().b == 0,
           "Default color not set correctly.");

  // Create an object and assert its colors were set correctly
  BasicBlock b2({1, 0.4, 0.856});
  t.assert(b2.getColor().r == 1 && b2.getColor().g == 0.4 &&
               b2.getColor().b == 0.856,
           "Custom color not set correctly.");

  return t.getResult(); // Return pass or fail result
}

// Test setColor
bool blockTests_setColor() {
  // Start new testing object
  Testing t("setColor()");

  // Create an object, change the color, and assert its color was updated
  BasicBlock b1;
  b1.setColor({1, 0.4, 0.856});
  t.assert(b1.getColor().r == 1 && b1.getColor().g == 0.4 &&
               b1.getColor().b == 0.856,
           "Custom color not set correctly.");

  // Try setting the color all negative
  b1.setColor({-1, -2, -3});
  t.assert(b1.getColor().r == 0 && b1.getColor().g == 0 && b1.getColor().b == 0,
           "Negative custom color not set correctly.");

  // Try setting the color all greater than 1
  b1.setColor({2, 234, 3.14});
  t.assert(b1.getColor().r == 1 && b1.getColor().g == 1 && b1.getColor().b == 1,
           "Negative custom color not set correctly.");

  // Create an object with out of bounds numbers and assert its colors were set
  // correctly
  BasicBlock b2({-1, 5, 0.856});
  t.assert(b2.getColor().r == 0 && b2.getColor().g == 1 &&
               b2.getColor().b == 0.856,
           "Out of bounds color not set correctly.");

  return t.getResult(); // Return pass or fail result
}