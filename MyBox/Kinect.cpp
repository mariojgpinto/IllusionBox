#include "Kinect.h"

//namespace opt
//{
//	ntk::arg<bool> high_resolution("--highres", "High resolution color image.", 0);
//	ntk::arg<int> kinect_id("--kinect-id", "Kinect id", 0);
//}

Kinect::Kinect(QObject* parent){
	ni_driver = new OpenniDriver();
	
	grabber = new OpenniGrabber(*ni_driver);//,opt::kinect_id());
	//grabber->set_xml_config_file("C:\\Program Files (x86)\\OpenNI\\Data\\SamplesConfig.xml");

	grabber->connectToDevice();

	//ntk::RGBDCalibration * cal = grabber->calibrationData();

	//{
	//	ntk_dbg(0) << "[WARNING] Using kinect_calibration.yml in current directory";
	//	ntk_dbg(0) << "[WARNING] use --calibration to specify a different file.";
	//}
	//cal = new RGBDCalibration();
	//cal->loadFromFile("C:\\calibration_depth.yaml");
 // 
	//   	
	//grabber->setCalibrationData(*cal);

//	grabber->setHighRgbResolution(false);
//	grabber->setTrackUsers(false);
//	grabber->setMirrored(true);
////	grabber->setIRMode(true);

	//grabber->niRGBGenerator().SetIntProperty("InputFormat", 6);
	//if(grabber->niDepthGenerator().IsCapabilitySupported(XN_CAPABILITY_ALTERNATIVE_VIEW_POINT)){
	//	grabber->niDepthGenerator().GetAlternativeViewPointCap().SetViewPoint(grabber->niRGBGenerator());
	//}
	grabber->start();
	grabber->niDepthGenerator().SetIntProperty("RegistrationType",2);
	xn::ImageGenerator gen  = grabber->niRGBGenerator();
	grabber->niDepthGenerator().GetAlternativeViewPointCap().SetViewPoint(grabber->niRGBGenerator());
	


	start();
}

Kinect::~Kinect(){

	grabber->stop();
}

void Kinect::processKey(char key){
	switch(key){
		default:break;
	}
}

void Kinect::run(){
	char c = 0;

	while((c = (cv::waitKey(10) & 0xff)) != 27){
		this->processKey(c);

		grabber->waitForNextFrame();
		grabber->copyImageTo(image);
		
		processor.processImage(image);

		emit kinectImage(&image);
	}
}

void resizeImage(const IplImage *origImg, IplImage *dest){
	// Make the image smaller
	cvResetImageROI((IplImage*)origImg);
	cvResize(origImg, dest, CV_INTER_AREA);	// CV_INTER_AREA is good for shrinking / decimation, but bad at enlarging.
}