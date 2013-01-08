#ifndef _GRAVITY_POINT
#define _GRAVITY_POINT

#include "MyPoint.h"
#include "Tools.h"
#include <vector>

class GravityPoint : public MyPoint{
	public:
		GravityPoint();
		GravityPoint(int posX, int posY, int posZ);
		GravityPoint(double posX, double posY, double posZ);
		~GravityPoint();

		void addDisturbancePoint(double xx, double yy, double zz);
		void addDisturbance(double range);

		void changeGravityCenter(int posX, int posY, int posZ);
		void changeGravityCenter(double posX, double posY, double posZ);
		void changeGravityDisturbance();

		MyPoint* getGravityPoint(int i);
		MyPoint* getRandomGravityPoint();

		int getNPoints(){return this->points->size();}

	private:
		std::vector<MyPoint*>* points;
		int nPoints;

		double xMin;
		double xMax;
		double zMin;
		double zMax;
};



#endif