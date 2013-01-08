#include "PostProcessor.h"

PostProcessor::PostProcessor(int width, int height){
	this->_width = width;
	this->_height = height;

	this->img_raw = cvCreateImage(cvSize(this->_width,this->_height),8,3);
	this->img_gray = cvCreateImage(cvSize(this->_width,this->_height),8,1);
	this->img_temp = cvCreateImage(cvSize(this->_width,this->_height),8,1);
	this->img_contour = cvCreateImage(cvSize(this->_width,this->_height),8,1);
	this->img_color = cvCreateImage(cvSize(this->_width,this->_height),8,3);

	contour_storage = cvCreateMemStorage(0);
	this->contours = NULL;

	this->matrix = cvCreateStructuringElementEx(5,5,2,2,CV_SHAPE_ELLIPSE);
	this->interactions = 2;

	this->rotate = false;
	this->nPoints = 20;
	this->points = new std::vector<std::vector<CvPoint*>*>();

	cvZero(img_raw);
	cvZero(img_gray);
	cvZero(img_temp);
	cvZero(img_contour);
	cvZero(img_color);
}

PostProcessor::~PostProcessor(){
	
}

void PostProcessor::normalizeImage(IplImage* img){
	bool top = false,down = false,left = false,right = false;
	//Horizontal
	for(int i = 0 ; !top && !down && i < img->width; i++){
		if(cvGet2D(img,0,i).val[0] > 0) top = true;
		if(cvGet2D(img,img->height-1,i).val[0] > 0) down = true;
	}

	for(int i = 0 ; !left && !right && i < img->height; i++){
		if(cvGet2D(img,i,0).val[0] > 0) left = true;
		if(cvGet2D(img,i,img->width-1).val[0] > 0) right = true;
	}

	if(down && !left){
		cvFlip(img,img,0);
		this->rotate = true;
	}
}

void PostProcessor::processBlob(IplImage *img, CvSeq* seq){
	cvDrawContours(this->img_gray, seq,  CV_RGB( 255, 255, 255), CV_RGB( 255, 255, 255), 1, 1, 8, cvPoint(0,0));
	cvDrawContours(this->img_color, seq,  CV_RGB( 255, 0, 0), CV_RGB( 255, 0, 0), 1, 1, 8, cvPoint(0,0));

	CvPoint* points2 = (CvPoint*)malloc(sizeof(CvPoint) * seq->total);
	cvCvtSeqToArray (seq, points2, CV_WHOLE_SEQ);

	double step = ((double)seq->total)/((double)(this->nPoints - 1));

//	if(step < 1) step = 1.0;
	int count = 0;

	this->points->push_back(new std::vector<CvPoint*>());

	int index = 0;
	for(double i = 0 ; i < seq->total /*&& count < (this->nPoints -1)*/; i+=step , count++){
		index = (int)i;
		this->points->at(this->temp_blob-1)->push_back(&points2[index]);
		//this->points->at(this->temp_blob-1)->at(this->points->at(this->temp_blob-1)->size()-1)->y = 
		//	img->height- this->points->at(this->temp_blob-1)->at(this->points->at(this->temp_blob-1)->size()-1)->y;
	}
	while(this->points->at(this->temp_blob-1)->size() >= this->temp_blob * this->nPoints){
		this->points->at(this->temp_blob-1)->erase(this->points->at(this->temp_blob-1)->begin() + this->points->at(this->temp_blob-1)->size()-1);
	}
	//cvDrawCircle(img_color,points[seq->total-1],3,CV_RGB(255,0,255),-1);

	//Push last point
	this->points->at(this->temp_blob-1)->push_back(&cvPoint(points2[seq->total-1].x,points2[seq->total-1].y));

//	this->points->at(this->temp_blob-1)->at(this->points->at(this->temp_blob-1)->size()-1)->y = 
//		img->height- this->points->at(this->temp_blob-1)->at(this->points->at(this->temp_blob-1)->size()-1)->y;


	//while(this->points->at(this->temp_blob-1)->size() < this->nPoints - 1){
	//	int diff = (this->nPoints -1 ) - seq->total;

	//	double step2 = ((double)this->points->at(this->temp_blob-1)->size()-1)/((double)(diff));
	//	if(step2 < 1.0) step2 = 1;
	//	int orig_size = this->points->at(this->temp_blob-1)->size()-1;
	//	int count = 1;
	//	for(double i = 0 ; i < orig_size ; i += step2){
	//		int index = (int)i;

	//		CvPoint* pt1 = this->points->at(this->temp_blob-1)->at(count + index - 1);
	//		CvPoint* pt2 = this->points->at(this->temp_blob-1)->at(count + index);

	//		this->points->at(this->temp_blob-1)->insert(this->points->at(this->temp_blob-1)->begin() + count + index, 
	//			 &cvPoint((int)((((double)(pt1->x + pt2->x))/2.0)),(int)((((double)(pt1->y + pt2->y))/2.0))));
	//		
	//		count++;
	//	}
	//}
	//if(this->rotate = true){
	//	cvFlip(this->img_color,this->img_color,0);
	//	cvFlip(this->img_gray,this->img_gray,0);
	//}

	for(int i = 0 ; i < this->points->at(this->temp_blob-1)->size() ; i++){
		cvDrawCircle(img_color,*this->points->at(this->temp_blob-1)->at(i),3,CV_RGB(0,0,255),-1);
	}
}

