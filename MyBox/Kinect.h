#ifndef _MY_KINECT
#define _MY_KINECT

#include <qthread.h>
#include <ntk/ntk.h>
#include <ntk/camera/calibration.h>
#include <ntk/camera/openni_grabber.h>

//namespace opt
//{
//	//ntk::arg<bool> high_resolution("--highres", "High resolution color image.", 0);
//	ntk::arg<int> kinect_id("--kinect-id", "Kinect id", 0);
//}

void resizeImage(const IplImage *origImg, IplImage *dest);

using namespace ntk;
using namespace cv;

class Kinect : public QThread{
	Q_OBJECT

	public:
		Kinect(QObject* parent =0);
		~Kinect();

		RGBDImage* getImage(){return &image;}

	protected:
		void run();
		void processKey(char key);

	private:
		OpenniDriver* ni_driver;
		OpenniGrabber* grabber;
		OpenniRGBDProcessor processor;

		RGBDImage image;

	signals:
		void kinectImage(RGBDImage* image);
};

#endif