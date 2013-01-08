#ifndef _MY_TIMER
#define _MY_TIMER

#include "Tools.h"
#include <string>

class MyTimer{
	public:
		MyTimer();
		~MyTimer();

		void update();
		std::string* getFPS();
		
		void startTimer();
		float pauseTimer();
		float stopTimer();
		void resetTimer();

		int myTime;
		int myTimeOld;
		float diff;

		int frame;
		int timeBase;
		float fps;

		char buff[8];
		std::string* str;

		int timer_start;
		int timer_pause;
};

#endif