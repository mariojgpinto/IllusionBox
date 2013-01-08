#ifndef _MAGNET_POINT
#define _MAGNET_POINT

#include "MyPoint.h"
#include "Tools.h"

extern int restore;

class MagneticPoint : public MyPoint{
	public:
		MagneticPoint();
		MagneticPoint(int posX, int posY, int posZ);
		MagneticPoint(double posX, double posY, double posZ);
		~MagneticPoint();

		void setDirection(double xx, double yy, double zz);
		void incDirection(double xx, double yy, double zz);

		void updatePosition();

		void setGravityPoint(double xx, double yy, double zz);

		void activateGravity(){this->gravity = true;this->home = false;}
		void deactivateGravity(){this->gravity = false;}

		void setStep(double s){this->step = s;}
		double getStep(){return this->step;}

	private:
		double direction[3];
		double origin[3];
		double center[3];
		
		double step;

		bool gravity;
		bool home;
		bool roam;
		bool newCenter;
};

#endif