#include "Keyboard.h"

//funcao que trata dos eventos das teclas "especiais"
void specialKeys(int tecla, int x, int y) {
	switch (tecla) {
		/*case GLUT_KEY_F1:
			flyMode = !flyMode;
			actualizaValores();
			break;	*/
		case GLUT_KEY_F2:
			lock = !lock;
			break;
		case GLUT_KEY_UP:
			//specialKeys('w',x,y);
			pt[2]--;
			follow = true;
			break;
		case GLUT_KEY_LEFT:
			//specialKeys('a',x,y);
			pt[0]--;
			follow = true;
			break;
		case GLUT_KEY_DOWN:
			//specialKeys('s',x,y);
			pt[2]++;
			follow = true;
			break;
		case GLUT_KEY_RIGHT:
			//specialKeys('d',x,y);
			pt[0]++;
			follow = true;
			break;
		default:	break;
	}
	glutPostRedisplay();
}

//funcao que trata dos eventos das teclas "normais"
void normalKeys(unsigned char tecla, int x, int y) {

	switch (tecla) {
		// ESCape: terminate
		case 27:	
			exit (0); 
			break;
				case 'w':
			if(flyMode){
				camPos[0] += (keyStep * cos(beta) * sin(alpha));
				camPos[1] += (keyStep * sin(beta));
				camPos[2] += (keyStep * cos(beta) * cos(alpha));
				camAt[0] += (keyStep * cos(beta) * sin(alpha));
				camAt[1] += (keyStep * sin(beta));
				camAt[2] += (keyStep * cos(beta) * cos(alpha));
			}
			else{
				float norm[3];
				calcDirectionNorm(norm);
				
				camPos[0] += keyStep * norm[0];
				//camPos[1] += keyStep * norm[1];
				camPos[2] += keyStep * norm[2];
				
				camAt[0] += keyStep * norm[0];
				//camAt[1] += keyStep * norm[1];
				camAt[2] += keyStep * norm[2];
			}
			break;
		case 'd':
			if(flyMode){
				camPos[0] += (keyStep * cos(beta) * sin(alpha-PI/2));
				camPos[1] += (keyStep * sin(beta));
				camPos[2] += (keyStep * cos(beta) * cos(alpha-PI/2));
				camAt[0] += (keyStep * cos(beta) * sin(alpha-PI/2));
				camAt[1] += (keyStep * sin(beta));
				camAt[2] += (keyStep * cos(beta) * cos(alpha-PI/2));
			}
			else{
				calcDirectionNorm(camDir);
				float perp[3];
				perp[0] = -camDir[2];
				perp[1] = camDir[1];
				perp[2] = camDir[0];
				
				camPos[0] += keyStep * perp[0];
				//camPos[1] += perp[1];
				camPos[2] += keyStep * perp[2];
				
				camAt[0] += keyStep * perp[0];
				//camAt[1] = perp[1];
				camAt[2] += keyStep * perp[2];
			}
			break;
		case 'a':
			if(flyMode){
				camPos[0] -= (keyStep * cos(beta) * sin(alpha-PI/2));
				//camPos[1] -= (keyStep * sin(beta));
				camPos[2] -= (keyStep * cos(beta) * cos(alpha-PI/2));
				camAt[0] -= (keyStep * cos(beta) * sin(alpha-PI/2));
				//camAt[1] -= (keyStep * sin(beta));
				camAt[2] -= (keyStep * cos(beta) * cos(alpha-PI/2));
			}
			else{
				calcDirectionNorm(camDir);
				float perp[3];
				perp[0] = camDir[2];
				perp[1] = camDir[1];
				perp[2] = -camDir[0];

				normaliza(perp);
				
				camPos[0] += keyStep * perp[0];
				//camPos[1] += perp[1];
				camPos[2] += keyStep * perp[2];
				
				camAt[0] += keyStep * perp[0];
				//camAt[1] = perp[1];
				camAt[2] += keyStep * perp[2];
			}
			break;
		case 's':
			if(flyMode){
				camPos[0] -= (keyStep * cos(beta) * sin(alpha));
				//camPos[1] -= (keyStep * sin(beta));
				camPos[2] -= (keyStep * cos(beta) * cos(alpha));
				camAt[0] -= (keyStep * cos(beta) * sin(alpha));
				//camAt[1] -= (keyStep * sin(beta));
				camAt[2] -= (keyStep * cos(beta) * cos(alpha));
			}
			else{
				float norm[3];
				calcDirectionNorm(norm);
				
				camPos[0] -= keyStep * norm[0];
				//camPos[1] -= keyStep * norm[1];
				camPos[2] -= keyStep * norm[2];
				
				camAt[0] -= keyStep * norm[0];
				//camAt[1] -= keyStep * norm[1];
				camAt[2] -= keyStep * norm[2];
			}
			break;
		case 'q':
			if(flyMode){
				
			}
			else{
				camPos[1] += keyStep;
				camAt[1] += keyStep;
			}
			break;
		case 'z':
			if(flyMode){
				
			}
			else{
				camPos[1] -= keyStep;
				camAt[1] -= keyStep;
			}
			break;
		case '+':
			staticHigh+=staticStep;
			break;
		case '-':
			staticHigh-=staticStep;
			break;
		case '0':
			step+=0.1;
			break;
		case '9':
			step-=0.1;
			break;
		case 'g':
			grill = !grill;
			break;
		case 'r':
			randomGPoint = true;
			break;
		case ' ':
			restore++;
			break;
		case 'f':
			drawGravity = !drawGravity;
			break;
		case 'm':

			break;
		case 'n':

			break;
		default:	break;
	}
	glutPostRedisplay();
}

void actualizaValores(){
	if(flyMode){
		beta = (beta - PI/2);
		alpha += PI;
	}
	else{
		r = distancia(camPos,camAt);
		alpha = atan((camPos[0] - camAt[0])/(camPos[2] - camAt[2]));
		beta = acos((camPos[1] - camAt[1])/r);
	}
}