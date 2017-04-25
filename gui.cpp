#include "gui.hpp"
#include <stdlib.h>

// Point 2D struct
struct Point2D {
  int x;
  int y;
};

// Pointer to gameboard
GameBoard *gameboard;

// Reference to window
int wd;

// Store the last cursor position
Point2D lastCursorPosition;

// Store if the mouse right button is depressed
bool isDragging;

// store the time when we last saved
int lastSave;

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

  // Initialize the variables
  init();

  // Initialize GLUT
  glutInit(&argc, argv);

  // Use RGBA mode with GLUT
  glutInitDisplayMode(GLUT_RGBA);

  // Set the window size based on the board size
  glutInitWindowSize(gameboard->getGamePixelWidth(),
                     gameboard->getGamePixelHeight());

  // Position the window's initial top-left corner
  glutInitWindowPosition(200, 200);

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
  glutMotionFunc(cursor);

  // handles mouse click
  glutMouseFunc(mouse);

  // handles timer
  glutTimerFunc(0, timer, 0);

  // Enter the event-processing loop
  glutMainLoop();
}

/**
* Requires: nothing
* Modifies: isDragging lastCursorPosition
* Effects: Prepares the variables
*/
void init() {
  // We are not dragging
  isDragging = false;
  // Last cursor position is (0,0)
  lastCursorPosition = {0, 0};
  // Store current time
  lastSave = 0;
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
  //display if recently saved
  displayConfirmation(); 
  // Render now
  glFlush();
}

/**
* Requires: nothing
* Modifies: nothing 
* Effects: nothing (confirms save)
*/
void displayConfirmation() {
	// Take current time stamp and substract it from the last save
	// display for 3 seconds.
	if (time(nullptr) - lastSave < 3) { 
		string saveMessage = "Game Saved";
		glColor3f(1, 1, 1);
		glRasterPos2i(5, 18);
		for (int i = 0; i < saveMessage.length(); ++i) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, saveMessage[i]);
		}
		
	}
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
	lastSave = time(nullptr);
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
void cursor(int x, int y) {
  // If we are dragging, move the wall
  if (isDragging) {
    if (gameboard->moveWall(lastCursorPosition.x, lastCursorPosition.y, x, y)) {
      // Only update the last cursor position if we successfully moved the block
      lastCursorPosition = {x, y};
    }
  }

  glutPostRedisplay();
}

/**
* Requires: GLUT to be setup and mouse info
* Modifies: GLUT
* Effects: Handle mouse button pressed and released events
*/
void mouse(int button, int state, int x, int y) {
  // button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
  // state will be GLUT_UP or GLUT_DOWN

  // Only for the left button
  if (button == GLUT_LEFT_BUTTON) {
    if (state == GLUT_DOWN) {
      // Add a wall
      gameboard->addWall(x, y);
      // On state down, enable dragging
      isDragging = true;
      lastCursorPosition = {x, y};
    } else if (state == GLUT_UP) {
      // On state up, disable dragging
      isDragging = false;
      // Save the game
      gameboard->saveGame();
    }
  }

  // Only for right button
  if (button == GLUT_RIGHT_BUTTON) {
    if (state == GLUT_DOWN) {
      // Remove a wall
      gameboard->removeWall(x, y);
      // Save the game
      gameboard->saveGame();
    }
  }

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