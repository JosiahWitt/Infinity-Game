#include <iostream>
#include <string>

#include "block_tests.hpp"
#include "floor_tests.hpp"
#include "gameboard.hpp"
#include "gameboard_tests.hpp"
#include "player_tests.hpp"
#include "wall_tests.hpp"

using namespace std;

void runTests();
void runGUI();

/**
 * Requires:
 * Modifies:
 * Effects:
*/
int main(int argc, char const *argv[]) {
  if (argc > 1 && string(argv[1]) == "test") {
    // Run tests
    runTests();
  } else if (argc > 1 && string(argv[1]) == "gui") {
    // Run GUI
    runGUI();
  } else {
    // TODO: Get users input to launch tests or gui
    cout << "Please use a command line argument. To run tests use 'test'. To "
            "launch the game use 'gui'."
         << endl;
  }

  return 0;
}

/**
* Requires: nothing
* Modifies: nothing
* Effects: Runs the tests
*/
void runTests() {
  cout << "TESTING" << endl;
  cout << "-------" << endl << endl;

  gameboardTests_run();

  cout << endl
       << "--------------------------------------------" << endl
       << endl;

  blockTests_run();

  cout << endl
       << "--------------------------------------------" << endl
       << endl;

  playerTests_run();

  cout << endl
       << "--------------------------------------------" << endl
       << endl;

  floorTests_run();

  cout << endl
       << "--------------------------------------------" << endl
       << endl;

  wallTests_run();
}

/**
* Requires: nothing
* Modifies: nothing
* Effects: Launches the game
*/
void runGUI() { cout << "Launching Infinity..." << endl; }