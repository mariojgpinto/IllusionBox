#ifndef _VIEWER
#define _VIEWER

#include "Cloud.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "MyTimer.h"
#include "PostProcessor.h"
#include "LineOrganism.h"

/*
 * Mouse and Keyboard
 */
extern float camPos[3];// = {100.0,100.0,100.0};
extern float camAt[3];// = {0.0,0.0,0.0};
extern float camUp[3];// = {0.0,1.0,0.0};
extern float camDir[3];// = {0.0,0.0,-1.0};
extern float alpha, beta,r;
extern bool turn;// = false; // Mouse only
extern bool flyMode;// = false;
extern float mouseStep;// = 0.08;
extern float keyStep;// = 2.5;
extern double staticHigh;
extern double staticStep;
extern bool grill;
extern bool randomGPoint;
extern int restore;
extern bool follow;
extern double pt[];
extern bool drawGravity;

/*
 * Display Function
 */
void changeSize(int w, int h);
void renderScene(void);

/*
 * Viewer Class
 */
class LineViewer{
	public:
		LineViewer(){}
		~LineViewer(){}

		void init(int argc, char* argv[], int width, int height);
		
		void setPointsPerBlob(int n);

		void addOrganism(int n, int xx, int yy, double step = 2.5, double s_range = 0.25, double d_range = 5.0);
		
		void updateFlora(double pps);
		void drawFlora();
		void drawCenters();

		void processeImage(IplImage *img);
		void deactivateFocus();

		void run();
		
		std::vector<LineOrganism*>* getFlora();
		int getTotalPoints();
		int getPointsOfOrganism(int n);
		int getNOrganisms();


		
	private:
		PostProcessor *processor;
		std::vector<LineOrganism*>* flora;

		int m_width;
		int m_height;

		void adaptFlora(int pts);
};

#endif