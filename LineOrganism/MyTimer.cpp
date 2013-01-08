#include "MyTimer.h"

MyTimer::MyTimer(){
	this->myTime = 0;
	this->myTimeOld = 0;
	this->diff = 0;

	this->frame = 0;
	this->timeBase = 0;
	this->fps = 0.0f;

	this->str = new std::string();

	this->timer_pause = 0.0;
	this->timer_start = 0.0;
}

MyTimer::~MyTimer(){

}



void MyTimer::update(){
	this->myTime = glutGet(GLUT_ELAPSED_TIME); 
	this->diff = (this->myTime - this->myTimeOld) / 1000.0;
	this->myTimeOld = this->myTime;
	this->frame++;
}

std::string* MyTimer::getFPS(){
	if(this->myTime - this->timeBase > 1000){
		this->fps = frame*1000.0/(this->myTime - this->timeBase);
		this->timeBase = this->myTime;
		this->frame = 0;

		_itoa_s(this->fps,this->buff,10);
		this->str->assign(this->buff);
		this->str->append("FPS");
	}

	return this->str;
}

void MyTimer::startTimer(){
	this->timer_start = this->myTime;
}

float MyTimer::pauseTimer(){
	this->timer_pause = this->myTime;
	return (this->timer_pause - this->timer_start)/1000.0;
}

float MyTimer::stopTimer(){
	this->timer_pause = this->myTime;
	float temp = (this->timer_pause - this->timer_start)/1000.0;

	this->resetTimer();

	return temp;
}

void MyTimer::resetTimer(){
	this->timer_pause = 0.0;
	this->timer_start = 0.0;
}