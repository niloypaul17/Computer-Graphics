#define _USE_MATH_DEFINES
#include <windows.h>
#include <GL/glut.h>
#include <cmath>
#include <cstdlib>

bool isGhostVisible = false;
float flicker = 1.0f;
float flickerStep = -0.02f;

void drawGhost(float x, float y) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    float alpha = 0.3f+0.2f*sin(glutGet(GLUT_ELAPSED_TIME)/200.0);
    glColor4f(1.0f, 1.0f, 1.0f, alpha);

    // Body rectangle
    glBegin(GL_QUADS);
        glVertex2f(x-30, y-50);
        glVertex2f(x+30, y-50);
        glVertex2f(x+30, y+50);
        glVertex2f(x-30, y+50);
    glEnd();

    // Wavy bottom (small quads)
    for(int i=-30;i<=30;i+=15){
        glBegin(GL_QUADS);
            glVertex2f(x+i-10, y-50-15);
            glVertex2f(x+i+10, y-50-15);
            glVertex2f(x+i+10, y-50);
            glVertex2f(x+i-10, y-50);
        glEnd();
    }

    // Head rectangle
    glBegin(GL_QUADS);
        glVertex2f(x-20, y+50);
        glVertex2f(x+20, y+50);
        glVertex2f(x+20, y+75);
        glVertex2f(x-20, y+75);
    glEnd();

    // Eyes as small rectangles
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(x-12, y+60);
        glVertex2f(x-7, y+60);
        glVertex2f(x-7, y+65);
        glVertex2f(x-12, y+65);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(x+7, y+60);
        glVertex2f(x+12, y+60);
        glVertex2f(x+12, y+65);
        glVertex2f(x+7, y+65);
    glEnd();

    glDisable(GL_BLEND);
}

