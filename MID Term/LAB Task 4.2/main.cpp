#include<windows.h>
#include<iostream>
#include<math.h>
#include <stdio.h>
#include<GL/gl.h>
#include <GL/glut.h>

using namespace std;

float PI = 3.1416;

// Draw a Filled Circle using Triangle Fan
void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius)
{
    int triangleAmount = 100;
    float twicePi = 2 * PI;

    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y);  // circle center
        for(int i = 0; i <= triangleAmount; i++)
        {
            glVertex2f
            (
                x + (radius * cos(i * twicePi / triangleAmount)),
                y + (radius * sin(i * twicePi / triangleAmount))
            );
        }
    glEnd();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Center offset
    int cx = 50;
    int cy = 20;

    // FLAG POLE - BLACK
    glColor3ub(0,0,0);
    glLineWidth(6.0);
    glBegin(GL_LINES);
        glVertex2i(-150 + cx, -150 + cy);
        glVertex2i(-150 + cx,  70 + cy);
    glEnd();

    // Pole tip triangle - BLACK
    glBegin(GL_TRIANGLES);
        glColor3ub(0,0,0);
        glVertex2i(-150 + cx, 75 + cy);
        glVertex2i(-155 + cx, 62 + cy);
        glVertex2i(-145 + cx, 62 + cy);
    glEnd();

    // GREEN RECTANGULAR
    glColor3ub(0, 106, 78);
    glBegin(GL_QUADS);
        glVertex2i(-150 + cx,  60 + cy);
        glVertex2i(  50 + cx,  60 + cy);
        glVertex2i(  50 + cx, -60 + cy);
        glVertex2i(-150 + cx, -60 + cy);
    glEnd();

    // RED CIRCLE
    glColor3ub(244, 42, 65);
    drawFilledCircle(-50 + cx, 0 + cy, 35);

    // WHITE STRIP ON POLE
    glColor3ub(255, 255, 255);
    glLineWidth(7.0);
    glBegin(GL_LINES);
        glVertex2i(-150 + cx, -60 + cy);
        glVertex2i(-150 + cx,  60 + cy);
    glEnd();

    glFlush();
}

// INITIALIZATION FUNCTION
void myInit(void)
{
    glClearColor(0.90, 0.90, 0.90, 0.0);   // Light gray background
    glColor3f(0,0,0);
    glPointSize(3.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-200, 200, -200, 200);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);

    glutCreateWindow("Bangladesh Flag - OpenGL");
    glutDisplayFunc(display);
    myInit();
    glutMainLoop();

    return 0;
}
