#include "player_tests.hpp"

bool playerTests_run() {
  cout << "Running Player Tests:" << endl;
  cout << "---------------------" << endl;

  // Create a new testing object to keep track of the results of each test
  Testing t;

  // Run all tests
  t.check(playerTests_constants());
  t.check(playerTests_colors());
  t.check(playerTests_coordinates());
  t.check(playerTests_toJsonAndFromJson());

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
  t.check(p1.getAlternateColor().r == 0 && p1.getAlternateColor().g == 0 &&
              p1.getAlternateColor().b == 0,
          "Negative custom color not set correctly.");

  // Try setting the color all greater than 1
  p1.setAlternateColor({2, 234, 3.14});
  t.check(p1.getAlternateColor().r == 1 && p1.getAlternateColor().g == 1 &&
              p1.getAlternateColor().b == 1,
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

// Test setX()/setY() and getX()/getY()
bool playerTests_coordinates() {
  // Start new testing object
  Testing t("setX()/setY() and getX()/getY()");

  // Create an object and check its getters and setters are correct
  Player p;
  p.setVectorX(12);
  p.setVectorY(40);
  t.check(p.getVectorX() == 12, "Player x position is not 12");
  t.check(p.getVectorY() == 40, "Player y position is not 40");

  // Check setting negative values, as they should be set to 0
  p.setVectorX(-10);
  p.setVectorY(-20);
  t.check(p.getVectorX() == 0, "Player x position is not 0");
  t.check(p.getVectorY() == 0, "Player y position is not 0");

  return t.getResult(); // Return pass or fail result
}

// Tests toJson and fromJson
bool playerTests_toJsonAndFromJson() {
  // Start new testing object
  Testing t("toJson() and fromJson()");

  // Create an object, and export and import using json, and
  // assert the json is identical
  Player p1;
  json j1 = p1.toJson();
  Player p2;
  p2.fromJson(j1);
  t.check(p2.getColor().r == 0 && p2.getColor().g == 0 &&
              p2.getColor().b == 0 && p2.getAlternateColor().r == 0 &&
              p2.getAlternateColor().g == 0 && p2.getAlternateColor().b == 0 &&
              p2.getVectorX() == 0 && p2.getVectorY() == 0,
          "Didn't export and import default JSON correctly.");

  // Create an object, change the color, and export and import using json, and
  // assert the json is identical
  Player p3;
  p3.setAlternateColor({1, 0.4, 0.856});
  p3.setVectorX(5);
  p3.setVectorY(6);
  json j3 = p3.toJson();
  Player p4;
  p4.fromJson(j3);
  t.check(p4.getAlternateColor().r == 1 && p4.getAlternateColor().g == 0.4 &&
              p4.getAlternateColor().b == 0.856 && p4.getVectorX() == 5 &&
              p4.getVectorY() == 6,
          "Didn't export and import custom JSON correctly.");

  // Import json into an object, and assert the color, alternateColor, and
  // player's vector positions were updated correctly
  Player p5;
  p5.fromJson({{"color", {{"r", 0.9}, {"g", 0.8}, {"b", 0.7}}},
               {"alternateColor", {{"r", 0.3}, {"g", 0.4}, {"b", 0.5}}},
               {"vectorX", 23},
               {"vectorY", 42}});
  t.check(p5.getColor().r == 0.9 && p5.getColor().g == 0.8 &&
              p5.getColor().b == 0.7 && p5.getAlternateColor().r == 0.3 &&
              p5.getAlternateColor().g == 0.4 &&
              p5.getAlternateColor().b == 0.5 && p5.getVectorX() == 23 &&
              p5.getVectorY() == 42,
          "Didn't import custom JSON correctly.");

  return t.getResult(); // Return pass or fail result
}
