#include <windows.h>
#include <GL/glut.h>
#include <cmath>
#include <cstring>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <iostream>

#define PI 3.14159265f

// Game variables
int currentScore = 0;
int gameTime = 60;
bool gameRunning = true;
int lives = 3;

float planeX = -700.0f;
float planeY = 0.0f;
float coinSpeed = 6.0f;
float minSpeed = 3.0f;
float maxSpeed = 15.0f;

// Coins
const int NUM_COINS = 20;
struct Coin {
    float x, y;
    bool active;
} coins[NUM_COINS];

// Obstacles - now only 5 and cute!
const int NUM_OBSTACLES = 5;
struct Obstacle {
    float x, y;
    bool active;
} obstacles[NUM_OBSTACLES];

// Sound effects
void playCoinSound() { Beep(1200, 150); }
void playHitSound() { Beep(200, 400); }
void playSpeedUpSound() { Beep(1500, 100); }
void playSpeedDownSound() { Beep(800, 100); }

// NEW: Cute Game Over tune
void playGameOverSound() {
    Beep(800, 300);
    Beep(600, 300);
    Beep(400, 600);
}

// Drawing helpers
void drawFilledCircle(float x, float y, float radius) {
    int segments = 50;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= segments; i++) {
        float angle = i * 2.0f * PI / segments;
        glVertex2f(x + radius * cos(angle), y + radius * sin(angle));
    }
    glEnd();
}

// NEW: Cute bird obstacle (smiling with big eyes)
void drawObstacle(float x, float y) {
    // Body (soft pink)
    glColor3ub(255, 182, 193);
    drawFilledCircle(x, y, 35);

    // Wings
    glColor3ub(255, 105, 180);
    drawFilledCircle(x - 30, y, 20);
    drawFilledCircle(x + 30, y, 20);

    // Big cute eyes
    glColor3ub(255, 255, 255);
    drawFilledCircle(x - 15, y + 10, 12);
    drawFilledCircle(x + 15, y + 10, 12);
    glColor3ub(0, 0, 0);
    drawFilledCircle(x - 15, y + 12, 6);
    drawFilledCircle(x + 15, y + 12, 6);

    // Smiling mouth
    glColor3ub(0, 0, 0);
    glLineWidth(3);
    glBegin(GL_LINE_STRIP);
    glVertex2f(x - 12, y - 8);
    glVertex2f(x, y - 15);
    glVertex2f(x + 12, y - 8);
    glEnd();

    // Little blush
    glColor3ub(255, 150, 150);
    drawFilledCircle(x - 20, y - 5, 7);
    drawFilledCircle(x + 20, y - 5, 7);
}

void drawPlane() {
    glColor3ub(100, 100, 100);
    glBegin(GL_QUADS);
    glVertex2f(planeX - 70, planeY - 20);
    glVertex2f(planeX + 70, planeY - 20);
    glVertex2f(planeX + 70, planeY + 20);
    glVertex2f(planeX - 70, planeY + 20);
    glEnd();

    glColor3ub(0, 100, 200);
    glBegin(GL_TRIANGLES);
    glVertex2f(planeX + 70, planeY);
    glVertex2f(planeX + 100, planeY + 15);
    glVertex2f(planeX + 100, planeY - 15);
    glEnd();

    glColor3ub(200, 50, 50);
    glBegin(GL_TRIANGLES);
    glVertex2f(planeX - 40, planeY + 20); glVertex2f(planeX - 40, planeY + 60); glVertex2f(planeX + 20, planeY + 20);
    glVertex2f(planeX + 40, planeY + 20); glVertex2f(planeX + 40, planeY + 60); glVertex2f(planeX - 20, planeY + 20);
    glEnd();

    glColor3ub(200, 50, 50);
    glBegin(GL_QUADS);
    glVertex2f(planeX - 70, planeY + 20); glVertex2f(planeX - 70, planeY + 50);
    glVertex2f(planeX - 90, planeY + 50); glVertex2f(planeX - 90, planeY + 20);
    glEnd();
}

