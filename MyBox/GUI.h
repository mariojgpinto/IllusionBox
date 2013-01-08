#ifndef _GUI
#define _GUI

#include "GeneratedFiles\ui_Exp.h"
#include <ntk/gui/image_widget.h>

#include <iostream>
#include <boost/tokenizer.hpp>
#include <string>

#include "Kinect.h"
#include <boost\thread.hpp>
 
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include <boost/regex.hpp>

#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>

#include "..\LineOrganism\LineViewer.h"

namespace ba=boost::asio;
namespace bs=boost::system;

typedef boost::shared_ptr<ba::ip::tcp::socket> socket_ptr;
typedef boost::shared_ptr<ba::io_service> io_service_ptr;

#define SLIDER_MAX 4.5

class expQt;

void compute2DPolygonCentroid(CvPoint* vertices, int vertexCount,  CvPoint *centroid);

class Lines{
	public:
		Lines(expQt* qt, int argc, char *argv[]){
			this->qt = qt;

			this->v = new LineViewer();
			this->v->init(argc, argv,590,440);
			this->v->setPointsPerBlob(502);
			for(int i = 0 ; i < 250 ; i++){
				if(argc > 2){
					int mvel, mrange;
					mvel = atoi(argv[1]);
					mrange = atoi(argv[2]);

					v->addOrganism(3,randomDouble(-55,55),randomDouble(-40,40),mvel,mrange,5.0);
				}
				else{
					v->addOrganism(3,randomDouble(-55,55),randomDouble(-40,40),12.5,2.0,5.0);
				}
			}
		}

		~Lines();

		void run(){
			v->run();
		}

		LineViewer *v;
	private:
		expQt* qt;

};
	 
class expQt : public QWidget, private Ui::Form
{
    Q_OBJECT
 
public:
	QMenuBar *menubar;
    expQt(int argc, char* argv[], QWidget *parent = 0){
		setupUi(this);
		kinect = new Kinect();

		kinect->getImage()->depth().copyTo(masked_distance);
		//this->magnet = NULL;
		this->line = NULL;
		this->setupWindows();

		oldMin = ((double)(maxDepth/SLIDER_MAX))*100;
		oldMax = ((double)(maxDepth/SLIDER_MAX))*100;

		minDepth = 0.4;
		maxDepth = 0.63;
		firstRun = true;
		roizinho = 1;

		roi.x = 0;
		roi.y = 0;
		roi.width = 640;
		roi.height = 480;

		depthRoi.x = 10;
		depthRoi.y = 30;
		depthRoi.width = 590;
		depthRoi.height = 440;

		this->maxSlider->setValue(((double)(maxDepth/1.5))*100);
		this->minSlider->setValue(((double)(minDepth/1.5))*100);

		connect(maxSlider, SIGNAL(valueChanged(int)), this, SLOT(on_maxSlider_valueChanged() ));
		connect(minSlider, SIGNAL(valueChanged(int)), this, SLOT(on_minSlider_valueChanged() ));
		connect(ROISlider, SIGNAL(valueChanged(int)), this, SLOT(on_ROISlider_valueChanged() ));
		connect(buttonLeft, SIGNAL(pressed()), this, SLOT(on_Left_Clicked() ));
		connect(buttonRight, SIGNAL(clicked()), this, SLOT(on_Right_Clicked() ));
		connect(buttonUp, SIGNAL(clicked()), this, SLOT(on_Up_Clicked() ));
		connect(buttonDown, SIGNAL(clicked()), this, SLOT(on_Down_Clicked() ));
		connect(lineButton, SIGNAL(clicked()), this, SLOT(on_Line_Clicked() ));
		connect(kinect, SIGNAL(kinectImage(RGBDImage*)),this, SLOT(paintImage(RGBDImage*)));

		m_argc = argc;
		m_argv = argv;
	}
 
	IplImage* getBin(){
		return this->binAux;
	}