void PostProcessor::processImage(IplImage* img){
	//normalizeImage(img);
	cvFlip(img,img,0);
	//cvFlip(img,img,1);

	for(int i = 0 ; i < this->points->size() ; i++){
		this->points->at(i)->clear();
	}
	this->points->clear();

	cvZero(img_color);

	if(img->nChannels == 3){
		this->img_raw = img;
		cvCvtColor(img, this->img_gray, CV_RGB2GRAY);		
		
	}
	else{
		this->img_gray = img;
		cvCvtColor(img, this->img_raw, CV_GRAY2RGB);	
	}

	cvThreshold(this->img_gray, this->img_temp, 1, 255, THRESH_BINARY );

	cvErode(this->img_temp,this->img_temp,this->matrix,this->interactions);
	cvDilate(this->img_temp,this->img_temp,this->matrix,this->interactions);

	if(this->contour_storage) cvClearMemStorage(this->contour_storage);
	if(this->contours) cvClearSeq(this->contours);

	//cvFindContours(this->img_temp, this->contour_storage, &this->contours,sizeof(CvContour), CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	cvFindContours(this->img_temp, this->contour_storage, &this->contours,sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

	this->temp_blob = 0;

	if(contours){
		CvSeq* seq = contours;

		int ac = 0;
		while(seq){
			if(seq->total > 100){
				ac++;
			}
			seq = seq->h_next;
		}

		this->nPoints = (int)((double)this->nPoints/(double)ac);
		this->nPoints++;
		if(this->nPoints % 2 == 0) this->nPoints++;
		
		seq = contours;
				
		while(seq){
			if(seq->total > 100){
				this->temp_blob++;
				this->processBlob(img,seq);
			}
			seq = seq->h_next;
		}
	}
	this->nPoints = this->nPoints_orig;
}

IplImage* PostProcessor::getGrayImg(){
	return this->img_gray;
}

IplImage* PostProcessor::getContourImage(){
	return this->img_contour;
}

IplImage* PostProcessor::getContourColorImage(){
	return this->img_color;
}

void PostProcessor::setNInteraction(int n){
	this->interactions = n;
}

std::vector<std::vector<CvPoint*>*>* PostProcessor::getPoints(){
	return this->points;
}

void PostProcessor::setNPoints(int n){
	this->nPoints = n;
	this->nPoints_orig = n;
}