void drawBackground() {
    glColor3f(0.53f, 0.81f, 0.92f);
    glBegin(GL_QUADS);
    glVertex2f(-1000, -600); glVertex2f(1000, -600);
    glVertex2f(1000, 600);   glVertex2f(-1000, 600);
    glEnd();

    glColor3ub(255, 255, 255);
    drawFilledCircle(-600, 400, 60); drawFilledCircle(-550, 420, 80); drawFilledCircle(-500, 400, 70);
    drawFilledCircle(0, 500, 70);    drawFilledCircle(50, 520, 90);   drawFilledCircle(100, 500, 80);
    drawFilledCircle(700, 450, 60);  drawFilledCircle(750, 470, 80);  drawFilledCircle(800, 450, 70);

    glColor3ub(34, 139, 34);
    glBegin(GL_QUADS);
    glVertex2f(-1000, -200); glVertex2f(1000, -200);
    glVertex2f(1000, -600);  glVertex2f(-1000, -600);
    glEnd();

    glColor3ub(80, 80, 80);
    glBegin(GL_QUADS);
    glVertex2f(-1000, -100); glVertex2f(1000, -100);
    glVertex2f(1000, -300);  glVertex2f(-1000, -300);
    glEnd();

    glColor3ub(255, 255, 255);
    glLineWidth(8.0f);
    glBegin(GL_LINES);
    for (float x = -1000; x < 1000; x += 150) {
        glVertex2f(x, -200); glVertex2f(x + 80, -200);
    }
    glEnd();

    glColor3ub(150, 150, 150);
    glBegin(GL_QUADS);
    glVertex2f(-800, -200); glVertex2f(-600, -200); glVertex2f(-600, 100); glVertex2f(-800, 100);
    glVertex2f(600, -200);  glVertex2f(800, -200);  glVertex2f(800, 150);  glVertex2f(600, 150);
    glEnd();
}

