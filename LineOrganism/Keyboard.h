#ifndef _KEYBOARD
#define _KEYBOARD

#include "Tools.h"

extern bool lock;
extern float camPos[3];
extern float camAt[3];
extern float camUp[3];
extern float alpha, beta , r;
extern bool flyMode;
extern float keyStep;
extern float mouseStep;
extern float step;

extern double staticHigh;
extern double staticStep;

extern bool grill;
extern bool randomGPoint;
extern int restore;

extern bool follow;
extern double pt[];
extern bool drawGravity;

void specialKeys(int tecla, int x, int y);
void normalKeys(unsigned char tecla, int x, int y);
void actualizaValores();

#endif