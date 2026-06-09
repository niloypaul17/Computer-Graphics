#include<windows.h>
#include<iostream>
#include<GL/gl.h>
#include <GL/glut.h>

using namespace std;

void DDA(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1), dy = abs(y2 - y1);
    int steps = max(dx, dy);
    float xinc = dx / (float)steps, yinc = dy / (float)steps;
    float x = x1, y = y1;
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    if (x1 > x2) xinc = -xinc;
    if (y1 > y2) yinc = -yinc;

    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; i++) {
        glVertex2i((int)(x + 0.5), (int)(y + 0.5));
        x += xinc; y += yinc;
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,0,0);
    glBegin(GL_LINES);
        glVertex2i(-100,0); glVertex2i(100,0);
        glVertex2i(0,-100); glVertex2i(0,100);
    glEnd();

    glColor3f(1,0,0); DDA(-80,80,80,-80);  // Red line
    glColor3f(0,1,0); DDA(-80,-80,80,80);  // Green line

    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glPointSize(3.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100, 100, -100, 100);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("LAB 2: DDA Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
