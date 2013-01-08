#include "LineOrganism.h"

LineOrganism::LineOrganism(int n, double xx, double yy, double step, double s_range, double d_range){
	this->base_step = step;
	this->range_step = s_range;
	this->range_origin = d_range;

	this->myPoints = new std::vector<MyPoint*>();
	this->directions = new std::vector<MyPoint*>();
	this->centers = new std::vector<MyPoint*>();
	this->steps = new std::vector<double>();

	this->generateNPoints(n, xx, yy);

	this->focus = false;
}

LineOrganism::~LineOrganism(){

}



void LineOrganism::setOrigin(double xx, double yy){
	this->origin->update(xx,0.0,yy);
}

void LineOrganism::generateNPoints(int n, double xx, double yy){
	this->nPoints = n;
	this->origin = new MyPoint(xx,0.0,yy);

	double xMin = xx - this->range_origin;
	double xMax = xx + this->range_origin;
	double yMin = yy - this->range_origin;
	double yMax = yy + this->range_origin;

	for(int i = 0 ; i < this->nPoints ; i++){
		this->myPoints->push_back(new MyPoint(randomDouble(xMin,xMax),0.0,randomDouble(yMin,yMax)));
		this->centers->push_back(new MyPoint(randomDouble(xMin,xMax),0.0,randomDouble(yMin,yMax)));
		this->steps->push_back(randomDouble((this->base_step - this->range_step), (this->base_step + this->range_step)));
		this->directions->push_back(new MyPoint());
	}

	this->normalizeDirections();
}

void LineOrganism::normalizeDirections(){
	for(int i = 0 ; i < this->nPoints ; i++){
		this->directions->at(i)->update(this->centers->at(i)->x() - this->myPoints->at(i)->x(),
										0.0,
										this->centers->at(i)->z() - this->myPoints->at(i)->z());
		
		
		double p = sqrt(pow((double)this->directions->at(i)->x(),2) + 
						pow((double)this->directions->at(i)->z(),2));

		this->directions->at(i)->update(this->directions->at(i)->x() / p, 
										0.0,
										this->directions->at(i)->z() / p);
	}
}


void LineOrganism::update(float pps){
	boost::mutex::scoped_lock scoped_lock(mutex);
	if(this->focus){
		this->updateFocus(pps);
	}
	else{
		this->updateIdle(pps);
	}
}

void LineOrganism::updateIdle(float pps){
	for(int i = 0 ; i < this->nPoints ; i++){
		this->myPoints->at(i)->increment(	(this->directions->at(i)->x() * this->steps->at(i) * pps),
											0.0,
											(this->directions->at(i)->z() * this->steps->at(i) * pps));

		double dist = sqrt( pow((double) (	this->myPoints->at(i)->x() - 
											this->centers->at(i)->x())
											,2) + 
							pow((double) (	this->myPoints->at(i)->z() - 
											this->centers->at(i)->z())
											,2));

		if(dist < 0.5){
			this->centers->at(i)->update(	randomDouble(this->origin->x() - this->range_origin,
														 this->origin->x() + this->range_origin),
											0.0,
											randomDouble(this->origin->z() - this->range_origin,
														 this->origin->z() + this->range_origin));
			this->normalizeDirections();
		}
	}

}

void LineOrganism::updateFocus(float pps){
	for(int i = 0 ; i < this->nPoints ; i++){
		double dist = sqrt( pow((double) (	this->myPoints->at(i)->x() - 
											this->centers->at(i)->x())
											,2) + 
							pow((double) (	this->myPoints->at(i)->z() - 
											this->centers->at(i)->z())
											,2));
		if(dist > 0.5){
			this->myPoints->at(i)->increment((this->directions->at(i)->x() * this->steps->at(i) * pps),
											 0.0,
											 (this->directions->at(i)->z() * this->steps->at(i) * pps));
		}
	}
	this->normalizeDirections();
}


void LineOrganism::updateCenters(std::vector<CvPoint*>* c){
	if(c){
		if(c->size() == this->nPoints){
			for(int i = 0 ; i < c->size() ; i++){
				this->centers->at(i)->update(c->at(i)->x,
											 0,
											 c->at(i)->y);
			}
		}
	}

	this->normalizeDirections();
}

void LineOrganism::updateCenter(int n, double xx, double yy, double zz){
	if(n < this->nPoints){
		this->centers->at(n)->update(xx,yy,zz);

		this->directions->at(n)->update(this->centers->at(n)->x() - this->myPoints->at(n)->x(),
										0.0,
										this->centers->at(n)->z() - this->myPoints->at(n)->z());
		
		
		double p = sqrt(pow((double)this->directions->at(n)->x(),2) + 
						pow((double)this->directions->at(n)->z(),2));

		this->directions->at(n)->update(this->directions->at(n)->x() / p, 
										0.0,
										this->directions->at(n)->z() / p);
	}
}

void LineOrganism::activateFocus(){
	this->focus = true;
}

void LineOrganism::deactivateFocus(){
	this->focus = false;

	for(int i = 0 ; i < this->nPoints ; i++){
		this->centers->at(i)->update(	randomDouble(this->origin->x() - this->range_origin,
													 this->origin->x() + this->range_origin),
										0.0,
										randomDouble(this->origin->z() - this->range_origin,
													 this->origin->z() + this->range_origin));
		this->normalizeDirections();
	}
}


std::vector<MyPoint*>* LineOrganism::getPoints(){
	return this->myPoints;
}


