#ifndef gui_h
#define gui_h

#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "gameboard.hpp"

/**
* Requires: Command line arguments, and a pointer to a gameboard
* Modifies: everything
* Effects: Starts the GUI
*/
void startGUI(int argc, char **argv, GameBoard *g);

/**
* Requires: nothing
* Modifies: isDragging lastCursorPosition
* Effects: Prepares the variables
*/
void init();

/**
* Requires: nothing
* Modifies: GULT
* Effects: Prepares the GUI
*/
void initGL();

/**
* Requires: nothing
* Modifies: nothing
* Effects: Prepares to exit the GUI
*/
void exitGUI();

// Callback functions for GLUT

/**
* Requires: GLUT to be setup
* Modifies: GLUT
* Effects: Displays the game by drawing the window. Called whenever the window
* needs repainting.
*/
void display(void);

/**
* Requires: nothing
* Modifies: nothing
* Effects: nothing (confirms save)
*/
void displayConfirmation();

/**
* Requires: nothing
* Modifies: nothing
* Effects: nothing (displays tutorial)
*/
void displayTutorial();

/**
* Requires: GLUT to be setup and key info
* Modifies: GLUT
* Effects: Trap and process keyboard events
*/
void kbd(unsigned char key, int x, int y);

/**
* Requires: GLUT to be setup and key info
* Modifies: GLUT
* Effects: Trap and process special keyboard events
*/
void kbdS(int key, int x, int y);

/**
* Requires: GLUT to be setup and mouse info
* Modifies: GLUT
* Effects: Handle "mouse cursor moved" events
*/
void cursor(int x, int y);

/**
* Requires: GLUT to be setup and mouse info
* Modifies: GLUT
* Effects: Handle mouse button pressed and released events
*/
void mouse(int button, int state, int x, int y);

/**
* Requires: GLUT to be setup and extra timer info
* Modifies: GLUT
* Effects: Handle timer
*/
void timer(int extra);

#endif /* gui_h */