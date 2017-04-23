#include "floor_tests.hpp"

bool floorTests_run() {
  cout << "Running Floor Tests:" << endl;
  cout << "--------------------" << endl;

  // Create a new testing object to keep track of the results of each test
  Testing t;

  // Run all tests
  t.check(floorTests_constants());
  t.check(floorTests_types());
  t.check(floorTests_toJsonAndFromJson());

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
bool floorTests_constants() {
  // Start new testing object
  Testing t("canMoveOnTop() and getBlockType()");

  // Create an object and check its constants are correct
  Floor f;
  t.check(f.canMoveOnTop() == true, "Cannot move on top of floor");
  t.check(f.getBlockType() == FloorBlock, "Floor is not a FloorBlock");

  return t.getResult(); // Return pass or fail result
}

// Test getFloorType() and changeFloorType()
bool floorTests_types() {
  // Start new testing object
  Testing t("getFloorType() and changeFloorType()");

  // Create the object and test to see if it can get and set floor type
  Floor f;
  t.check(f.getFloorType() == GrassFloor, "Floor is not a GrassFloor");
  f.setFloorType(GrassFloor);
  t.check(f.getColor().r == 0 && f.getColor().g == 123 / 255.0 &&
              f.getColor().b == 12 / 255.0,
          "GrassFloor isn't the correct color");

  f.setFloorType(SandFloor);
  t.check(f.getColor().r == 237 / 255.0 && f.getColor().g == 201 / 255.0 &&
              f.getColor().b == 175 / 255.0,
          "SandFloor isn't the correct color");

  f.setFloorType(DirtFloor);
  t.check(f.getColor().r == 120 / 255.0 && f.getColor().g == 72 / 255.0 &&
              f.getColor().b == 0,
          "DirtFloor isn't the correct color");

  return t.getResult(); // Return pass or fail result
}

// Tests toJson and fromJson
bool floorTests_toJsonAndFromJson() {
  // Start new testing object
  Testing t("toJson() and fromJson()");

  // Create an object, and export and import using json, and
  // assert the json is identical
  Floor f1;
  json j1 = f1.toJson();
  Floor f2;
  f2.fromJson(j1);
  t.check(f2.getColor().r == 0 && f2.getColor().g == 123 / 255.0 &&
              f2.getColor().b == 12 / 255.0 && f2.getFloorType() == GrassFloor,
          "Didn't export and import default JSON correctly.");

  // Create an object, change the color, and export and import using json, and
  // assert the json is identical
  Floor f3;
  f3.setFloorType(DirtFloor);
  json j3 = f3.toJson();
  Floor f4;
  f4.fromJson(j3);
  t.check(f4.getFloorType() == DirtFloor,
          "Didn't export and import custom JSON correctly.");

  // Import json into an object, and assert the color, alternateColor, and
  // player's vector positions were updated correctly
  Floor f5;
  f5.fromJson(
      {{"color", {{"r", 0.9}, {"g", 0.8}, {"b", 0.7}}}, {"floorType", 2}});
  t.check(f5.getFloorType() == SandFloor,
          "Didn't import custom JSON correctly.");

  return t.getResult(); // Return pass or fail result
}
