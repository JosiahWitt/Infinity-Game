#include "floor_tests.hpp"

void floorTests_run() {
  cout << "Running Floor Tests:" << endl;
  cout << "--------------------" << endl;

  // Create a new testing object to keep track of the results of each test
  Testing t;

  // Run all tests
  t.check(floorTests_constants());
    t.check(floorTests_types());

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

// Test getTypeOfFloor() and changeFloorType()
bool floorTests_types() {
    // Start new testing object
    Testing t("getTypeOfFloor() and changeFloorType()");
    
    // Create the object and test to see if it can get and set floor type
    Floor f;
    t.check(f.getTypeOfFloor() == GrassFloor, "Floor is not a GrassFloor");
    f.setTypeOfFloor(GrassFloor);
    t.check(f.getColor().r == 0 && f.getColor().g == 123/255.0 && f.getColor().b == 12/255.0, "Floor isn't the correct color");
    
    f.setTypeOfFloor(SandFloor);
    t.check(f.getColor().r == 237/255.0 && f.getColor().g == 201/255.0 && f.getColor().b == 175/255.0, "Floor isn't the correct color");
    
    f.setTypeOfFloor(DirtFloor);
    t.check(f.getColor().r == 120/255.0 && f.getColor().g == 72/255.0 && f.getColor().b == 0, "Floor isn't the correct color");
    
    return t.getResult(); // Return pass or fail result
}

