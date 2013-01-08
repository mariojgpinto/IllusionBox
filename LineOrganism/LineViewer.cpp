#include "LineViewer.h"

LineViewer* instance;
MyTimer* timer;

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set the correct perspective
	gluPerspective(45,ratio,2,2500);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void renderScene(void) {
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	gluLookAt(camPos[0],camPos[1],camPos[2], 
			  camAt[0],camAt[1],camAt[2],
			  camUp[0],camUp[1],camUp[2]);
	
	GLfloat amb[3] = {0.3, 0.3, 0.3};
	GLfloat diff[3] = {1.0, 1.0, 1.0};
	GLfloat pos[4] = {0.0, 10.0 ,0.0, 1.0};

	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);

	if(lock){
		camPos[0] = .0;
		camPos[1] = staticHigh;
		camPos[2] = -.1;
		camAt[0] = 0.0;
		camAt[1] = 0.0;
		camAt[2] = 0.0;
	}

	//eixos(1000,0,0,0);
	if(grill)
		grelha(62);
	
	//Line Drawing
	instance->drawFlora();
	
	if(drawGravity){
		//LineOrganism *org1 = NULL,*org2 = NULL;
		//instance->flora->at(0)->split(&org1,&org2);
		//if(org1 && org2){
		//	instance->flora->erase(instance->flora->begin());
		//	instance->flora->push_back(org1);
		//	instance->flora->push_back(org2);
		//}

		//instance->flora->at(0)->mitosis(10);
		instance->drawCenters();
	}

	timer->update();
	instance->updateFlora(timer->diff);

	glutSetWindowTitle(timer->getFPS()->c_str());

	glutSwapBuffers();
}

void LineViewer::init(int argc, char* argv[], int width, int height){
	// pôr inicialização aqui
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,600);
	glutCreateWindow("LineViewer");

	// pôr registo de funções aqui
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	// Registo das funções do teclado
	glutKeyboardFunc(normalKeys);
	glutSpecialFunc(specialKeys);

	// Registo das funções do Rato
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMotion);
	glutPassiveMotionFunc(mousePassiveMotion);

	// alguns settings para OpenGL
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	//glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);
	//glEnable(GL_LINE_SMOOTH);
//	glEnable(GL_LIGHTING);

	timer = new MyTimer();
	this->flora = new std::vector<LineOrganism*>();

	this->processor = new PostProcessor(width,height);
	this->m_width = width;
	this->m_height = height;

	//this->processor->setNPoints(201);
	cvNamedWindow("Result", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Gray", CV_WINDOW_AUTOSIZE);
	//cvNamedWindow("", CV_WINDOW_AUTOSIZE);
}

void LineViewer::run(){
	instance = this;
	
	glutMainLoop();
}

void LineViewer::adaptFlora(int pts){
	int flora_pts = this->getTotalPoints();
	int nOrganisms = this->getNOrganisms();
	int diff = pts - (flora_pts - nOrganisms);
	
	if(pts-1 > flora_pts){
		int index = 0;

		while(diff > 0){
			index = randomInt(0,this->getNOrganisms()-1);

			if(diff % 2){
				//mitosis 2
				this->flora->at(index)->mitosis(2);
				diff -= 2;
				flora_pts += 2;
			}
			else{
				//mitosis 1
				this->flora->at(index)->mitosis(1);
				diff--;
				flora_pts++;
			}

			if(this->getPointsOfOrganism(index) > 5){
				//split
				LineOrganism *org1 = NULL,*org2 = NULL;
				if(instance->flora->at(index)->split(&org1,&org2)){
					instance->getFlora()->insert(instance->getFlora()->begin() + index + 1,org1);
					instance->getFlora()->insert(instance->getFlora()->begin() + index + 2,org2);
					instance->flora->erase(instance->flora->begin() + index);
					diff--;
					nOrganisms++;
				}
			}
		}

		printf("");
	}
	else{
		while(diff < 0){
			int index = this->getNOrganisms()-1;

			if(abs(diff) > this->getPointsOfOrganism(index)){
				diff += this->getPointsOfOrganism(index);
				this->getFlora()->pop_back();
			}
			else{
				if(this->getPointsOfOrganism(index) > 4){
					this->getFlora()->at(index)->dropPoint(2);
					diff+=2;
				}
				else{
					this->getFlora()->at(index)->dropPoint(1);
					diff++;
				}
			}
		}
	}	
}

