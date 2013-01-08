#ifndef _POST_PROCESSOR
#define _POST_PROCESSOR

#include "Tools.h"
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;

class PostProcessor{
	public:
		//PostProcessor();
		PostProcessor(int width, int height);
		~PostProcessor();

		void processImage(IplImage* img);

		IplImage* getGrayImg();
		IplImage* getContourImage();
		IplImage* getContourColorImage();

		void setNPoints(int n);
		void setNInteraction(int n);
		std::vector<std::vector<CvPoint*>*>* getPoints();

	private:
		IplImage *img_raw;
		IplImage *img_gray;
		IplImage *img_temp;
		IplImage *img_contour;
		IplImage *img_color;

		int _width;
		int _height;

		CvSeq *contours;
		CvMemStorage *contour_storage;

		IplConvKernel *matrix;
		int interactions;

		bool rotate;
		void normalizeImage(IplImage* img);

		int nPoints;
		int nPoints_orig;

		std::vector<std::vector<CvPoint*>*>* points;

		void processBlob(IplImage *img, CvSeq* seq);

		int temp_blob;
};

#endif