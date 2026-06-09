#include <windows.h>
#include <iostream>
#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>

using namespace std;

float xa, ya, xb, yb;  // Line 1
float xc, yc, xd, yd;  // Line 2

void drawAxes() {
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2i(-100, 0); glVertex2i(100, 0);
    glVertex2i(0, -100); glVertex2i(0, 100);
    glEnd();
}

void drawDDA(float X1, float Y1, float X2, float Y2, int r, int g, int b) {
    float m = (Y2 - Y1) / (X2 - X1);
    glColor3ub(r, g, b);
    glBegin(GL_POINTS);

    // Swap to ensure X1 < X2 and Y1 < Y2
    if (X1 > X2) { swap(X1, X2); swap(Y1, Y2); m = -m; }
    if (Y1 > Y2) { swap(Y1, Y2); m = -m; }

    if (m <= 1) {
        while (X1 < X2 && Y1 < Y2) {
            X1 = X1 + 1;
            Y1 = Y1 + m;
            glVertex2i(round(X1), round(Y1));
        }
    } else {
        while (X1 < X2 && Y1 < Y2) {
            X1 = X1 + (1 / m);
            Y1 = Y1 + 1;
            glVertex2i(round(X1), round(Y1));
        }
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();
    drawDDA(xa, ya, xb, yb, 255, 0, 0);   // Red
    drawDDA(xc, yc, xd, yd, 0, 255, 0);   // Green
    glFlush();
}

void myInit() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glPointSize(4.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100, 100, -100, 100);
}

int main(int argc, char** argv) {
    cout << "Enter Line 1 (X1 Y1 X2 Y2): ";
    cin >> xa >> ya >> xb >> yb;
    cout << "Enter Line 2 (X1 Y1 X2 Y2): ";
    cin >> xc >> yc >> xd >> yd;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("LAB 2: DDA - Two Lines");
    myInit();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
