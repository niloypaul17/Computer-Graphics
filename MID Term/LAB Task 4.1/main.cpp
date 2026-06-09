#include<windows.h>
#include<iostream>
#include<math.h>
#include <stdio.h>
#include<GL/gl.h>
#include <GL/glut.h>

using namespace std;

int xc = -2;   // center x
int yc = -2;   // center y
int r  = 50;   // radius

// Function to draw 8 symmetric points
void draw8Points(int xc, int yc, int x, int y)
{
    glBegin(GL_POINTS);
        glVertex2i(xc + x, yc + y);
        glVertex2i(xc - x, yc + y);
        glVertex2i(xc + x, yc - y);
        glVertex2i(xc - x, yc - y);

        glVertex2i(xc + y, yc + x);
        glVertex2i(xc - y, yc + x);
        glVertex2i(xc + y, yc - x);
        glVertex2i(xc - y, yc - x);
    glEnd();
}

// Midpoint Circle Algorithm
void midpointCircle()
{
    int x = 0;
    int y = r;
    int d = 1 - r;   // initial decision parameter

    draw8Points(xc, yc, x, y);

    while (x < y)
    {
        if (d < 0)
        {
            d += 2 * x + 3;
        }
        else
        {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;

        draw8Points(xc, yc, x, y);
    }
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    midpointCircle();
    glFlush();
}

void myInit(void)
{
    glClearColor(1, 1, 1, 0);
    glColor3f(1, 0, 0);
    glPointSize(3.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Required coordinate system
    gluOrtho2D(-200, 200, -200, 200);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Midpoint Circle Algorithm");

    glutDisplayFunc(display);
    myInit();
    glutMainLoop();

    return 0;
}
