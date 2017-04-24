#include "gui.hpp"
#include <stdlib.h>

// Pointer to gameboard
GameBoard *gameboard;
// Reference to window
int wd;

/**
* Requires: Command line arguments, and a pointer to a gameboard
* Modifies: everything
* Effects: Starts the GUI
*/
void startGUI(int argc, char **argv, GameBoard *g) {
  // Save the pointer to the gameboard
  gameboard = g;

  // Set at exit callback to save the game
  atexit(exitGUI);

  // Initialize GLUT
  glutInit(&argc, argv);

  // Use RGBA mode with GLUT
  glutInitDisplayMode(GLUT_RGBA);

  // Set the window size based on the board size
  glutInitWindowSize(gameboard->getGamePixelWidth(),
                     gameboard->getGamePixelHeight());

  // Position the window's initial top-left corner
  glutInitWindowPosition(300, 300);

  // create the window and store the handle to it
  wd = glutCreateWindow("Infinity");

  // Register callback handler for window re-paint event
  glutDisplayFunc(display);

  // Our own OpenGL initialization
  initGL();

  // register keyboard press event processing function
  // works for numbers, letters, spacebar, etc.
  glutKeyboardFunc(kbd);

  // register special event: function keys, arrows, etc.
  glutSpecialFunc(kbdS);

  // handles mouse movement
  glutPassiveMotionFunc(cursor);

  // handles mouse click
  glutMouseFunc(mouse);

  // handles timer
  glutTimerFunc(0, timer, 0);

  // Enter the event-processing loop
  glutMainLoop();
}

/**
* Requires: nothing
* Modifies: GULT
* Effects: Prepares the GUI
*/
void initGL() {
  // Set background color to black and opaque
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

/**
* Requires: nothing
* Modifies: nothing
* Effects: Prepares to exit the GUI
*/
void exitGUI() {
  // Save game
  gameboard->saveGame();
}

/**
* Requires: GLUT to be setup
* Modifies: GLUT
* Effects: Displays the game by drawing the window. Called whenever the window
* needs repainting.
*/
void display() {
  // Use the whole window for drawing
  glViewport(0, 0, gameboard->getGamePixelWidth(),
             gameboard->getGamePixelHeight());

  // Do an orthographic parallel projection with the coordinate
  // system set to first quadrant, limited by screen/window size
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, gameboard->getGamePixelWidth(), gameboard->getGamePixelHeight(),
          0.0, -1.f, 1.f);

  // Clear the color buffer with background color
  glClear(GL_COLOR_BUFFER_BIT);

  // Enable plolygon front and back mode
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  // Display the gameboard
  gameboard->display();

  // Render now
  glFlush();
}

/**
* Requires: GLUT to be setup and key info
* Modifies: GLUT
* Effects: Trap and process keyboard events
*/
void kbd(unsigned char key, int x, int y) {
  // Escape:
  // http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
  if (key == 27) {
    // Prepare to exit
    exitGUI();
    // Destroy window
    glutDestroyWindow(wd);
    exit(0);
  }

  // Save the game with the s key
  if (key == 's') {
    gameboard->saveGame();
  }

  glutPostRedisplay();

  return;
}

/**
* Requires: GLUT to be setup and key info
* Modifies: GLUT
* Effects: Trap and process special keyboard events
*/
void kbdS(int key, int x, int y) {
  // Move a direction depending on the key
  switch (key) {
  case GLUT_KEY_DOWN:
    gameboard->movePlayer(DIR_DOWN);
    break;
  case GLUT_KEY_LEFT:
    gameboard->movePlayer(DIR_LEFT);
    break;
  case GLUT_KEY_RIGHT:
    gameboard->movePlayer(DIR_RIGHT);
    break;
  case GLUT_KEY_UP:
    gameboard->movePlayer(DIR_UP);
    break;
  }

  glutPostRedisplay();

  return;
}

/**
* Requires: GLUT to be setup and mouse info
* Modifies: GLUT
* Effects: Handle "mouse cursor moved" events
*/
void cursor(int x, int y) { glutPostRedisplay(); }

/**
* Requires: GLUT to be setup and mouse info
* Modifies: GLUT
* Effects: Handle mouse button pressed and released events
*/
void mouse(int button, int state, int x, int y) {
  // button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
  // state will be GLUT_UP or GLUT_DOWN
  glutPostRedisplay();
}

/**
* Requires: GLUT to be setup and extra timer info
* Modifies: GLUT
* Effects: Handle timer
*/
void timer(int extra) {

  glutPostRedisplay();
  glutTimerFunc(30, timer, 0); // Every 30 ms
}