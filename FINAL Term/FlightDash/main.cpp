/**
 * FLIGHT DASH: Aircraft Control and Obstacle Avoidance
 * --------------------------------------------------
 * Combined Source: Console Login + OpenGL Game Engine
 *
 * REQUIRED LIBRARIES:
 * 1. GLUT (Graphics)
 * 2. MySQL Connector/C (Database)
 * 3. WinMM (Sound/Multimedia)
 */

#include <windows.h>
#include <GL/glut.h>
#include <mysql.h>
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
#include <mmsystem.h> // Required for PlaySound

using namespace std;

// --- Linker Pragma (Works in some versions of MinGW) ---
#pragma comment(lib, "winmm.lib")

// --- Global Constants & State ---
const int MAX_COINS = 15;
const int MAX_BOMBS = 8;
const float PI = 3.14159265f;

// User Session
string currentUser = "Guest";
int userHighScore = 0;
int currentSessionScore = 0;
bool isGameOver = false;

// Plane & Objects
float flightX = -800.0f, flightY = 0.0f;
float coinX[MAX_COINS], coinY[MAX_COINS], coinActive[MAX_COINS];
float bombX[MAX_BOMBS], bombY[MAX_BOMBS], bombActive[MAX_BOMBS];
float cloudPos[5] = {960, 960, 960, 960, 960};
float cloudSpeeds[5] = {2.0f, 3.5f, 5.0f, 2.8f, 1.2f};

// --- Sound Logic ---
// Note: Ensure these .wav files exist in your "resource" folder
void playBGM() {
    PlaySound("resource/bgm.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

void playCoinSound() {
    PlaySound("resource/coin.wav", NULL, SND_FILENAME | SND_ASYNC);
}

void playGameOverSound() {
    PlaySound("resource/gameover.wav", NULL, SND_FILENAME | SND_ASYNC);
}

// --- Database Logic ---
void saveHighScore(int score, string username) {
    MYSQL* conn = mysql_init(0);
    conn = mysql_real_connect(conn, "127.0.0.1", "root", "", "flight_dash", 0, NULL, 0);
    if(conn) {
        stringstream ss;
        ss << "UPDATE user SET score = '" << score << "' WHERE username = '" << username << "'";
        mysql_query(conn, ss.str().c_str());
        mysql_close(conn);
    }
}

// --- Drawing Primitives ---
void drawFilledCircle(float x, float y, float r) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for(int i = 0; i <= 40; i++) {
        float angle = 2.0f * PI * i / 40.0f;
        glVertex2f(x + cos(angle) * r, y + sin(angle) * r);
    }
    glEnd();
}

void drawFighterPlane(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glRotatef(-90, 0, 0, 1);

    // Body (Gray)
    glColor3ub(120, 120, 120);
    glBegin(GL_POLYGON);
        glVertex2f(0, 120); glVertex2f(15, 60); glVertex2f(15, -80);
        glVertex2f(-15, -80); glVertex2f(-15, 60);
    glEnd();

    // Wings (Dark Gray)
    glColor3ub(80, 80, 80);
    glBegin(GL_TRIANGLES);
        glVertex2f(-15, 30); glVertex2f(-120, -10); glVertex2f(-15, -40);
        glVertex2f(15, 30); glVertex2f(120, -10); glVertex2f(15, -40);
    glEnd();

    // Cockpit (Blue)
    glColor3ub(0, 180, 220);
    drawFilledCircle(0, 40, 12);
    glPopMatrix();
}

// --- GLUT Callbacks ---
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Render Environment (Parallax Clouds)
    glColor3ub(255, 255, 255);
    for(int i=0; i<5; i++) drawFilledCircle(cloudPos[i], 300 - (i*150), 50 + (i*10));

    if (!isGameOver) {
        drawFighterPlane(flightX, flightY);

        // Render Collectibles
        for(int i=0; i<MAX_COINS; i++) if(coinActive[i]) {
            glColor3ub(255, 215, 0); drawFilledCircle(coinX[i], coinY[i], 15);
        }
        for(int i=0; i<MAX_BOMBS; i++) if(bombActive[i]) {
            glColor3ub(200, 20, 20); drawFilledCircle(bombX[i], bombY[i], 18);
        }
    } else {
        // Render Game Over Text
        glColor3f(1, 1, 1);
        string scoreMsg = "GAME OVER! SCORE: " + to_string(currentSessionScore);
        glRasterPos2f(-200, 0);
        for(char c : scoreMsg) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    glutSwapBuffers();
}

void update(int v) {
    if (!isGameOver) {
        // Cloud Parallax
        for(int i=0; i<5; i++) {
            cloudPos[i] -= cloudSpeeds[i];
            if(cloudPos[i] < -1100) cloudPos[i] = 1000;
        }

        // Collision Logic: Coin
        for(int i=0; i<MAX_COINS; i++) {
            if(coinActive[i]) {
                float dx = flightX - coinX[i], dy = flightY - coinY[i];
                if(sqrt(dx*dx + dy*dy) < 60) {
                    coinActive[i] = false;
                    currentSessionScore++;
                    playCoinSound();
                }
            }
        }

        // Collision Logic: Bomb
        for(int i=0; i<MAX_BOMBS; i++) {
            if(bombActive[i]) {
                float dx = flightX - bombX[i], dy = flightY - bombY[i];
                if(sqrt(dx*dx + dy*dy) < 50) {
                    isGameOver = true;
                    playGameOverSound();
                    if(currentSessionScore > userHighScore) saveHighScore(currentSessionScore, currentUser);
                }
            }
        }
    }
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

// --- Navigation Functions ---
void handleKeys(unsigned char key, int x, int y) {
    if(key == 'w' || key == 'W') flightY += 15;
    if(key == 's' || key == 'S') flightY -= 15;
    if(key == 'a' || key == 'A') flightX -= 15;
    if(key == 'd' || key == 'D') flightX += 15;
    if(key == 27) exit(0); // ESC
}

// --- Entry Points ---
void startMainGame(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Flight Dash");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-960, 960, -540, 540);

    playBGM(); // Start loop music

    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    glutKeyboardFunc(handleKeys);
    glutMainLoop();
}

void login() {
    system("cls");
    string u, p;
    cout << "--- FLIGHT DASH LOGIN --- Username: "; cin >> u;
    cout << "Password: "; cin >> p;

    MYSQL* conn = mysql_init(0);
    conn = mysql_real_connect(conn, "127.0.0.1", "root", "", "flight_dash", 0, NULL, 0);
    if(conn) {
        mysql_query(conn, "SELECT username, password, score FROM user");
        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row;
        while(row = mysql_fetch_row(res)) {
            if(u == row[0] && p == row[1]) {
                currentUser = u;
                userHighScore = atoi(row[2]);
                cout << "Success! Launching...";
                Sleep(500);
                startMainGame(__argc, __argv);
                return;
            }
        }
    }
    cout << "Invalid credentials!";
    system("pause");
}

int main(int argc, char** argv) {
    int choice;
    while(true) {
        system("cls");
        cout << "1. Login \n"
        cout << "2. Register \n"
        cout << "0. Exit \n"
        cout <<  "Choice: ";
        cin >> choice;
        if(choice == 1) login();
        else if(choice == 0) break;
    }
    return 0;
}
