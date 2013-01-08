#ifndef _CLOUD
#define _CLOUD

#include "MagnetPoint.h"
#include "GravityPoint.h"
#include "Tools.h"
#include <vector>

extern bool drawGravity;

class Cloud{
	public:
		Cloud(int nRows, int nCols, int nElems, double interval);
		~Cloud();

		void init();

		void drawPoints();
		void drawGravityPoints();
		void updatePoints();

		void addGravityPoint(GravityPoint* MyPoint);
		void changeGravityPoint(double xx, double yy, double zz);

		void activateGravity();
		void deactivateGravity();

	private:
		std::vector<MagneticPoint*>* pointPool;
		int nPoints;

		double interval;
		int cols;
		int rows;
		int elems;
		int ***positions;
		double **positionsBack;

		double minX;
		double minY;
		
		std::vector<GravityPoint*>* gravityPoints;

		void addRandomPoint(int xx, int yy);
};

#endif