void LineViewer::processeImage(IplImage *img){
	this->processor->processImage(img);

	static bool first = true;

	std::vector<std::vector<CvPoint*>*>* pts = this->processor->getPoints();

	if(pts){
		//this->adaptFlora(pts->size());
		if(pts->size() == 0){
			if(first){
				this->deactivateFocus();
				first = false;
			}
		}
		else{
			//int my_pts = 0;
			//For each image's blob
			first = true;
			int hand_coord = 0;
			int blob = 0;
			double xx = 0.0;
			double zz = 0.0;

			int organism = 0 ;
			int bacteria = 0 ;

			for(bacteria = 0 ; bacteria < this->flora->size() && blob < pts->size() ; bacteria++){
				for(organism = 0 ; organism < this->flora->at(bacteria)->getNOrganisms() ; organism ++){
					this->flora->at(bacteria)->activateFocus();
					xx = ((pts->at(blob)->at(hand_coord)->x * 120.0) / 590.0) - 60.0;
					zz = ((pts->at(blob)->at(hand_coord)->y * 90.0) / 440.0) - 45.0;

					this->flora->at(bacteria)->updateCenter(organism,xx,00,zz);
					hand_coord++;
				}
				hand_coord--;

				if(hand_coord > (pts->at(blob)->size() - 4)){
					while(organism < this->flora->at(bacteria)->getNOrganisms()){
						this->flora->at(bacteria)->updateCenter(organism,xx,00,zz);
						organism++;
					}
					blob++;
					hand_coord = 0;
				}
			}

			while(bacteria < this->flora->size()){
				this->flora->at(bacteria)->deactivateFocus();
				bacteria++;
			}
			//for(int blob = 0 ; blob < pts->size() && my_pts < this->flora->size(); blob++){
			//	if(pts && pts->at(blob)->size() == 0){
			//		this->deactivateFocus();
			//	}
			//	else{
			//		double xx = 0.0;
			//		double zz = 0.0;

					//while(pts->at(blob)->size() % 3){
					//	pts->at(blob)->pop_back();
					//}

					//for( ; hand_coord < (pts->at(blob)->size() - 2) && my_pts < this->flora->size() ; my_pts++){
					//	this->flora->at(my_pts)->activateFocus();
					//	for(int j = 0 ; j < this->flora->at(my_pts)->getNOrganisms() && hand_coord < (pts->at(blob)->size() - 2) && my_pts < this->flora->size() ; j++){				
					//		xx = ((pts->at(blob)->at(hand_coord)->x * 120.0) / 590.0) - 60.0;
					//		zz = ((pts->at(blob)->at(hand_coord)->y * 90.0) / 440.0) - 45.0;

					//		this->flora->at(my_pts)->updateCenter(j,xx,00,zz);
					//		hand_coord++;
					//	}
					//	hand_coord--;
					//}
					//for(int i = 0 ; i < this->flora->size() ; i++){
					//	this->flora->at(i)->activateFocus();
					//	for(int j = 0 ; j < this->flora->at(i)->getNOrganisms() && hand_c < pts->size() ; j++){
					//		cvDrawCircle(img,*pts->at(hand_c),3,CV_RGB(0,0,255),-1);
				
					//		xx = ((pts->at(hand_c)->x * 120.0) / 590.0) - 60.0;
					//		zz = ((pts->at(hand_c)->y * 90.0) / 440.0) - 45.0;

					//		this->flora->at(i)->updateCenter(j,xx,00,zz);

					//		hand_c++;
					//	}
					//	hand_c--;
					//}
			//	}
			//}
		}
	}
	else{
		if(first){
			this->deactivateFocus();
			first = false;
		}
	}
	

	cvShowImage("Result",this->processor->getContourColorImage());
	cvShowImage("Gray",this->processor->getGrayImg());
}

void LineViewer::addOrganism(int n, int xx, int yy, double step, double s_range, double d_range){
	this->flora->push_back(new LineOrganism(n,xx,yy,step,s_range,d_range));
}

void LineViewer::drawFlora(){
	for(int i = 0 ; i < this->flora->size() ; i++){
		this->flora->at(i)->drawLines();
	}
}

void LineViewer::drawCenters(){
	for(int i = 0 ; i < this->flora->size() ; i++){
		this->flora->at(i)->drawCenters();
	}
}

void LineViewer::updateFlora(double pps){
	for(int i = 0 ; i < this->flora->size() ; i++){
		this->flora->at(i)->update(pps);
	}
}

void LineViewer::setPointsPerBlob(int n){
	this->processor->setNPoints(n);
}

std::vector<LineOrganism*>* LineViewer::getFlora(){
	return this->flora;
}

int LineViewer::getTotalPoints(){
	int ac = 0;

	for(int i = 0 ; i < this->getNOrganisms(); i++){
		ac += this->getPointsOfOrganism(i);
	}

	return ac;
}

int LineViewer::getPointsOfOrganism(int n){
	if(n > 0 && n < this->getNOrganisms()){
		this->getFlora()->at(n)->getNOrganisms();
	}
	else
		return -1;
}

int LineViewer::getNOrganisms(){
	return this->getFlora()->size();
}

void LineViewer::deactivateFocus(){
	for(int i = 0 ; i < this->flora->size() ; i++){
		this->flora->at(i)->deactivateFocus();
	}
}