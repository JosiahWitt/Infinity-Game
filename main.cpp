#include <iostream>
#include <string>

#include "block_tests.hpp"
#include "floor_tests.hpp"
#include "gameboard.hpp"
#include "gameboard_tests.hpp"
#include "player_tests.hpp"
#include "wall_tests.hpp"

using namespace std;

// These methods are defined below
void runTests();
void runGUI();

/**
 * Requires: The command line arguments
 * Modifies: everything
 * Effects: Starts the application
*/
int main(int argc, char const *argv[]) {
  if (argc > 1 && string(argv[1]) == "test") {
    // Run tests
    runTests();
  } else if (argc > 1 && string(argv[1]) == "gui") {
    // Run GUI
    runGUI();
  } else {
    // Present the user with the options
    cout << "Would you like to: " << endl
         << " 1) Launch the game" << endl
         << " 2) Run tests" << endl
         << "Please enter your choice: ";

    // Get the user's choice
    int option;
    while (!(cin >> option) || !(option == 1 || option == 2 || option == 42)) {
      // Not in a good stream state, so clear the stream
      cin.clear();

      // Get rid of the bad input
      string junk;
      getline(cin, junk);

      // Ask the user to try again
      cout
          << "I'm sorry, I couldn't understand that option, please try again: ";
    }

    // Take the specified action
    switch (option) {
    case 1:
      // Launch the game
      cout << endl;
      runGUI();
      break;
    case 2:
      // Run tests
      cout << endl;
      runTests();
      break;
    case 42:
      // Bonus mode
      cout << endl;
      cout << "You found the bonus mode! Unlocking Infinity and Beyond..."
           << endl;
      cout << "Actually, it doesn't do anything special at the moment, except "
              "run both the tests and the game."
           << endl;
      cout << "I'm sorry for getting your hopes up... unless, of course, "
              "that's what you were looking for! :)"
           << endl
           << endl;
      runTests();
      cout << endl;
      runGUI();
    }
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

  // Create a new testing object to keep track of the results of each test
  Testing t;

  t.check(gameboardTests_run());

  cout << endl
       << "--------------------------------------------" << endl
       << endl;

  t.check(blockTests_run());

  cout << endl
       << "--------------------------------------------" << endl
       << endl;

  t.check(playerTests_run());

  cout << endl
       << "--------------------------------------------" << endl
       << endl;

  t.check(floorTests_run());

  cout << endl
       << "--------------------------------------------" << endl
       << endl;

  t.check(wallTests_run());

  cout << endl
       << "--------------------------------------------" << endl
       << endl;

  // Display pass or fail result
  if (t.getResult()) {
    cout << "*** Done testing. All " << t.getNumTested()
         << " test sections passed! ***" << endl;
  } else {
    cout << "*** Failed " << t.getNumFailed() << "/" << t.getNumTested()
         << " test section(s). See message(s) above. ***" << endl;
  }
}

/**
* Requires: nothing
* Modifies: nothing
* Effects: Launches the game
*/
void runGUI() {
  cout << "This will launch Infinity when we add the graphics." << endl;
  cout
      << "Right now, it serves as an example that saves and loads instances of "
         "the game."
      << endl
      << endl;

  // Present the user with the options
  cout << "Would you like to: " << endl
       << " 1) Save an instance of the game" << endl
       << " 2) Load an instance of the game" << endl
       << "Please enter your choice: ";

  // Get the user's choice
  int option;
  while (!(cin >> option) || !(option == 1 || option == 2)) {
    // Not in a good stream state, so clear the stream
    cin.clear();

    // Get rid of the bad input
    string junk;
    getline(cin, junk);

    // Ask the user to try again
    cout << "I'm sorry, I couldn't understand that option, please try again: ";
  }

  // Create a new gameboard
  GameBoard g;

  // Take the specified action
  switch (option) {
  case 1:
    if (g.saveGame()) {
      cout << "Saved!" << endl;
    } else {
      cout << "Error saving game. Couldn't open file." << endl;
    }
    break;
  case 2:
    if (g.loadGame()) {
      cout << "Loaded!" << endl;
    } else {
      cout << "Error loading game. Couldn't open the file." << endl;
    }
    break;
  }

  cout << endl;
  cout << "Once graphics are added, we will use a keyboard shortcut to "
          "save the game while it is running."
       << endl;
}
