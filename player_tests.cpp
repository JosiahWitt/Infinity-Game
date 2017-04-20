#include "player_tests.hpp"

void playerTests_run() {
  cout << "Running Player Tests:" << endl;
  cout << "---------------------" << endl;

  // Create a new testing object to keep track of the results of each test
  Testing t;

  // Run all tests
  t.check(playerTests_constants());
  t.check(playerTests_colors());
  t.check(playerTests_coordinates());

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

  // Create an object and check its constants are correct
  Player p;
  t.check(p.canMoveOnTop() == false, "Can move on top of player");
  t.check(p.getBlockType() == PlayerBlock, "Player is not a PlayerBlock");

  return t.getResult(); // Return pass or fail result
}

// Test getAlternateColor(), setAlternateColor(Color c), and swapColor()
bool playerTests_colors() {
    // Start new testing object
    Testing t("getAlternateColor(), setAlternateColor(Color c), and swapColor()");
    
    // Create an object, change the color, and check its color was updated
    Player p1;
    p1.setAlternateColor({1, 0.4, 0.856});
    t.check(p1.getAlternateColor().r == 1 && p1.getAlternateColor().g == 0.4 &&
            p1.getAlternateColor().b == 0.856,
            "Custom color not set correctly.");
    
    // Try setting the color all negative
    p1.setAlternateColor({-1, -2, -3});
    t.check(p1.getAlternateColor().r == 0 && p1.getAlternateColor().g == 0 && p1.getAlternateColor().b == 0,
            "Negative custom color not set correctly.");
    
    // Try setting the color all greater than 1
    p1.setAlternateColor({2, 234, 3.14});
    t.check(p1.getAlternateColor().r == 1 && p1.getAlternateColor().g == 1 && p1.getAlternateColor().b == 1,
            "Negative custom color not set correctly.");
    
    // Create an object with out of bounds numbers and check its colors were set
    // correctly
    Player p2;
    p2.setAlternateColor({-1, 5, 0.856});
    t.check(p2.getAlternateColor().r == 0 && p2.getAlternateColor().g == 1 &&
            p2.getAlternateColor().b == 0.856,
            "Out of bounds color not set correctly.");
    
    return t.getResult(); // Return pass or fail result
}

/**
* Requires: nothing
* Modifies: nothing
* Effects: test getters and setters
*/

bool playerTests_coordinates() {
	// Start new testing object
	Testing t("setX()/setY() and getX()/getY()");

	// Create an object and check its getters and setters are correct
	Player p;
	p.setX(12);
	p.setY(40);
	t.check(p.getX() == 12, "Player x position is not 12"); // work here
	t.check(p.getY() == 40, "Player y position is not 40");

	return t.getResult(); // Return pass or fail result
}