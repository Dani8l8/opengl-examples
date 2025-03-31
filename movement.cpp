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

void drawSquare(float bottom, float left, float side, float r, float g, float b) {
  
  glBegin(GL_QUADS);
  glColor3f(r,g,b); // Yellow
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
// Movement vector class
// ----------------------------------------------------------

class ColVec3f {
public:
  float r;
  float g;
  float b;
};

ColVec3f col_vector;

// ----------------------------------------------------------
// Pressed keys states
// ----------------------------------------------------------

int keyUpPressed = 0;
int keyDownPressed = 0;
int keyLeftPressed = 0;
int keyRightPressed = 0;
int keyCtrlPressed = 0;

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

  // Al hacer esto el cuadro solo cambia de color al presionar una tecla de direccion
  // y no al solo presionar ctrl por lo que lo ideal seria que estuviera en la
  // funcion de 'UnprocessSpecialKeys' pero al menos resuelve el problema en el cual
  // el cuadro cambia de color de manera aleatoria durante el movimiento lento
  if (glutGetModifiers() & GLUT_ACTIVE_CTRL) { keyCtrlPressed = 1; } else { keyCtrlPressed = 0; };
  
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

  float speed = 0.02f;
  
  col_vector = { 1.0f, 1.0f, 0.0f };

  if (keyCtrlPressed) { speed = 0.005f; col_vector.g = 0.0f; } ;

  moveSquare(mov_vector, speed);

  //  Clear screen and Z-buffer
  glClear(GL_COLOR_BUFFER_BIT);

  // Reset transformations
  glLoadIdentity();
  
  if (abs(bottom) >= 1.0f) { bottom *= -1; };
  if (abs(left) >= 1.0f) { left *= -1; };

  drawSquare(bottom,left, 0.03f, col_vector.r, col_vector.g, col_vector.b);
   
  
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
