#ifndef _VARIABLES
#define _VARIABLES

/*
 * Mouse and Keyboard
 */
bool lock = true;
float camPos[3] = {0.0,96.0,0.1};
float camAt[3] = {0.0,0.0,0.0};
float camUp[3] = {0.0,1.0,0.0};
float camDir[3] = {0.0,0.0,-1.0};
float alpha = 0.0f, beta = 0.0f, r = 100.0f;
bool turn = false; // Mouse only
bool flyMode = false;
float mouseStep = 0.08f;
float keyStep = 2.5f;
float step = 10.1f;
double staticHigh = 110.0;
double staticStep = 1.0;
bool grill = true;
bool randomGPoint = false;
int restore = 0;
bool drawGravity = false;

bool follow = false;
double pt[3] = {0.0,0.0,0.0};

#endif