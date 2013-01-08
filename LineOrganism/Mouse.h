#ifndef _MOUSE
#define _MOUSE

#include "Tools.h"

static bool leftButton = false;
static bool middleButton = false;
static bool rightButton = false;
static float yClick;
static float xClick;
static float zClick = 17.321;
static int width = glutGet(GLUT_SCREEN_WIDTH);
static int height = glutGet(GLUT_SCREEN_HEIGHT);

extern bool lock;
extern float alpha, beta, r;
extern float camPos[3];
extern float camDir[3];
extern float camAt[3];
extern float camUp[3];
extern bool turn;
extern bool flyMode;
extern float mouseStep;
extern float keyStep;

void mouseButton(int button, int state, int x, int y);
void mouseMotion(int x, int y);
void mousePassiveMotion(int x,int y);
void actualizaCamara();

#endif