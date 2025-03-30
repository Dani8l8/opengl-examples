//
// File:       movement.cpp
// Created:    Sun Mar 30 08:28:55 AM -05 2025
// Description: Creates an OpenGL window and draws a 2D square
//              That the user can control using the arrow keys
// 
// Controls:    Left Arrow  - Move Left
//              Right Arrow - Move Right
//              Up Arrow    - Move Up
//              Down Arrow  - Move Down     

// ----------------------------------------------------------
// Includes
// ----------------------------------------------------------
#include <GL/gl.h>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// ----------------------------------------------------------
// Function Prototypes
// ----------------------------------------------------------
void display();
void specialKeys();
void drawSquare();
class MovVec2f;

// ----------------------------------------------------------
// Global Variables
// ----------------------------------------------------------
double bottom=0.1f;
double left = 0.1f;

// ----------------------------------------------------------
// drawSquare() function
// ----------------------------------------------------------

void drawSquare(float bottom, float left, float side) {
  
  glBegin(GL_QUADS);
  glColor3f(1.0f, 1.0f, 0.0f); // Yellow
  glVertex2f(left, bottom);    // x, y
  glVertex2f(left + side, bottom);
  glVertex2f(left + side, bottom + side);
  glVertex2f(left, bottom + side);
  glEnd();

}

// ----------------------------------------------------------
// Movement vector class
// ----------------------------------------------------------

class MovVec2f {
public:
  float x;
  float y;
};

MovVec2f mov_vector;


// ----------------------------------------------------------
// Pressed keys states
// ----------------------------------------------------------

int keyUpPressed = 0;
int keyDownPressed = 0;
int keyLeftPressed = 0;
int keyRightPressed = 0;

// ----------------------------------------------------------
// Movement function
// ----------------------------------------------------------

void moveSquare(MovVec2f mov_vector, float speed) {
  left += mov_vector.x * speed;
  bottom += mov_vector.y * speed;
}

// ----------------------------------------------------------
// specialKeys() Callback Function
// ----------------------------------------------------------
void ProcessSpecialKeys( int key, int x, int y ) {

  if (key == GLUT_KEY_RIGHT)
    keyRightPressed = 1;
 
  else if (key == GLUT_KEY_LEFT)
    keyLeftPressed = 1;
 
  else if (key == GLUT_KEY_UP)
    keyUpPressed = 1;

  else if (key == GLUT_KEY_DOWN)
    keyDownPressed = 1;
}

void UnprocessSpecialKeys( int key, int x, int y ) {

  if (key == GLUT_KEY_RIGHT)
    keyRightPressed = 0;
 
  else if (key == GLUT_KEY_LEFT)
    keyLeftPressed = 0;
 
  else if (key == GLUT_KEY_UP)
    keyUpPressed = 0;

  else if (key == GLUT_KEY_DOWN)
    keyDownPressed = 0;
}


// ----------------------------------------------------------
// display() Callback function
// ----------------------------------------------------------
void display(){

  mov_vector = { 0.0f, 0.0f };

  if (keyUpPressed && keyDownPressed) { mov_vector.y = 0; }
  else if (keyUpPressed) { mov_vector.y = 1.0f; }
  else if (keyDownPressed) { mov_vector.y = -1.0f; }
  else { mov_vector.y = 0; }

  if (keyLeftPressed && keyRightPressed) { mov_vector.x = 0; }
  else if (keyRightPressed) { mov_vector.x = 1.0f; }
  else if (keyLeftPressed) { mov_vector.x = -1.0f; }
  else { mov_vector.x = 0; }

  moveSquare(mov_vector, 0.02f);

  //  Clear screen and Z-buffer
  glClear(GL_COLOR_BUFFER_BIT);

  // Reset transformations
  glLoadIdentity();

  drawSquare(bottom,left, 0.05f);
   
  glFlush();
  glutSwapBuffers();
  
  //  Request display update
  glutPostRedisplay();

}


// ----------------------------------------------------------
// main() function
// ----------------------------------------------------------
int main(int argc, char* argv[]){
 
  //  Initialize GLUT and process user parameters
  glutInit(&argc,argv);
 
  //  Request double buffered true color window with Z-buffer
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
 
  // Create window
  glutCreateWindow("Movement Test");

  // Callback functions
  glutDisplayFunc(display);
  glutSpecialFunc(ProcessSpecialKeys);
  glutSpecialUpFunc(UnprocessSpecialKeys);

  //  Pass control to GLUT for events
  glutMainLoop();
 
  //  Return to OS
  return 0;
 
}
