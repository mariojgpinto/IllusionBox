#include "Cloud.h"

Cloud::Cloud(int nRows, int nCols, int nElems, double interval){
	this->pointPool = new std::vector<MagneticPoint*>();
	this->gravityPoints = new std::vector<GravityPoint*>();

	this->nPoints = 0;

	this->rows = nRows;
	this->cols = nCols;
	this->elems = nElems;
	this->interval = interval;

	this->minX = -((nCols * interval) / 2.0);
	this->minY = -((nRows * interval) / 2.0);
}






void Cloud::init(){
	this->positions = (int***)malloc(sizeof(int**) * this->cols);

	for(int i = 0 ; i < this->cols ; i++){
		this->positions[i] = (int**)malloc(sizeof(int*) * this->rows);

		for(int j = 0 ; j < this->rows ; j++){
			this->positions[i][j] = (int*)malloc(sizeof(int) * this->elems);
			

			for(int k = 0 ; k < this->elems ; k++){
				this->positions[i][j][k] = this->nPoints;
				this->addRandomPoint(i,j);
			}
		}
	}

	this->positionsBack = (double**)malloc(sizeof(double*) * this->pointPool->size());
	for(int i = 0 ; i < this->pointPool->size() ; i++){
		this->positionsBack[i] = (double*)malloc(sizeof(double) * 3);
		this->positionsBack[i][0] = this->pointPool->at(i)->x();
		this->positionsBack[i][1] = this->pointPool->at(i)->y();
		this->positionsBack[i][2] = this->pointPool->at(i)->z();
	}
}


void Cloud::addRandomPoint(int xx, int yy){
	double xMin = this->minX + (this->interval * xx);
	double xMax = this->minX + (this->interval * (1 + xx));
	double yMin = this->minY + (this->interval * yy);
	double yMax = this->minY + (this->interval * (1 + yy));

	this->pointPool->push_back(new MagneticPoint(randomDouble(xMin,xMax),0.0,randomDouble(yMin,yMax)));
	this->pointPool->at(nPoints)->activateGravity();
	//this->pointPool->at(nPoints)->setColor(randomDouble(0.0,1.0),randomDouble(0.0,1.0),randomDouble(0.0,1.0));

#ifdef NDEBUG
	this->pointPool->at(nPoints)->setStep(randomDouble(0.005,0.02));
#else			
	this->pointPool->at(nPoints)->setStep(randomDouble(0.035,0.12));
#endif	
	
	this->nPoints++;
}

void Cloud::drawPoints(){
	glColor3f(BRANCO);
	glBegin(GL_POINTS);

	for(unsigned int i = 0 ; i < this->pointPool->size() ; i++){
		glColor3f(	this->pointPool->at(i)->r(),
					this->pointPool->at(i)->g(),
					this->pointPool->at(i)->b());
		glVertex3f(	this->pointPool->at(i)->x(), 
					this->pointPool->at(i)->y(), 
					this->pointPool->at(i)->z());
	}

	glEnd();
}

void Cloud::drawGravityPoints(){
	glColor3f(VERMELHO);

	for(unsigned int i = 0 ; i < this->gravityPoints->size() ; i++){
		for(unsigned int j = 0 ; j < this->gravityPoints->at(i)->getNPoints() ; j++){
			glPushMatrix();		
			glTranslatef(this->gravityPoints->at(i)->getGravityPoint(j)->x(),
						 this->gravityPoints->at(i)->getGravityPoint(j)->y(),
						 this->gravityPoints->at(i)->getGravityPoint(j)->z());
			glutSolidSphere(0.5,4,4);
			glPopMatrix();
		}
	}
}

void Cloud::updatePoints(){
	static int temp = 0;
	static int gen = 0;

	if(this->gravityPoints->size() == 0){
		for(unsigned int i = 0 ; i < this->pointPool->size() ; i++){
			this->pointPool->at(i)->updatePosition();
		}
	}
	else{
		if(restore){
			for(unsigned int i = 0 ; i < this->pointPool->size() ; i++){
				//this->pointPool->at(i)->setGravityPoint(positionsBack[i][0],positionsBack[i][1],positionsBack[i][2]);
				this->pointPool->at(i)->deactivateGravity();
				this->pointPool->at(i)->updatePosition();
			}
		}
		else{
			if(temp == 0){
				MyPoint* MyPoint;
				for(unsigned int i = 0 ; i < this->pointPool->size() ; i++){
					//this->pointPool->at(i)->it = (this->pointPool->at(i)->it + 1) % this->gravityPoints->at(0)->getNPoints() ;

					//MyPoint = this->gravityPoints->at(0)->getGravityPoint(this->pointPool->at(i)->it);
					MyPoint = this->gravityPoints->at(0)->getRandomGravityPoint();
					this->pointPool->at(i)->setGravityPoint(MyPoint->x(),MyPoint->y(),MyPoint->z());
				
				}
#ifdef NDEBUG
				temp = 125;
#else			
				temp = 25;
#endif				
			}
			if(gen == 0){
				//this->gravityPoints->at(0)->changeGravityDisturbance();
				gen = 1;
			}
			for(unsigned int i = 0 ; i < this->pointPool->size() ; i++){
				this->pointPool->at(i)->updatePosition();
			}
			temp--;
			gen--;
		}
	}
}

void Cloud::addGravityPoint(GravityPoint* MyPoint){
	this->gravityPoints->push_back(MyPoint);
}

void Cloud::changeGravityPoint(double xx, double yy, double zz){
	this->gravityPoints->at(0)->changeGravityCenter(xx,yy,zz);
}

//bool coiso = true;
void Cloud::activateGravity(){
	//drawGravity = true;
	for(unsigned int i = 0 ; i < this->pointPool->size() ; i++){
		this->pointPool->at(i)->activateGravity();
	//	if(coiso)
	//		this->pointPool->at(i)->setStep(this->pointPool->at(i)->getStep() + (this->pointPool->at(i)->getStep() / 2.0));
	}
	//if(coiso) coiso = false;
}

void Cloud::deactivateGravity(){
	//drawGravity = false;
	for(unsigned int i = 0 ; i < this->pointPool->size() ; i++){
		this->pointPool->at(i)->deactivateGravity();
	//	if(!coiso)
	//		this->pointPool->at(i)->setStep(this->pointPool->at(i)->getStep() - (this->pointPool->at(i)->getStep() / 2.0));
	}
	//if(!coiso) coiso = true;
}