void display2() {
    glClear(GL_COLOR_BUFFER_BIT);

    float brightness = isGhostVisible ? flicker : 1.0f;

    // Walls
    glColor3f(0.9f*brightness,0.9f*brightness,0.9f*brightness);
    glBegin(GL_QUADS);
        glVertex2f(-900,-500);
        glVertex2f(900,-500);
        glVertex2f(900,500);
        glVertex2f(-900,500);
    glEnd();

    // Floor
    glColor3f(0.7f*brightness,0.5f*brightness,0.3f*brightness);
    glBegin(GL_QUADS);
        glVertex2f(-900,-900);
        glVertex2f(900,-900);
        glVertex2f(900,-500);
        glVertex2f(-900,-500);
    glEnd();

    // Ceiling
    glColor3f(0.8f*brightness,0.8f*brightness,0.8f*brightness);
    glBegin(GL_QUADS);
        glVertex2f(-900,500);
        glVertex2f(900,500);
        glVertex2f(900,900);
        glVertex2f(-900,900);
    glEnd();

    // Window
    if(isGhostVisible) {
            glColor3f(0.1f,0.1f,0.1f);
    }
    else {
            glColor3f(0.5f,0.8f,1.0f);
    }
    glBegin(GL_QUADS);
        glVertex2f(300,50);
        glVertex2f(700,50);
        glVertex2f(700,450);
        glVertex2f(300,450);
    glEnd();

    // Window grid
    glColor3f(0,0,0);
    glBegin(GL_LINES);
        glVertex2f(500,50);
        glVertex2f(500,450);
        glVertex2f(300,250);
        glVertex2f(700,250);
    glEnd();

    // Picture frame
    glColor3f(0.5f,0.3f,0.1f);
    glBegin(GL_QUADS);
        glVertex2f(-700,50);
        glVertex2f(-300,50);
        glVertex2f(-300,350);
        glVertex2f(-700,350);
    glEnd();

    glColor3f(1.0f,0.5f,0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-680,70);
        glVertex2f(-320,70);
        glVertex2f(-320,330);
        glVertex2f(-680,330);
    glEnd();

    glColor3f(0.0f,0.0f,0.5f);
    glBegin(GL_QUADS);
        glVertex2f(-680,150);
        glVertex2f(-320,150);
        glVertex2f(-320,170);
        glVertex2f(-680,170);
    glEnd();

    // Table
    glColor3f(0.6f,0.3f,0.0f);
    glBegin(GL_QUADS);
        glVertex2f(500,-500);
        glVertex2f(850,-500);
        glVertex2f(850,-300);
        glVertex2f(500,-300);
    glEnd();

    glColor3f(0.4f,0.2f,0.0f);
    glBegin(GL_QUADS);
        glVertex2f(510,-700);
        glVertex2f(530,-700);
        glVertex2f(530,-500);
        glVertex2f(510,-500);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(820,-700);
        glVertex2f(840,-700);
        glVertex2f(840,-500);
        glVertex2f(820,-500);
    glEnd();

    // Sofa
    glColor3f(0.7f,0.1f,0.1f);
    glBegin(GL_QUADS);
        glVertex2f(-800,-700);
        glVertex2f(-200,-700);
        glVertex2f(-200,-500);
        glVertex2f(-800,-500);
    glEnd();
    glColor3f(0.8f,0.2f,0.2f);
    glBegin(GL_QUADS);
        glVertex2f(-800,-500);
        glVertex2f(-200,-500);
        glVertex2f(-200,-400);
        glVertex2f(-800,-400);
    glEnd();
    // Sofa arms
    glColor3f(0.4f,0.1f,0.1f);
    glBegin(GL_QUADS);
        glVertex2f(-820,-700);
        glVertex2f(-800,-700);
        glVertex2f(-800,-400);
        glVertex2f(-820,-400);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(-200,-700);
        glVertex2f(-180,-700);
        glVertex2f(-180,-400);
        glVertex2f(-200,-400);
    glEnd();

    // Chair
    glColor3f(0.5f,0.3f,0.1f);
    glBegin(GL_QUADS);
        glVertex2f(600,-650);
        glVertex2f(700,-650);
        glVertex2f(700,-500);
        glVertex2f(600,-500);
    glEnd();
    glColor3f(0.6f,0.4f,0.2f);
    glBegin(GL_QUADS);
        glVertex2f(600,-500);
        glVertex2f(700,-500);
        glVertex2f(700,-420);
        glVertex2f(600,-420);
    glEnd();

    // TV centered
    glColor3f(0,0,0);
    glBegin(GL_QUADS);
        glVertex2f(-50,150);
        glVertex2f(150,150);
        glVertex2f(150,300);
        glVertex2f(-50,300);
    glEnd();
    glColor3f(0.1f,0.1f,0.1f);
    glBegin(GL_QUADS);
        glVertex2f(-45,155);
        glVertex2f(145,155);
        glVertex2f(145,295);
        glVertex2f(-45,295);
    glEnd();

    // Bulbs
    int positions[5] = {-600,-300,0,300,600};
    for(int i=0;i<5;i++){
        glColor3f(0.2f,0.2f,0.2f);
        glBegin(GL_QUADS);
            glVertex2f(positions[i]-5,880);
            glVertex2f(positions[i]+5,880);
            glVertex2f(positions[i]+5,850);
            glVertex2f(positions[i]-5,850);
        glEnd();
        glColor3f(1.0f,1.0f,0.6f);
        glBegin(GL_QUADS);
            glVertex2f(positions[i]-20,840);
            glVertex2f(positions[i]+20,840);
            glVertex2f(positions[i]+20,860);
            glVertex2f(positions[i]-20,860);
        glEnd();
    }

    // Fan
    float angle = glutGet(GLUT_ELAPSED_TIME)/5.0f;
    glPushMatrix();
    glTranslatef(0,800,0);
    glRotatef(angle,0,0,1);
    glColor3f(0.2f,0.2f,0.2f);
    glBegin(GL_QUADS);
        glVertex2f(-100,-10);
        glVertex2f(100,-10);
        glVertex2f(100,10);
        glVertex2f(-100,10);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(-10,-100);
        glVertex2f(10,-100);
        glVertex2f(10,100);
        glVertex2f(-10,100);
    glEnd();
    glPopMatrix();
    glColor3f(0.1f,0.1f,0.1f);
    glBegin(GL_QUADS);
        glVertex2f(-5,800);
        glVertex2f(5,800);
        glVertex2f(5,850);
        glVertex2f(-5,850);
    glEnd();

    // Ghost
    if(isGhostVisible) drawGhost(500,200);

    glFlush();
}


float boyX = -900;
float boyY = -690;
float speed = 0.50f;
bool isMoving = true;

const int NUM_STARS = 100;
int starX[NUM_STARS], starY[NUM_STARS];

const int NUM_FIREFLIES = 80;
int fireflyX[NUM_FIREFLIES], fireflyY[NUM_FIREFLIES];

const int NUM_GRASS = 100;
float grassBaseX[NUM_GRASS], grassBaseY[NUM_GRASS];
float grassTipX[NUM_GRASS], grassTipY[NUM_GRASS];

