#include <experimental/filesystem> // Only available in C++17. On Linux, compile with the -lstdc++fs flag.
#include <iomanip>
#include <iostream>
#include <math.h>
#include <string>

#include "block_tests.hpp"
#include "floor_tests.hpp"
#include "gameboard.hpp"
#include "gameboard_tests.hpp"
#include "gui.hpp"
#include "player_tests.hpp"
#include "wall_tests.hpp"

using namespace std;
using namespace experimental::filesystem;

// These methods are defined below
void runTests();
void runGUI(int argc, char **argv);

// Structure the file metadata
struct FileMetadata {
  string shortName;          // Part before .infinity.json
  string lastModifiedString; // Human readable string
  long int lastModifiedInt;  // Unix timestamp
};

/**
 * Requires: The command line arguments
 * Modifies: everything
 * Effects: Starts the application
*/
int main(int argc, char **argv) {
  if (argc > 1 && string(argv[1]) == "test") {
    // Run tests
    runTests();
  } else if (argc > 1 && string(argv[1]) == "gui") {
    // Run GUI
    runGUI(argc, argv);
  } else {
    // Present the user with the options
    cout << "Would you like to: " << endl << " 1) Launch the game" << endl << " 2) Run tests" << endl << "Please enter your choice: ";

    // Get the user's choice
    int option;
    while (!(cin >> option) || !(option == 1 || option == 2 || option == 42)) {
      // Not in a good stream state, so clear the stream
      cin.clear();

      // Get rid of the bad input
      string junk;
      getline(cin, junk);

      // Ask the user to try again
      cout << "I'm sorry, I couldn't understand that option, please try again: ";
    }

    // Take the specified action
    switch (option) {
    case 1:
      // Launch the game
      cout << endl;
      runGUI(argc, argv);
      break;
    case 2:
      // Run tests
      cout << endl;
      runTests();
      break;
    case 42:
      // Bonus mode
      cout << endl;
      cout << "You found the bonus mode! Unlocking Infinity and Beyond..." << endl;
      cout << "Actually, it doesn't do anything special at the moment, except "
              "run both the tests and the game."
           << endl;
      cout << "I'm sorry for getting your hopes up... unless, of course, "
              "that's what you were looking for! :)"
           << endl
           << endl;
      runTests();
      cout << endl;
      runGUI(argc, argv);
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

  cout << endl << "--------------------------------------------" << endl << endl;

  t.check(blockTests_run());

  cout << endl << "--------------------------------------------" << endl << endl;

  t.check(playerTests_run());

  cout << endl << "--------------------------------------------" << endl << endl;

  t.check(floorTests_run());

  cout << endl << "--------------------------------------------" << endl << endl;

  t.check(wallTests_run());

  cout << endl << "--------------------------------------------" << endl << endl;

  // Display pass or fail result
  if (t.getResult()) {
    cout << "*** Done testing. All " << t.getNumTested() << " test sections passed! ***" << endl;
  } else {
    cout << "*** Failed " << t.getNumFailed() << "/" << t.getNumTested() << " test section(s). See message(s) above. ***" << endl;
  }
}

/**
* Requires: The command line arguments
* Modifies: nothing
* Effects: Launches the game
*/
void runGUI(int argc, char **argv) {
  // Store the list of game files
  vector<FileMetadata> saveFiles;
  // Store the longest game name
  int longestName = 0;

  // Loop through all the files in the current directory
  // http://en.cppreference.com/w/cpp/experimental/fs
  for (auto &p : directory_iterator(".")) {
    // Get the path as a string
    string path = p.path().string();

    // Try to find game files
    string::size_type found = path.rfind(".infinity.json");

    // If the file is a game file, add it to the vector
    if (found != string::npos) {
      // Create a string representing the last modified time
      auto lastWriteTime = last_write_time(p);
      time_t lastModifiedStringTime = decltype(lastWriteTime)::clock::to_time_t(lastWriteTime);
      char lastModifiedString[21];
      strftime(lastModifiedString, 21, "%m/%d/%Y %I:%M%p", localtime(&lastModifiedStringTime));

      // Create the filename from the path string
      string filename = path.substr(0, found).substr(2);

      // Add to the vector
      saveFiles.push_back({filename, lastModifiedString, static_cast<long int>(lastModifiedStringTime)});

      // Update the longest name
      if (filename.length() > longestName) {
        longestName = filename.length();
      }
    }
  }

  // Sort the files by descending date
  sort(saveFiles.begin(), saveFiles.end(), [](const FileMetadata &lhs, const FileMetadata &rhs) { return lhs.lastModifiedInt > rhs.lastModifiedInt; });

  // Create a new gameboard
  GameBoard g;

  // Default save or load game option
  int option = 1;

  // If there aren't any game files, load the game
  if (saveFiles.size() != 0) {
    // Present the user with the options
    cout << "Would you like to: " << endl << " 1) Start New Game" << endl << " 2) Load Existing Game" << endl << "Please enter your choice: ";

    // Get the user's choice
    while (!(cin >> option) || !(option == 1 || option == 2)) {
      // Not in a good stream state, so clear the stream
      cin.clear();

      // Get rid of the bad input
      string junk;
      getline(cin, junk);

      // Ask the user to try again
      cout << "I'm sorry, I couldn't understand that option, please try again: ";
    }
  }

  // Take the specified action
  switch (option) {
  case 1:
    if (g.saveGame()) {
      cout << "Created a new game!" << endl;
      cout << "Launching Infinity..." << endl;

      // Start the game
      startGUI(argc, argv, &g);
    } else {
      cout << "Error saving game. Couldn't create the file." << endl;
    }
    break;
  case 2:
    // Store user's game choice
    int fileChoice = 0;

    // If there is only 1 game file, load that one
    if (saveFiles.size() != 1) {
      // Present the user with the options
      cout << endl << "Please choose the game file you would like to load: " << endl;

      // Print the header
      cout << " " << right << setw(log10(saveFiles.size()) + 4) << "#  " << left << setw(longestName + 5) << "Filename"
           << "Last Modified" << endl;

      // Print all the game files
      for (int i = 0; i < saveFiles.size(); i++) {
        cout << " " << right << setw(log10(saveFiles.size()) + 4) << to_string(i) + ": " << left << setw(longestName + 5) << saveFiles[i].shortName << saveFiles[i].lastModifiedString << endl;
      }

      cout << "Please enter your choice #: ";

      // Get the user's choice
      while (!(cin >> fileChoice) || (fileChoice < 0 || fileChoice >= saveFiles.size())) {
        // Not in a good stream state, so clear the stream
        cin.clear();

        // Get rid of the bad input
        string junk;
        getline(cin, junk);

        // Ask the user to try again
        cout << "I'm sorry, I couldn't understand that option, please try again: ";
      }
    }

    // Load the chosen game
    cout << endl << "Loading '" << saveFiles[fileChoice].shortName + ".infinity.json'..." << endl;
    if (g.loadGame(saveFiles[fileChoice].shortName + ".infinity.json")) {
      cout << "Game loaded!" << endl;
      cout << "Launching Infinity..." << endl;

      // Start the game
      startGUI(argc, argv, &g);
    } else {
      cout << "Error loading game. Couldn't open the file." << endl;
    }
    break;
  }
}
