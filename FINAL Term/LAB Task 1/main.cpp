#include <windows.h>
#include <GL/glut.h>
#include <cmath>

float angle = 175.0f;
const float PI = 3.14159265f;

// Draw a circle for wheels
void drawWheel(float x, float y, float radius) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float theta = i * PI / 180.0f;
        glVertex2f(x + radius * cos(theta), y + sin(theta) * radius);
    }
    glEnd();
}

void drawCarShape() {

    // 1. Define the 5 points of the Pentagon (Van Shape)
    float points[5][2] = {
        {-25, 0},  // 0: Bottom-Back
        { 25, 0},  // 1: Bottom-Front
        { 25, 12}, // 2: Front-Hood
        { 10, 22}, // 3: Top-Windshield (The Pentagon "Point")
        {-25, 22}  // 4: Top-Back
    };

    float Angle = -175.0f * PI / 180.0f;

    // Draw the Body with Gradient (Red top, Green bottom)
    glBegin(GL_POLYGON);
    for (int i = 0; i < 5; i++) {

        float x = points[i][0] * cos(Angle) - points[i][1] * sin(Angle);
        float y = points[i][0] * sin(Angle) + points[i][1] * cos(Angle);

        if (i >= 3) glColor3f(1.0f, 0.0f, 0.0f); // Red Top
        else glColor3f(0.0f, 1.0f, 0.0f);        // Green Bottom
        glVertex2f(x, y);
    }
    glEnd();

    // Draw Wheels
    glColor3f(0.0f, 1.0f, 0.0f);
    float wheelPos[2][2] = {{-15, -3}, {15, -3}};
    for (int i = 0; i < 2; i++) {
        float wx = wheelPos[i][0] * cos(Angle) - wheelPos[i][1] * sin(Angle);
        float wy = wheelPos[i][0] * sin(Angle) + wheelPos[i][1] * cos(Angle);
        drawWheel(wx, wy, 6);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    //1. DRAW PRIMARY CAR (Before Transformation)
    glPushMatrix();
        glTranslatef(-120.0f, 100.0f, 0.0f);
        drawCarShape();
    glPopMatrix();

    // 2. DRAW TRANSFORMED CAR
    glPushMatrix();
        glTranslatef(3.0f, 4.0f, 0.0f);       // tx=3, ty=4
        glRotatef(angle, 0.0f, 0.0f, 1.0f);  // Rotation = 175
        glScalef(3.0f, 4.0f, 1.0f);          // sx=3, sy=4


        drawCarShape();
    glPopMatrix();

    glutSwapBuffers();
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-200, 200, -300, 300);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Transformation Lab - Final Pentagon Car");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
