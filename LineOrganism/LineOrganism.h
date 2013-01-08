#ifndef _LINE_ORGANISM
#define _LINE_ORGANISM

#include "Tools.h"
#include "MyPoint.h"
#include <vector>
#include <opencv2/opencv.hpp>
#include <boost\thread\mutex.hpp>


class LineOrganism{
	public:
		LineOrganism(int n, double xx, double yy, double step = 2.5, double s_range = 0.25, double d_range = 5.0);
		~LineOrganism();

		void setOrigin(double xx, double yy);

		void update(float pps);
		void updateCenter(int n, double xx, double yy, double zz);
		void updateCenters(std::vector<CvPoint*>* c);

		void activateFocus();
		void deactivateFocus();

		std::vector<MyPoint*>* getPoints();
		int getNOrganisms();

		bool split(LineOrganism **org1, LineOrganism **org2);
		int mitosis(int n);
		void dropPoint(int n);

		void drawPoints();
		void drawCenters();
		void drawLines();
		void drawPointsAndLines();

	private:
		int nPoints;
		std::vector<MyPoint*>* myPoints;
		std::vector<MyPoint*>* directions;
		std::vector<MyPoint*>* centers;
		std::vector<double>* steps;

		MyPoint* origin;

		double range_origin;
		double range_step;
		double base_step;

		bool focus;

		boost::mutex mutex;

		void generateNPoints(int n, double xx, double yy);
		void normalizeDirections();
		void updateIdle(float pps);
		void updateFocus(float pps);
};

#endif