void renderText(float x, float y, const char* text) {
    glColor3ub(255, 255, 255);
    glRasterPos2f(x, y);
    for (int i = 0; text[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    drawBackground();

    // Coins
    glColor3ub(255, 215, 0);
    for (int i = 0; i < NUM_COINS; i++) {
        if (coins[i].active) {
            drawFilledCircle(coins[i].x, coins[i].y, 20);
            glColor3ub(255, 255, 255);
            renderText(coins[i].x - 10, coins[i].y - 8, "$");
            glColor3ub(255, 215, 0);
        }
    }

    // Cute obstacles
    for (int i = 0; i < NUM_OBSTACLES; i++) {
        if (obstacles[i].active) {
            drawObstacle(obstacles[i].x, obstacles[i].y);
        }
    }

    drawPlane();

    // HUD
    std::stringstream ss;
    ss << "Score: " << currentScore << "   Lives: " << lives << "   Time: " << gameTime << "s   Speed: " << (int)coinSpeed;
    renderText(-950.0f, 550.0f, ss.str().c_str());
    renderText(-950.0f, 520.0f, "L-Click: Speed Up   R-Click: Speed Down");

    if (!gameRunning) {
        renderText(-350.0f, 100.0f, "GAME OVER!");
        std::stringstream final;
        final << "Final Score: " << currentScore << "   Lives Left: " << lives;
        renderText(-300.0f, 0.0f, final.str().c_str());
        renderText(-400.0f, -100.0f, "Press ESC to exit");
    }

    glutSwapBuffers();
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    gluOrtho2D(-1000, 1000, -600, 600);

    srand(time(NULL));

    for (int i = 0; i < NUM_COINS; i++) {
        coins[i].x = 1000.0f + (rand() % 1200);
        coins[i].y = (rand() % 1000) - 500;
        coins[i].active = true;
    }

    for (int i = 0; i < NUM_OBSTACLES; i++) {
        obstacles[i].x = 1500.0f + (rand() % 2000);  // Appear less often
        obstacles[i].y = (rand() % 1000) - 500;
        obstacles[i].active = true;
    }
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1000, 1000, -600, 600);
}

void idle() {
    if (!gameRunning) return;

    for (int i = 0; i < NUM_COINS; i++) {
        if (coins[i].active) {
            coins[i].x -= coinSpeed;
            if (coins[i].x < -1000) {
                coins[i].x = 1000.0f + (rand() % 800);
                coins[i].y = (rand() % 1000) - 500;
            }
        }
    }

    for (int i = 0; i < NUM_OBSTACLES; i++) {
        if (obstacles[i].active) {
            obstacles[i].x -= coinSpeed;
            if (obstacles[i].x < -1000) {
                obstacles[i].x = 1500.0f + (rand() % 2000);
                obstacles[i].y = (rand() % 1000) - 500;
            }
        }
    }

    for (int i = 0; i < NUM_COINS; i++) {
        if (coins[i].active) {
            float dx = coins[i].x - planeX;
            float dy = coins[i].y - planeY;
            if (dx * dx + dy * dy < 100 * 100) {
                currentScore += 10;
                playCoinSound();
                coins[i].x = 1000.0f + (rand() % 800);
                coins[i].y = (rand() % 1000) - 500;
            }
        }
    }

    for (int i = 0; i < NUM_OBSTACLES; i++) {
        if (obstacles[i].active) {
            float dx = obstacles[i].x - planeX;
            float dy = obstacles[i].y - planeY;
            if (dx * dx + dy * dy < 120 * 120) {
                lives--;
                playHitSound();
                obstacles[i].x = 1500.0f + (rand() % 2000);
                obstacles[i].y = (rand() % 1000) - 500;
                if (lives <= 0) {
                    gameRunning = false;
                    playGameOverSound();  // Game over sound!
                }
            }
        }
    }

    glutPostRedisplay();
}

void keyboard(unsigned char key, int, int) {
    if (!gameRunning && key != 27) return;

    float step = 35.0f;
    switch (key) {
        case 'w': case 'W': planeY += step; break;
        case 's': case 'S': planeY -= step; break;
        case 'a': case 'A': planeX -= step; break;
        case 'd': case 'D': planeX += step; break;
        case 27: exit(0);
    }

    if (planeX < -950) planeX = -950;
    if (planeX > 950)  planeX = 950;
    if (planeY < -550) planeY = -550;
    if (planeY > 550)  planeY = 550;

    glutPostRedisplay();
}

void mouse(int button, int state, int, int) {
    if (!gameRunning || state != GLUT_DOWN) return;

    if (button == GLUT_LEFT_BUTTON) {
        coinSpeed += 2.0f;
        if (coinSpeed > maxSpeed) coinSpeed = maxSpeed;
        playSpeedUpSound();
    }
    else if (button == GLUT_RIGHT_BUTTON) {
        coinSpeed -= 2.0f;
        if (coinSpeed < minSpeed) coinSpeed = minSpeed;
        playSpeedDownSound();
    }
    glutPostRedisplay();
}

void gameTimer(int) {
    if (gameTime > 0 && gameRunning) {
        gameTime--;
        glutTimerFunc(1000, gameTimer, 0);
    } else {
        if (gameRunning) {
            gameRunning = false;
            playGameOverSound();  // Also play when time ends
        }
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1400, 800);
    glutInitWindowPosition(100, 50);
    glutCreateWindow("Flight Dash - Final Version!");

    init();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutTimerFunc(1000, gameTimer, 0);

    std::cout << "=== FLIGHT DASH STARTED ===\n";
    std::cout << "WASD to move | Left Click: faster | Right Click: slower\n";
    std::cout << "Avoid the cute birds! Collect coins!\n";
    std::cout << "You have 3 lives and 60 seconds. Good luck!\n";

    glutMainLoop();
    return 0;
}