bool lightOn = false;
bool boyVisible = true;
float lightOscillate = 0.0f;

// cars positions
float carX[5] = {-1200, -1500, -1800, -2100, -2500};
float carSpeed[5] = {0.8f, 1.0f, 0.6f, 0.85f, 0.65f};

// cloud positions and oscillation
float cloudX[4] = {-800, -200, 400, 900};
float cloudY[4] = {600, 650, 620, 580};
float cloudDir[4] = {0.02f, 0.01f, 0.015f, 0.018f};

// boy
void boy(float a, float b){
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex2f(20+a,30+b);
    glVertex2f(30+a,40+b);
    glVertex2f(40+a,30+b);
    glVertex2f(30+a,20+b);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex2f(25+a,28+b);
    glVertex2f(27+a,30+b);
    glVertex2f(25+a,32+b);
    glVertex2f(23+a,30+b);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex2f(33 + a, 28 + b);
    glVertex2f(35 + a, 30 + b);
    glVertex2f(33 + a, 32 + b);
    glVertex2f(31 + a, 30 + b);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(.73, .36, .36);
    glVertex2f(20 + a, 20 + b);
    glVertex2f(40 + a, 20 + b);
    glVertex2f(40 + a, -20 + b);
    glVertex2f(20 + a, -20 + b);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex2f(22 + a, -20 + b);
    glVertex2f(27 + a, -20 + b);
    glVertex2f(27 + a, -40 + b);
    glVertex2f(22 + a, -40 + b);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex2f(33 + a, -20 + b);
    glVertex2f(38 + a, -20 + b);
    glVertex2f(38 + a, -40 + b);
    glVertex2f(33 + a, -40 + b);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(20 + a, 10 + b);
    glVertex2f(10 + a, 0 + b);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(40 + a, 10 + b);
    glVertex2f(50 + a, 0 + b);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(50 + a, 0 + b);
    glVertex2f(50 + a, 50 + b);
    glEnd();
}

// balloon
void ballon(float a, float b){
    glBegin(GL_POLYGON);
    glColor3f(0.7,0.5,0.7);
    for (int i=0;i<360;i++){
        float theta=i*3.1416/180;
        glVertex2f(50+a+15*cos(theta),65+b+20*sin(theta));
    }
    glEnd();
}

// circle utility
void drawCircle(float cx, float cy, float r, int segments){
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for(int i=0;i<=segments;i++){
        float angle =2.0f*M_PI*i/segments;
        glVertex2f(cx + r*cos(angle), cy + r*sin(angle));
    }
    glEnd();
}

// moon
void drawMoon(){
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(600, 700, 100, 100);
    glColor3f(0.0f, 0.0f, 0.5f);
    drawCircle(650, 730, 100, 100);
}

// stars
void drawStars(){
    glPointSize(3.0);
    glBegin(GL_POINTS);
    glColor3f(1.0f,1.0f,1.0f);
    for(int i=0;i<NUM_STARS;i++){
        glVertex2f(starX[i], starY[i]);
    }
    glEnd();
}

// clouds
void drawCloud(float x, float y){
    glColor3f(1.0f,1.0f,1.0f);
    drawCircle(x, y, 30, 30);
    drawCircle(x + 30, y + 10, 40, 30);
    drawCircle(x + 60, y, 30, 30);
}

// realistic cars
void drawCar(float x, float y, float width, float height, float r, float g, float b){
    glColor3f(r,g,b);
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y + height*0.6);
        glVertex2f(x, y + height*0.6);
    glEnd();

    glColor3f(0.8f,0.8f,0.8f);
    glBegin(GL_QUADS);
        glVertex2f(x + width*0.1, y + height*0.6);
        glVertex2f(x + width*0.4, y + height*0.6);
        glVertex2f(x + width*0.4, y + height);
        glVertex2f(x + width*0.1, y + height);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(x + width*0.6, y + height*0.6);
        glVertex2f(x + width*0.9, y + height*0.6);
        glVertex2f(x + width*0.9, y + height);
        glVertex2f(x + width*0.6, y + height);
    glEnd();

        glColor3f(0.0f,0.0f,0.0f);
    drawCircle(x + width*0.2, y, height*0.2, 20);
    drawCircle(x + width*0.8, y, height*0.2, 20);
}

