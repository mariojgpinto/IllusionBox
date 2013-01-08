#ifndef _TOOLS
#define _TOOLS


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <GL/glew.h>	
#include <GL/glut.h>
//#include <cxtypes.h>
#include <time.h>

#include "Colors.h"

#define PI 3.14159265

extern float camPos[3];
extern float camDir[3];
extern float camAt[3];
extern float camUp[3];

void eixos(int size,float x,float y,float z);
void grelha(int scale);

void normaliza(double vec[3]);
float distancia(double vec1[3], double vec2[3]);
void calcDirectionNorm(double vec[3]);
void calcPerpendicularNorm(double vec[3]);

void normaliza(float vec[3]);
float distancia(float vec1[3], float vec2[3]);
void calcDirectionNorm(float vec[3]);
void calcPerpendicularNorm(float vec[3]);

int randomInt(int min, int max);
float randomDouble(double min, double max);
float media(double i1, double i2);
float media(float i1, float i2);

int maxPos(int *vec, int cap);
void initializeArray(int* a, int cap);

#endif