		void startLineOrganism(int argc, char*argv[]){
			line = new Lines(this,argc,argv);
			line->run();
		}
 
public slots:
    void on_maxSlider_valueChanged(int value){
		if(this->checkBoxDiff->isChecked()){
			changeFixedDepth(value,true);
		}
		else{
			double max_meters = this->maxSlider->value()/100.0;
			maxDepth = max_meters*SLIDER_MAX;
			this->labelMaxSlider->setText(QString("Max Slider: %1 m").arg(maxDepth, 0, 'f', 2));
			oldMax = value;
		}
	}

    void on_minSlider_valueChanged(int value){
		if(this->checkBoxDiff->isChecked()){
			changeFixedDepth(value,false);
		}
		else{
			double min_meters = this->minSlider->value()/100.0;
			minDepth = min_meters*SLIDER_MAX;
			this->labelMinSlider->setText(QString("Min Slider: %1 m").arg(minDepth, 0, 'f', 2));
			oldMin = value;
		}
	}

	void on_ROISlider_valueChanged(int value){
		double roimeter = this->ROISlider->value()/100.0;
		roizinho = 1 + roimeter*3;

		double factor = pow(2,(roizinho - 1));
		int w = 640/factor;
		int h = 480/factor;

		int hor = (640 - w ) / 2;
		int ver = (480 - h ) / 2;

		roi.x = hor;
		roi.y = ver;
		roi.width = w;
		roi.height = h;

		this->labelROI->setText(QString("ROI: %1 m").arg(roizinho, 0, 'f', 2));		
	}

	void on_Up_Clicked(){	
		if(this->roi.y > 2){
			this->roi.y -= 2;
			this->roi.height -= 2;
		}
	}

	void on_Down_Clicked(){
		if(this->roi.height < 638){
			this->roi.y += 2;
			this->roi.height += 2;
		}
	}

	void on_Left_Clicked(){
		if(this->roi.x > 2){
			this->roi.x -= 2;
			this->roi.width -= 2;
		}
	}

	void on_Right_Clicked(){
		if(this->roi.x < 438){
			this->roi.x += 2;
			this->roi.width += 2;
		}
	}

	void on_Line_Clicked(){
		boost::thread(&expQt::startLineOrganism, this, m_argc, m_argv);
	}

	void paintImage(RGBDImage* image){
		if(firstRun){
			image->depth().copyTo(masked_distance);
			binAux = cvCreateImage(cvSize(590,440), 8, 1);
			//bin = cvCreateImage(cvSize(640,480), 8, 1);
			greyTemp = cvCreateImage(cvSize(590,440), 8, 1);
			raw_depth = cvCreateImage(cvSize(640,480), 8, 1);
			contours = cvCreateImage(cvSize(640,480), 8, 1);
			colorTemp = cvCreateImage(cvSize(640,480), 8, 3);
			raw_rgb = cvCreateImage(cvSize(640,480), 8, 3);

			cvSetImageROI(raw_depth,depthRoi);
			cvSetImageROI(raw_rgb,depthRoi);

			g_storage = cvCreateMemStorage(0);
			compute_color_encoded_depth(masked_distance, depth_as_color, &minDepth, &maxDepth);
			depth_as_color.copyTo(diff);
			depth_as_color.copyTo(old);
			firstRun = false;
		}
		else{
			//image->rgb().adjustROI(30,440,7,590);
			raw_rgb = &image->rgb().operator IplImage();
			cvSetImageROI(raw_rgb,depthRoi);
			rgb = raw_rgb;

			raw_depth = &image->depth().operator IplImage();
			cvSetImageROI(raw_depth,depthRoi);
			depth = raw_depth ;

			compute_color_encoded_depth(depth, depth_as_color, &minDepth, &maxDepth);

			cvZero(greyTemp);
			cvZero( binAux );
			
			colorTemp = &depth_as_color.operator IplImage();

			cvCvtColor( colorTemp, greyTemp, CV_BGR2GRAY );

			cvSmooth( binAux, binAux, CV_GAUSSIAN, 7, 7 );
			cvThreshold(greyTemp, binAux, 1 ,255, CV_THRESH_BINARY);
			

			cvFlip(binAux,binAux,1);

			cvClearMemStorage( g_storage );
					
			static bool firstRun = true;
			static double oldXX = 0, oldYY = 0;

			if(line){
				this->line->v->processeImage(greyTemp );
			}

			if(roizinho > 1.01){
				cvSetImageROI(binAux, roi);
				
				bin = binAux;
				cvResetImageROI(binAux);

				cvSetImageROI(colorTemp, roi);
				depth_as_color_roi = colorTemp;
				cvResetImageROI(colorTemp);
				colorDepthView->setImage(depth_as_color_roi);
			}
			else{
				bin = binAux;
				colorDepthView->setImage(depth_as_color);
			}
			binView->setImage(bin);
			//diffView->setImage(diff);
		}
	}