// houses (original)
void drawHouse() {
    glColor3f(0.0f, 0.0f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(-900, -600);
    glVertex2f(-450, -600);
    glVertex2f(-450, -300);
    glVertex2f(-900, -300);
    glEnd();

    glColor3f(0.1f, 0.1f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(-450, -600);
    glVertex2f(-450, -300);
    glVertex2f(-190, -300);
    glVertex2f(-190, -600);
    glEnd();

    glColor3f(0.2f, 0.2f, 0.8f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-950, -300);
    glVertex2f(-700, -100);
    glVertex2f(-450, -300);
    glEnd();

    glColor3f(0.3f, 0.3f, 0.9f);
    glBegin(GL_QUADS);
    glVertex2f(-700, -100);
    glVertex2f(-500,-100);
    glVertex2f(-150,-300);
    glVertex2f(-450, -300);
    glEnd();

    glColor3f(1.0f, 0.9f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(-240, -600);
    glVertex2f(-320, -600);
    glVertex2f(-320, -400);
    glVertex2f(-240, -400);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(-820, -500);
    glVertex2f(-740, -500);
    glVertex2f(-740, -400);
    glVertex2f(-820, -400);
    glEnd();
}

// trees (original)
void drawTree() {
    glColor3f(0.3f, 0.2f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(-30, -600);
        glVertex2f( 30, -600);
        glVertex2f( 30, -400);
        glVertex2f(-30, -400);
    glEnd();

    glColor3f(0.0f, 0.6f, 0.3f);
    glBegin(GL_QUADS);
        glVertex2f(-100, -300);
        glVertex2f( 100, -300);
        glVertex2f( 100, -240);
        glVertex2f(-100, -240);
    glEnd();

    glColor3f(0.0f, 0.5f, 0.3f);
    glBegin(GL_QUADS);
        glVertex2f(-150, -300);
        glVertex2f( 150, -300);
        glVertex2f( 150, -440);
        glVertex2f(-150, -440);
    glEnd();

    glColor3f(0.0f, 0.5f, 0.25f);
    glBegin(GL_QUADS);
        glVertex2f(-80, -240);
        glVertex2f( 80, -240);
        glVertex2f( 80, -180);
        glVertex2f(-80, -180);
    glEnd();

    glColor3f(0.0f, 0.4f, 0.2f);
    glBegin(GL_QUADS);
        glVertex2f(-60, -180);
        glVertex2f( 60, -180);
        glVertex2f( 60, -120);
        glVertex2f(-60, -120);
    glEnd();
}

// grass + fireflies (original)
void drawGrass() {
    glLineWidth(2.0);
    glBegin(GL_LINES);
    for(int i=0;i<NUM_GRASS;i++){
        glColor3f(0.0f, 0.8f, 0.2f);
        glVertex2f(grassBaseX[i], grassBaseY[i]);
        glVertex2f(grassTipX[i], grassTipY[i]);
    }
    glEnd();

    glPointSize(4.0);
    glBegin(GL_POINTS);
    for(int i=0;i<NUM_GRASS;i++){
        glColor3f(1.0f,1.0f,0.0f);
        glVertex2f(grassTipX[i], grassTipY[i]);
    }
    glEnd();

    glPointSize(5.0);
    glBegin(GL_POINTS);
    for(int i=0;i<NUM_FIREFLIES;i++){
        glColor3f(1.0f,1.0f,0.0f);
        glVertex2f(fireflyX[i], fireflyY[i]);
    }
    glEnd();
}

// light under tree (original)
void drawLight() {
    if (lightOn) {
        float flicker = 4.0f * sin(lightOscillate);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        float sourceX = 500.0f + flicker;
        float sourceY = 120.0f;

        glBegin(GL_TRIANGLES);
        glColor4f(1.0f, 1.0f, 0.5f, 0.35f);
        glVertex2f(sourceX, sourceY);
        glVertex2f(sourceX - 300, -600.0f);
        glVertex2f(sourceX + 300, -600.0f);
        glEnd();

        glDisable(GL_BLEND);
    }
}

void display1() {
    glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // ground
    glBegin(GL_QUADS);
    glColor3f(0.06f, 0.06f, 0.12f);
    glVertex2d(-1000,-700);
    glVertex2d(-1000,-1000);
    glVertex2d(1000,-1000);
    glVertex2d(1000,-700);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.25f,0.15f, 0.15f);
    glVertex2d(-1000,-250);
    glVertex2d(1000,-250);
    glVertex2d(1000,-700);
    glVertex2d(-1000,-700);
    glEnd();

    glPushMatrix();
    glTranslated(100,0,0);
    glScalef(0.67f, 0.67f, 1.0f);
    drawHouse();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-100,0,0);
    drawHouse();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(300.0f, 80.0f, 0.0f);
    glScalef(0.75f, 0.75f, 1.0f);
    drawTree();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(500.0f, 160.0f, 0.0f);
    glScalef(0.85f, 0.85f, 1.0f);
    drawTree();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(700.0f, 80.0f, 0.0f);
    glScalef(0.55f, 0.55f, 1.0f);
    drawTree();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(900.0f, 160.0f, 0.0f);
    glScalef(0.75f, 0.75f, 1.0f);
    drawTree();
    glPopMatrix();
    glPushMatrix();
    glTranslated(1100, -50, 0);
    glScalef(0.75f, 0.8f, 1.0f);
    drawHouse();
    glPopMatrix();

    drawStars();
    drawMoon();
    drawGrass();

    // clouds
    for(int i=0;i<4;i++) {
            drawCloud(cloudX[i], cloudY[i]);
    }

    // cars on road
    if(lightOn){
        for(int i=0;i<5;i++){
            glPushMatrix();
            glTranslated(0,-80,0);
            drawCar(carX[i], -650, 120 + i*10, 50 + i*5, 1.0f-(i*0.2), 0.0f+(i*0.2), 0.0f+(i*0.2));
            glPopMatrix();
        }
    }

    if(boyVisible){
        glPushMatrix();
        glTranslatef(boyX,boyY,0);
        glScalef(2.0f,2.0f,1.0f);
        boy(0,0);
        ballon(0,0);
        glPopMatrix();
    }

    glPushMatrix();
    glTranslated(-600,-370,0);
    drawLight();
    glPopMatrix();

    glFlush();
}

void keyboard(unsigned char key, int x, int y){
    if(key==32) isMoving = !isMoving;
    if(key=='z'||key=='Z'){ lightOn = !lightOn; boyVisible = !lightOn; }
}

void specialKeys(int key,int x,int y){
    if(key==GLUT_KEY_LEFT) {
            boyX -= 10;
    }
    if(key==GLUT_KEY_RIGHT) {
            boyX += 10;
    }
}

void idle(){
    if(isMoving && boyVisible){
        boyX += speed;
        if(boyX>1000) {
                boyX=-1000;
        }
    }
    if(lightOn){
        for(int i=0;i<5;i++){
            carX[i]+=carSpeed[i];
            if(carX[i]>1200) carX[i]=-1200;
        }
    }

    for(int i=0;i<4;i++){
        cloudX[i]+=0.1f;
        cloudY[i]+=cloudDir[i];
        if(cloudY[i]>650||cloudY[i]<550) cloudDir[i]*=-1;
        if(cloudX[i]>1200) cloudX[i]=-1200;
    }

    if(isGhostVisible){
        flicker += flickerStep;
        if(flicker < 0.7f || flicker > 1.0f) flickerStep = -flickerStep;
    }
    lightOscillate += 0.1f; // Update oscillation for light flicker

    glutPostRedisplay();
}

void init(){
    gluOrtho2D(-1000,1000,-1000,1000);
    for(int i=0;i<NUM_STARS;i++){ starX[i]=-950 + rand()%1900; starY[i]=400 + rand()%400; }
    for(int i=0;i<NUM_FIREFLIES;i++){ fireflyX[i]=-900 + rand()%1800; fireflyY[i]=-600 + rand()%400; }
    for(int i=0;i<NUM_GRASS;i++){
        grassBaseX[i]=-1000 + rand()%2000;
        grassBaseY[i]=-700 + rand()%50;
        grassTipX[i]=grassBaseX[i]+(rand()%10 - 5);
        grassTipY[i]=grassBaseY[i]+30 + rand()%20;
    }
}

bool useDisplay1 = true;

// TIMER FUNCTION
void switchDisplay(int value){
    useDisplay1 = !useDisplay1; // Toggle between scenes
    glutTimerFunc(10000, switchDisplay, 0); // Repeat every 10 seconds
}

// MODIFY DISPLAY FUNCTION (DO NOT TOUCH display1/display2)
void display(){
    if(useDisplay1) display1();
    else display2();
}

int main(int argc,char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(1200,800);
    glutCreateWindow("Night Scene with Realistic Cars and Haunted Room");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutIdleFunc(idle);

    glutTimerFunc(10000, switchDisplay, 0); // switch after 10 sec

    glutMainLoop();
    return 0;
}
