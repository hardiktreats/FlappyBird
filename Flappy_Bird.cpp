#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <GL/glut.h>
#include <bits/stdc++.h>
#include <string.h>
using namespace std;
int difficulty;
// Window dimensions
const int WIDTH = 750, HEIGHT = 480;
// Bird radius and position
const int BIRD_RADIUS = 25;
const int BIRD_X = WIDTH / 4;
int birdY = HEIGHT / 2;
// Pipe dimensions and position
const int PIPE_WIDTH = 40, PIPE_HEIGHT = 300, PIPE_GAP = 200;
const int PIPE_SPEED = 3;
int pipeX = WIDTH, pipeGapY;
// Game variables
bool isGameOver = false;
//int score = 0;
// Vector to store previous pipe positions
vector<int> pipeYPositions;
// Function to draw a circle
void drawCircle(int x, int y, int r) {
    glBegin(GL_TRIANGLE_FAN);
    for(int i = 0; i <= 360; i++) {
        glVertex2f(x + r * cos(i * M_PI / 180.0), y + r * sin(i * M_PI / 180.0));
    }
    glEnd();
}
void drawEye(int x, int y, int r) {
    glBegin(GL_TRIANGLE_FAN);
    for(int i = 0; i <= 360; i++) {
        glVertex2f(x + r * cos(i * M_PI / 180.0), y + r * sin(i * M_PI / 180.0));
    }
    glEnd(); 
}
void drawBeak(int x, int y, int r) {
    glBegin(GL_TRIANGLES);
    for(int i = 0; i <= 360; i++) {
        glVertex2f(7+(x + r * cos(i * M_PI / 180.0)), (y + r*sin(i * M_PI / 180.0) )-7);
        glVertex2f(12+(x + r * cos(i * M_PI / 180.0)), (y + r * sin(i * M_PI / 180.0))-4);
        glVertex2f(7+(x + r * cos(i * M_PI / 180.0)), -1+(y + r * sin(i * M_PI / 180.0)));
    }
    glEnd(); 
}
void drawWings(int x, int y, int r) {
    glBegin(GL_LINES);
    for(int i = 0; i <= 360; i++) {
        glVertex2f(12+(x + r * cos(i * M_PI / 180.0)), (y + r * sin(i * M_PI / 180.0))-4);
        glVertex2f(17+(x + r * cos(i * M_PI / 180.0)), -1+(y + r * sin(i * M_PI / 180.0)));
        glVertex2f(17+(x + r * cos(i * M_PI / 180.0)), -1+(y + r * sin(i * M_PI / 180.0)));
    }
    glEnd(); 
}
// Function to draw a rectangle
void drawRectangle(int x1, int y1, int x2, int y2) {
    glBegin(GL_QUADS);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();
}
// Function to draw the bird
void drawBird() {
    glColor3f(1.0, 1.0, 0.0);
    drawCircle(BIRD_X, birdY, BIRD_RADIUS);
    glColor3f(0.0, 0.0, 0.0);
    drawEye(11+BIRD_X, 7+birdY, BIRD_RADIUS/6);
    glColor3f(1.0, 0.0, 0.0 );
    drawBeak(18+BIRD_X, 4+birdY, BIRD_RADIUS/6);
    glColor3f(0.0, 0.0, 0.0);
    drawWings(-25+BIRD_X, -22+birdY, BIRD_RADIUS/6);
    glColor3f(0.0, 0.0, 0.0);
    drawWings(-5+BIRD_X, -22+birdY, BIRD_RADIUS/6);
}
// Function to draw a single pipe
void drawPipe(int y){
    glColor3f(0.3, 1.0, 0.0);//Color of PIPES
    drawRectangle(pipeX, 0, pipeX + PIPE_WIDTH, 50+y); //bottom pipe
    drawRectangle(pipeX, y + PIPE_GAP+10, pipeX + PIPE_WIDTH, HEIGHT); //above pipe
}
// Function to draw all pipes
void drawPipes(){
    for(int i = 0; i < pipeYPositions.size(); i++) {
        drawPipe(pipeYPositions[i]);
    }
}
// Function to update the bird's position
void updateBird() {
    if(isGameOver) {
        return;
    }
    if(birdY > BIRD_RADIUS) {
        birdY -= difficulty;
    } else {
        isGameOver = true;
    }
}
// Function to update the pipe's position and spawn new pipes
void updatePipes() {
    if(isGameOver) {
        return;
    }
    pipeX -= PIPE_SPEED;
    if(pipeX < -PIPE_WIDTH) {
        pipeX = WIDTH;
        pipeGapY = rand() % (HEIGHT - PIPE_HEIGHT - PIPE_GAP);
        pipeYPositions.push_back(pipeGapY);
    }
    for(int i = 0; i < pipeYPositions.size(); i++) {
        if(pipeX + PIPE_WIDTH > BIRD_X - BIRD_RADIUS && pipeX < BIRD_X + BIRD_RADIUS) {
            if(birdY - BIRD_RADIUS < pipeYPositions[i] || birdY + BIRD_RADIUS > pipeYPositions[i] + PIPE_GAP) {
                isGameOver = true;
                break;
            }
        }
    }
    if(!isGameOver && pipeX + PIPE_WIDTH < BIRD_X - BIRD_RADIUS && !pipeYPositions.empty()) {
        pipeYPositions.erase(pipeYPositions.begin());
	}
}
// Function to draw the score
void Name(){
    glColor3f(0.0, 0.0, 0.0);
    glRasterPos2i(10, 10);
    string scoreStr = "FLAPPY BIRD\nHardikDhanjal-102003329\nShrey-102003208\nGurtaranSingh-102003220";
    for(int i = 0; i < scoreStr.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, scoreStr[i]);
    }
}
// Function to display the game
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawBird();
    drawPipes();
    Name();
    glutSwapBuffers();
}
// Function to update the game
void update(int value) {
    updateBird();
    updatePipes();
    glutPostRedisplay();
    glutTimerFunc(25, update, 0);
}
// Function to handle keyboard input
void keyboard(unsigned char key, int x, int y) {
    if(key == 32) {
        birdY += 50;
    } 
	else if(key == 'r' || key == 'R') {
        pipeYPositions.clear();
        pipeX = WIDTH;
        isGameOver = false;
        birdY = HEIGHT / 2;
    }
}
// Function to initialize OpenGL
void init() {
    glClearColor(0.0, 0.6, 0.8, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WIDTH, 0, HEIGHT);
}
// Main function
int main(int argc, char** argv) {
    srand(time(NULL));
    cout<<"Enter Level 1-10"<<endl;
    cin>>difficulty;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Flappy Bird");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    init();
    glutTimerFunc(25, update, 0);
    glutMainLoop();
    cout<<"FLAPPY BIRD"<<endl;
    return 0;
}