	private:
		IplImage *raw_rgb;
		cv::Mat3b rgb;
		IplImage *raw_depth;
		cv::Mat1f depth;

		bool firstRun;
		Kinect* kinect;
		cv::Mat3b depth_as_color;
		cv::Mat3b depth_as_color_roi;
		cv::Mat1f masked_distance;
		IplImage* colorTemp;
		IplImage* greyTemp;
		IplImage* binAux;
		CvMemStorage* 	g_storage;
		CvMemStorage *defect_storage;
		IplImage* contours;
		cv::Mat1f bin;
		cv::Mat3b old;
		cv::Mat3b diff;
		double minDepth;//140;
		double maxDepth;//242;
		double roizinho;//242;
		CvRect roi;
		CvRect depthRoi;

		int oldMax;
		int oldMin;

		ntk::ImageWidget *binView;
		ntk::ImageWidget *colorDepthView;

		//PointMagnet* magnet;
		Lines* line;
		int m_argc;
		char** m_argv;

		void setupWindows(){
			QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
			sizePolicy1.setHorizontalStretch(0);
			sizePolicy1.setVerticalStretch(0);
			//sizePolicy1.setHeightForWidth(colorView->sizePolicy().hasHeightForWidth());
			sizePolicy1.setHeightForWidth(false);
			
			colorDepthView = new ntk::ImageWidget(this->widgetTopLeft);
			colorDepthView->setObjectName(QString::fromUtf8("colorDepthView"));
			colorDepthView->setSizePolicy(sizePolicy1);
			colorDepthView->setFixedSize(320,240);

			binView = new ntk::ImageWidget(this->widgetTopRight);
			binView->setObjectName(QString::fromUtf8("binView"));
			binView->setSizePolicy(sizePolicy1);
			binView->setFixedSize(320,240);
		}

		void changeFixedDepth(int value, bool max){
			if(max){
				double max_meters = this->maxSlider->value()/100.0;
				maxDepth = max_meters*1.5;
				this->labelMaxSlider->setText(QString("Max Slider: %1 m").arg(maxDepth, 0, 'f', 2));

				int diff = value - oldMax;
				oldMin += diff;
				double min_meters = oldMin/100.0;
				minDepth = min_meters*1.5;
				this->minSlider->setValue(oldMin);
				this->labelMinSlider->setText(QString("Min Slider: %1 m").arg(minDepth, 0, 'f', 2));

				oldMax = value;
				
			}
			else{
				double min_meters = this->minSlider->value()/100.0;
				minDepth = min_meters*1.5;
				this->labelMinSlider->setText(QString("Min Slider: %1 m").arg(minDepth, 0, 'f', 2));

				int diff = value - oldMin;
				oldMax += diff;
				double max_meters = oldMax/100.0;
				maxDepth = max_meters*1.5;
				
				this->maxSlider->setValue(oldMax);
				this->labelMaxSlider->setText(QString("Max Slider: %1 m").arg(maxDepth, 0, 'f', 2));

				oldMin = value;
				
			}
		}
};

#endif