void LineOrganism::drawPoints(){
	//glBegin(GL_POINT);
	//glColor3f(BRANCO);
	//for(int i = 0 ; i < this->nPoints ; i++){
	//	glVertex3f(	this->myPoints->at(i)->x(), 
	//				0.0,
	//				this->myPoints->at(i)->z());
	//}
	//glEnd();
	boost::mutex::scoped_lock scoped_lock(mutex);

	glBegin(GL_POINT);
	glColor3f(BRANCO);
	for(int i = 0 ; i < this->nPoints ; i++){
		glPushMatrix();		
		glTranslatef(	this->myPoints->at(i)->x(),
						0.0,
						this->myPoints->at(i)->z());
		glutSolidSphere(0.3,4,4);

		glPopMatrix();
	}
	glEnd();
}

void LineOrganism::drawCenters(){
	boost::mutex::scoped_lock scoped_lock(this->mutex);

	glBegin(GL_POINT);
	glColor3f(VERMELHO);
	for(int i = 0 ; i < this->nPoints ; i++){
		glPushMatrix();		
		glTranslatef(	this->centers->at(i)->x(),
						0.0,
						this->centers->at(i)->z());
		glutSolidSphere(0.5,4,4);

		glPopMatrix();
	}
	glEnd();
}

void LineOrganism::drawLines(){
	boost::mutex::scoped_lock scoped_lock(mutex);


	//glEnable (GL_LINE_SMOOTH);
	//glEnable (GL_BLEND);
	//glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR);
	//glHint (GL_LINE_SMOOTH_HINT, GL_FASTEST);
	glLineWidth (1.5);
	//
	glBegin(GL_LINES);
	glColor3f(BRANCO);
	for(int i = 0 ; i < this->nPoints - 1; i++){
		//glColor4ub(255,255,255,150);
		glVertex3f(	this->myPoints->at(i)->x(), 
					0.0,
					this->myPoints->at(i)->z());
		glVertex3f(	this->myPoints->at(i+1)->x(), 
					0.0,
					this->myPoints->at(i+1)->z());
	}
	glEnd();
}

void LineOrganism::drawPointsAndLines(){
	boost::mutex::scoped_lock scoped_lock(mutex);

	this->drawPoints();
	this->drawLines();
}

int LineOrganism::getNOrganisms(){
	return this->nPoints;
}

bool LineOrganism::split(LineOrganism **org1, LineOrganism **org2){
	boost::mutex::scoped_lock scoped_lock(mutex);

	if(this->nPoints > 3){
		//(int)((double)7/2.0)
		int n1 = (int)((double)this->nPoints / 2.0);
		int n2 = this->nPoints - n1;

		LineOrganism *aux1 = new LineOrganism(n1,this->myPoints->at(0)->x(),this->myPoints->at(0)->z(),
												 this->base_step,this->range_step,this->range_origin);
		LineOrganism *aux2 = new LineOrganism(n2,this->myPoints->at(n1)->x(),this->myPoints->at(n1)->z(),
												 this->base_step,this->range_step,this->range_origin);

		aux1->setOrigin(randomDouble(-60.0,60.0),randomDouble(-45.0,45.0));
		
		double xMin = aux1->origin->x() - this->range_origin;
		double xMax = aux1->origin->x() + this->range_origin;
		double yMin = aux1->origin->z() - this->range_origin;
		double yMax = aux1->origin->z() + this->range_origin;

		for(int i = 0 ; i < n1 ; i++){
			aux1->myPoints->at(i)->update(this->myPoints->at(i)->x(),this->myPoints->at(i)->y(),this->myPoints->at(i)->z());
			aux1->centers->at(i)->update(randomDouble(xMin,xMax),0.0,randomDouble(yMin,yMax));
			aux1->normalizeDirections();
		}

		aux2->setOrigin(randomDouble(-60.0,60.0),randomDouble(-45.0,45.0));

		xMin = aux2->origin->x() - this->range_origin;
		xMax = aux2->origin->x() + this->range_origin;
		yMin = aux2->origin->z() - this->range_origin;
		yMax = aux2->origin->z() + this->range_origin;

		for(int i = n1 , j = 0; j < n2 ; i++, j++){
			aux2->myPoints->at(j)->update(this->myPoints->at(i)->x(),this->myPoints->at(i)->y(),this->myPoints->at(i)->z());
			aux2->centers->at(j)->update(randomDouble(xMin,xMax),0.0,randomDouble(yMin,yMax));
			aux2->normalizeDirections();
		}

		*org1 = aux1;
		*org2 = aux2;

		return true;
	}
	else{
		return false;
	}
}

int LineOrganism::mitosis(int n){
	boost::mutex::scoped_lock scoped_lock(mutex);

	double xMin = this->myPoints->at(this->nPoints-1)->x() - this->range_origin;
	double xMax = this->myPoints->at(this->nPoints-1)->x() + this->range_origin;
	double yMin = this->myPoints->at(this->nPoints-1)->x() - this->range_origin;
	double yMax = this->myPoints->at(this->nPoints-1)->x() + this->range_origin;

	for(int i = 0 ; i < n ; i++){
		this->myPoints->push_back(new MyPoint(randomDouble(xMin,xMax),0.0,randomDouble(yMin,yMax)));
		this->centers->push_back(new MyPoint(randomDouble(xMin,xMax),0.0,randomDouble(yMin,yMax)));
		this->steps->push_back(randomDouble((this->base_step - this->range_step), (this->base_step + this->range_step)));
		this->directions->push_back(new MyPoint());
		this->nPoints++;
	}

	this->normalizeDirections();

	return this->nPoints;
}

void LineOrganism::dropPoint(int n){
	boost::mutex::scoped_lock scoped_lock(mutex);

	if(this->nPoints - n < 3) return;

	for(int i = 0 ; i < n ; i++){
		this->myPoints->pop_back();
		this->directions->pop_back();
		this->centers->pop_back();
		this->steps->pop_back();
	}

	this->nPoints -= n;
}