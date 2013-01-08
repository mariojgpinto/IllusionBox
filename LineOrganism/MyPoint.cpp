#include "MyPoint.h"

MyPoint::MyPoint(){
	this->coord[0] = 0.0;
	this->coord[1] = 0.0;
	this->coord[2] = 0.0;

	this->color[0] = 1.0;
	this->color[1] = 1.0;
	this->color[2] = 1.0;
	//it=0;
}

MyPoint::MyPoint(int xx, int yy, int zz){
	this->coord[0] = xx;
	this->coord[1] = yy;
	this->coord[2] = zz;

	this->color[0] = 1.0;
	this->color[1] = 1.0;
	this->color[2] = 1.0;
	//it=0;
}

//MyPoint::MyPoint(float xx, float yy, float zz){
//	this->coord[0] = xx;
//	this->coord[1] = yy;
//	this->coord[2] = zz;
//}

MyPoint::MyPoint(double xx, double yy, double zz){
	this->coord[0] = xx;
	this->coord[1] = yy;
	this->coord[2] = zz;

	this->color[0] = 1.0;
	this->color[1] = 1.0;
	this->color[2] = 1.0;
	//it=0;
}

MyPoint::~MyPoint(){

}

//Methods

void MyPoint::increment(double xx, double yy, double zz){
	this->coord[0] += xx;
	this->coord[1] += yy;
	this->coord[2] += zz;
}

void MyPoint::update(int xx, int yy, int zz){
	this->coord[0] = xx;
	this->coord[1] = yy;
	this->coord[2] = zz;
}

void MyPoint::update(double xx, double yy, double zz){
	this->coord[0] = xx;
	this->coord[1] = yy;
	this->coord[2] = zz;
}

void MyPoint::setColor(double rr, double gg, double bb){
	this->color[0] = rr;
	this->color[1] = gg;
	this->color[2] = bb;
}