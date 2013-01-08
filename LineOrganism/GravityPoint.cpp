#include "GravityPoint.h"

GravityPoint::GravityPoint() : MyPoint(), nPoints(1){
	this->points = new std::vector<MyPoint*>();
	this->points->push_back(this->getMe());
}

GravityPoint::GravityPoint(int posX, int posY, int posZ) : MyPoint(posX, posY, posZ), nPoints(1){
	this->points = new std::vector<MyPoint*>();
	this->points->push_back(this->getMe());
}

GravityPoint::GravityPoint(double posX, double posY, double posZ) : MyPoint(posX, posY, posZ), nPoints(1){
	this->points = new std::vector<MyPoint*>();
	this->points->push_back(this->getMe());
}

GravityPoint::~GravityPoint(){

}


void GravityPoint::addDisturbance(double range){
	xMin = this->x() - range/2.0;
	xMax = this->x() + range/2.0;
	zMin = this->z() - range/2.0;
	zMax = this->z() + range/2.0;
	
	this->points->push_back(new MyPoint(xMin,0.0,0.0));
	this->points->push_back(new MyPoint(xMax,0.0,0.0));
	this->points->push_back(new MyPoint(0.0,0.0,zMin));
	this->points->push_back(new MyPoint(0.0,0.0,zMax));
	this->points->push_back(new MyPoint(xMin/1.3,0.0,zMin/1.3));
	this->points->push_back(new MyPoint(xMin/1.3,0.0,zMax/1.3));
	this->points->push_back(new MyPoint(xMax/1.3,0.0,zMin/1.3));
	this->points->push_back(new MyPoint(xMax/1.3,0.0,zMax/1.3));

	//for(int i = 0 ; i < n ; i++){
	//	this->points->push_back(new MyPoint(randomDouble(xMin,xMax),0.0,randomDouble(zMin,zMax)));
	//}

	//this->nPoints += n;
	this->nPoints += 8;
}

void GravityPoint::addDisturbancePoint (double xx, double yy, double zz){
	this->points->push_back(new MyPoint(xx,yy,zz));
	this->nPoints++;
}

MyPoint* GravityPoint::getGravityPoint(int i){
	if(i >= this->points->size()) return new MyPoint();
	else return this->points->at(i);
}

MyPoint* GravityPoint::getRandomGravityPoint(){
	return this->points->at(randomInt(0,this->points->size()));
}


void GravityPoint::changeGravityCenter(int posX, int posY, int posZ){
	this->changeGravityCenter((double)posX,(double)posY,(double)posZ);
}

void GravityPoint::changeGravityCenter(double posX, double posY, double posZ){
	double diffX = posX - this->x();
	double diffZ = posZ - this->z();

	for(int i = 0 ; i < this->points->size() ; i++){
		this->points->at(i)->increment(diffX,0.0,diffZ);
	}
}

void GravityPoint::changeGravityDisturbance(){
	for(int i = 1 ; i < this->points->size() ; i++){
		this->points->at(i)->update(randomDouble(this->x() + xMin,this->x() + xMax),0.0,this->z() + randomDouble(zMin,zMax));
	}
}