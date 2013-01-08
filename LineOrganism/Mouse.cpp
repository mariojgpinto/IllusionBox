#include "Mouse.h"

//Funcao que trata do evento das teclas do rato
void mouseButton(int button, int state, int x, int y){
	yClick = (float)y;
   	xClick = (float)x;
  	zClick = (float)y;

	if (button == GLUT_LEFT_BUTTON){
		leftButton = (state == GLUT_DOWN) ? true : false;
	}

	if (button == GLUT_RIGHT_BUTTON){
		rightButton = (state == GLUT_DOWN) ? true : false;
	}

	if (button == GLUT_MIDDLE_BUTTON){
		middleButton = (state == GLUT_DOWN) ? true : false;
	}
}

void mouseMotion(int x, int y){
	//Middle button pressed
	if(middleButton){

	}
	//Left button pressed
	if(leftButton){

	}
	//Right button pressed
	if(rightButton){
		//Aproximar ou afastar de ponto de foco
		if(!flyMode){
			if(y > yClick) r+=0.2;
			if(y < yClick) r-= (r >= 2) ? 0.2 : 0.0;

			xClick = x;
			yClick = y;
			actualizaCamara();
		}
	}
}

//Funcao que trata do movimento do rato
void mousePassiveMotion(int x,int y){
	if(lock) {
		xClick = x;
		yClick = y;

		glutPostRedisplay();

		return;
	}
	if(x > xClick) //alpha -> horizontal
		alpha -= mouseStep;
	else{
		if(x < xClick)
			alpha += mouseStep;
	}

	if(flyMode){		
		if(y > yClick)
			beta -= (beta <= (-PI/2 + mouseStep + 0.01)) ? 0 : mouseStep;
		else{
			if(y < yClick)
				beta += (beta >= (PI/2 -mouseStep -0.01)) ? 0 : mouseStep;
		}

		if(!turn && beta>(PI/2)){
			turn = !turn;
			alpha += PI;
		}
	}
	else{ // Around the MyPoint
		if(y > yClick) //teta -> vertival
			beta -= (beta <= ( mouseStep + 0.01)) ? 0 : mouseStep;
		else{
			if(y < yClick){
				beta += (beta >= (PI -mouseStep -0.01)) ? 0 : mouseStep;	
			}
		}
	}

	//Actualização do Parâmetro
	xClick = x;
	yClick = y;

	actualizaCamara();
	//printf("(%.2f,%.2f)\n",alpha,beta);
	glutPostRedisplay();
}

void actualizaCamara(){
	if(flyMode){
		camAt[0] = camPos[0] + (r * cos(beta) * sin(alpha));
		camAt[1] = camPos[1] + (r * sin(beta));
		camAt[2] = camPos[2] + (r * cos(beta) * cos(alpha));
	}
	else{
		camPos[0] = camAt[0] + r * sin(beta) * sin(alpha);
		camPos[1] = camAt[1] + r * cos(beta);
		camPos[2] = camAt[2] + r * sin(beta) * cos(alpha);
	}
}