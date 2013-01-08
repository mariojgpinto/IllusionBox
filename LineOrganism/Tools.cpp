#include "Tools.h"

void eixos(int size,float x,float y,float z){
	glPushMatrix();
	glTranslatef(x,y,z);
	glBegin(GL_LINES);
			glColor3f(BRANCO); 
			glVertex3f(size,0,0);
			glVertex3f(-size,0,0);
			
			glVertex3f(0,size,0);
			glVertex3f(0,-size,0);
			
			glVertex3f(0,0,size);
			glVertex3f(0,0,-size);
	glEnd();
	glPopMatrix();
}

void grelha(int scale){	
	int i;
	glPushMatrix();
	glColor3f(BRANCO);
	glBegin(GL_LINES);
		for(i=-scale;i<=scale;i+=5)
		{
			glVertex3f(-scale,0,i);
			glVertex3f(scale,0,i);
			glVertex3f(i,0,-scale);
			glVertex3f(i,0,scale);
		}
	glEnd();
	glPopMatrix();
}

void calcDirectionNorm(float vec[3]){
	camDir[0] = camAt[0] - camPos[0];
	camDir[1] = camAt[1] - camPos[1];
	camDir[2] = camAt[2] - camPos[2];

	vec[0] = camDir[0];
	vec[1] = camDir[1];
	vec[2] = camDir[2];

	normaliza(vec);
}

void calcDirectionNorm(double vec[3]){
	camDir[0] = camAt[0] - camPos[0];
	camDir[1] = camAt[1] - camPos[1];
	camDir[2] = camAt[2] - camPos[2];

	vec[0] = camDir[0];
	vec[1] = camDir[1];
	vec[2] = camDir[2];

	normaliza(vec);
}

void calcPerpendicularNorm(float vec[3]){
	camDir[0] = camAt[0] - camPos[0];
	camDir[1] = camAt[1] - camPos[1];
	camDir[2] = camAt[2] - camPos[2];

	vec[0] = -camDir[2];
	vec[1] = camDir[1];
	vec[2] = camDir[0];

	normaliza(vec);
}

void calcPerpendicularNorm(double vec[3]){
	camDir[0] = camAt[0] - camPos[0];
	camDir[1] = camAt[1] - camPos[1];
	camDir[2] = camAt[2] - camPos[2];

	vec[0] = -camDir[2];
	vec[1] = camDir[1];
	vec[2] = camDir[0];

	normaliza(vec);
}

void normaliza(float vec[3]){
	float _v = sqrt(pow(vec[0],2) + pow(vec[1],2) + pow(vec[2],2));
	vec[0] = (vec[0] / _v);
	vec[1] = (vec[1] / _v);
	vec[2] = (vec[2] / _v);
}

void normaliza(double vec[3]){
	double _v = sqrt(pow(vec[0],2) + pow(vec[1],2) + pow(vec[2],2));
	vec[0] = (vec[0] / _v);
	vec[1] = (vec[1] / _v);
	vec[2] = (vec[2] / _v);
}

float distancia(float vec1[3], float vec2[3]){
	return sqrt(pow(vec1[0] - vec2[0],2) + 
				pow(vec1[1] - vec2[1],2) + 
				pow(vec1[2] - vec2[2],2));
}

float distancia(double vec1[3], double vec2[3]){
	return sqrt(pow(vec1[0] - vec2[0],2) + 
				pow(vec1[1] - vec2[1],2) + 
				pow(vec1[2] - vec2[2],2));
}


int randomInt(int min, int max){
	return rand() % (max-min) + min;
}

float randomDouble(double min, double max){
	return (rand() / (static_cast<float>(RAND_MAX) + 1.0)) * (max - min) + min;
}

int maxPos(int *vec, int cap){
	int max = 0;

	for(int i = 0 ; i < cap ; i++){
		if(vec[i] > vec[max]) max = i;
	}

	return max;
}

void initializeArray(int* a, int cap){
	if(a){
		for(int i = 0 ; i < cap ; a[i++] = 0);
	}
}

float media(float i1, float i2){
	float m = ((i1+i2)/2.0);
	
	return m;
}