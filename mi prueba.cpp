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
// Prototipos de funciones
// ----------------------------------------------------------
void display();
void specialKeys();
void drawSquare();

// ----------------------------------------------------------
// Variables Globales
// ----------------------------------------------------------
double bottom = 0.0f;  // Posición inicial Y del cuadro controlado por el usuario
double left = 0.0f;    // Posición inicial X del cuadro controlado por el usuario

// Variables para el nuevo cuadro automático
double newBottom = 0.9f;  // Posición Y del nuevo cuadro
double newLeft = 0.9f;    // Posición X del nuevo cuadro (inicia a la derecha)

// ----------------------------------------------------------
// Estructura para el movimiento del cuadro controlado por el usuario
// ----------------------------------------------------------
struct MovVec2f {
    float x;
    float y;
};

// ----------------------------------------------------------
// Función para dibujar el cuadro
// ----------------------------------------------------------

void drawSquare(float bottom, float left, float side, float r, float g, float b) {
    glBegin(GL_QUADS);
    glColor3f(r, g, b);  // Color del cuadrado
    glVertex2f(left, bottom);    // Esquina inferior izquierda
    glVertex2f(left + side, bottom); // Esquina inferior derecha
    glVertex2f(left + side, bottom + side); // Esquina superior derecha
    glVertex2f(left, bottom + side); // Esquina superior izquierda
    glEnd();
}

// ----------------------------------------------------------
// Función para mover el nuevo cuadro automáticamente hacia la izquierda
// ----------------------------------------------------------

void moveNewSquare(float speed) {
    newLeft -= speed;  // Mueve el cuadro hacia la izquierda

    // Cuando el cuadro llegue al borde izquierdo, lo reiniciamos a la parte superior derecha
    if (newLeft < -1.0f) {
        newLeft = 1.0f;  // Resetea a la parte superior derecha
    }
}

// ----------------------------------------------------------
// Variables para el control de teclas especiales
// ----------------------------------------------------------

int keyUpPressed = 0;
int keyDownPressed = 0;
int keyLeftPressed = 0;
int keyRightPressed = 0;
int keyCtrlPressed = 0;

void ProcessSpecialKeys(int key, int x, int y) {
    if (glutGetModifiers() & GLUT_ACTIVE_CTRL) {
        keyCtrlPressed = 1;
    }
    else {
        keyCtrlPressed = 0;
    }

    if (key == GLUT_KEY_RIGHT)
        keyRightPressed = 1;
    else if (key == GLUT_KEY_LEFT)
        keyLeftPressed = 1;
    else if (key == GLUT_KEY_UP)
        keyUpPressed = 1;
    else if (key == GLUT_KEY_DOWN)
        keyDownPressed = 1;
}

void UnprocessSpecialKeys(int key, int x, int y) {
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
// Función display() para renderizar los cuadros
// ----------------------------------------------------------

void display() {
    // Movimiento del cuadro controlado por el usuario
    MovVec2f mov_vector = { 0.0f, 0.0f };

    if (keyUpPressed && keyDownPressed) {
        mov_vector.y = 0;
    }
    else if (keyUpPressed) {
        mov_vector.y = 1.0f;
    }
    else if (keyDownPressed) {
        mov_vector.y = -1.0f;
    }
    else {
        mov_vector.y = 0;
    }

    if (keyLeftPressed && keyRightPressed) {
        mov_vector.x = 0;
    }
    else if (keyRightPressed) {
        mov_vector.x = 1.0f;
    }
    else if (keyLeftPressed) {
        mov_vector.x = -1.0f;
    }
    else {
        mov_vector.x = 0;
    }

    float speed = 0.02f;
    float col_r = 1.0f, col_g = 1.0f, col_b = 0.0f;  // Color amarillo para el cuadro controlado

    if (keyCtrlPressed) {
        speed = 0.005f;
        col_g = 0.0f;  // Cambia a color amarillo si Ctrl está presionado
    }

    // Mueve el cuadro controlado por el usuario
    left += mov_vector.x * speed;
    bottom += mov_vector.y * speed;

    // Movimiento del nuevo cuadro hacia la izquierda automáticamente
    float newSpeed = 0.01f;
    moveNewSquare(newSpeed);

    // Limpiar la pantalla y el Z-buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Resetear transformaciones
    glLoadIdentity();

    // Dibuja el cuadro controlado por el usuario
    drawSquare(bottom, left, 0.03f, col_r, col_g, col_b);

    // Dibuja el nuevo cuadro que se mueve hacia la izquierda
    drawSquare(newBottom, newLeft, 0.03f, 0.0f, 1.0f, 0.0f);  // Este cuadro es verde

    glFlush();
    glutSwapBuffers();

    // Solicitar actualización de la pantalla
    glutPostRedisplay();
}

// ----------------------------------------------------------
// Función main() para inicializar GLUT y configurar todo
// ----------------------------------------------------------

int main(int argc, char* argv[]) {
    // Inicializar GLUT y procesar parámetros del usuario
    glutInit(&argc, argv);

    // Solicitar ventana a color con doble buffer y Z-buffer
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    // Crear la ventana
    glutCreateWindow("Movement Test");

    // Funciones de retorno de llamada
    glutDisplayFunc(display);
    glutSpecialFunc(ProcessSpecialKeys);
    glutSpecialUpFunc(UnprocessSpecialKeys);

    // Iniciar el bucle de GLUT para gestionar eventos
    glutMainLoop();

    return 0;
}
