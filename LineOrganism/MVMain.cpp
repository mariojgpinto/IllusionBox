#include "Variables.h"
#include "LineViewer.h"

#include <boost\thread.hpp>


unsigned int index = 0;
std::vector<IplImage*>* images;

void processKey(char c){
	switch(c){
		case '1':
			if(index < (images->size() - 1))
				index++;
			break;
		case '2':
			if(index > 0)
				index--;
			break;
		default:break;
	}
}

LineViewer v;

int coiso(int argc, char* argv[]){
	v.init(argc,argv,590,440);
	//
	v.setPointsPerBlob(202);
	for(int i = 0 ; i < 100 ; i++){
		v.addOrganism(3,randomDouble(-60,60),randomDouble(-45,45),12.5,2.0,10.0);
	}

	//v.addOrganism(10,randomDouble(-60,60),randomDouble(-45,45),12.5,2.0,10.0);
	//v.addOrganism(10,randomDouble(-60,60),randomDouble(-45,45),12.5,2.0,10.0);
	//v.addOrganism(10,randomDouble(-60,60),randomDouble(-45,45),12.5,2.0,10.0);
	//v.addOrganism(10,randomDouble(-60,60),randomDouble(-45,45),12.5,2.0,10.0);
	//v.addOrganism(10,randomDouble(-60,60),randomDouble(-45,45),12.5,2.0,10.0);
	//v.addOrganism(10,randomDouble(-60,60),randomDouble(-45,45),12.5,2.0,10.0);
	//v.addOrganism(10,randomDouble(-60,60),randomDouble(-45,45),12.5,2.0,10.0);
	//v.addOrganism(10,randomDouble(-60,60),randomDouble(-45,45),12.5,2.0,10.0);
	//v.addOrganism(10,randomDouble(-60,60),randomDouble(-45,45),12.5,2.0,10.0);
	//v.addOrganism(10,randomDouble(-60,60),randomDouble(-45,45),12.5,2.0,10.0);
	//v.addOrganism(9,randomDouble(-60,60),randomDouble(-45,45),12.5,2.0,10.0);

	//v.addOrganism(10,randomDouble(-60,60),randomDouble(-45,45),12.5,2.0,10.0);
	//v.addOrganism(10,randomDouble(-60,60),randomDouble(-45,45),12.5,2.0,10.0);
	//v.addOrganism(10,randomDouble(-60,60),randomDouble(-45,45),12.5,2.0,10.0);
	//v.addOrganism(10,randomDouble(-60,60),randomDouble(-45,45),12.5,2.0,10.0);
	//v.addOrganism(10,randomDouble(-60,60),randomDouble(-45,45),12.5,2.0,10.0);
	//v.addOrganism(10,randomDouble(-60,60),randomDouble(-45,45),12.5,2.0,10.0);
	//v.addOrganism(10,randomDouble(-60,60),randomDouble(-45,45),12.5,2.0,10.0);
	//v.addOrganism(10,randomDouble(-60,60),randomDouble(-45,45),12.5,2.0,10.0);
	//v.addOrganism(10,randomDouble(-60,60),randomDouble(-45,45),12.5,2.0,10.0);
	//v.addOrganism(10,randomDouble(-60,60),randomDouble(-45,45),12.5,2.0,10.0);
	//v.addOrganism(9,randomDouble(-60,60),randomDouble(-45,45),12.5,2.0,10.0);


	//v.addOrganism(5,0.0,0.0,12.5,2.0,10.0);
	//v.addOrganism(4,randomDouble(-60,60),randomDouble(-45,45),12.5,2.0,10.0);
	//v.addOrganism(5,randomDouble(-60,60),randomDouble(-45,45),12.5,2.0,10.0);
	//v.addOrganism(3,randomDouble(-60,60),randomDouble(-45,45),12.5,2.0,10.0);
	//v.addOrganism(3,randomDouble(-60,60),randomDouble(-45,45),12.5,2.0,10.0);
	//v.addOrganism(3,randomDouble(-60,60),randomDouble(-45,45),12.5,2.0,10.0);
	//v.addOrganism(3,randomDouble(-60,60),randomDouble(-45,45),12.5,2.0,10.0);
	//v.addOrganism(3,randomDouble(-60,60),randomDouble(-45,45),12.5,2.0,10.0);
	//v.addOrganism(3,randomDouble(-60,60),randomDouble(-45,45),12.5,2.0,10.0);
	//v.addOrganism(3,randomDouble(-60,60),randomDouble(-45,45),12.5,2.0,10.0);
	//v.addOrganism(3,randomDouble(-60,60),randomDouble(-45,45),12.5,2.0,10.0);
	//v.addOrganism(3,randomDouble(-60,60),randomDouble(-45,45),12.5,2.0,10.0);
	//v.addOrganism(3,randomDouble(-60,60),randomDouble(-45,45),12.5,2.0,10.0);
	//v.addOrganism(3,randomDouble(-60,60),randomDouble(-45,45),12.5,2.0,10.0);
	//v.addOrganism(3,randomDouble(-60,60),randomDouble(-45,45),12.5,2.0,10.0);
	//v.addOrganism(3,randomDouble(-60,60),randomDouble(-45,45),12.5,2.0,10.0);
	//v.addOrganism(3,randomDouble(-60,60),randomDouble(-45,45),12.5,2.0,10.0);
	//v.addOrganism(3,randomDouble(-60,60),randomDouble(-45,45),12.5,2.0,10.0);
	//v.addOrganism(3,randomDouble(-60,60),randomDouble(-45,45),12.5,2.0,10.0);
	//v.addOrganism(3,randomDouble(-60,60),randomDouble(-45,45),12.5,2.0,10.0);
	//v.addOrganism(3,randomDouble(-60,60),randomDouble(-45,45),12.5,2.0,10.0);
	//v.addOrganism(3,randomDouble(-60,60),randomDouble(-45,45),12.5,0.5,10.0);
	//v.addOrganism(3,randomDouble(-60,60),randomDouble(-45,45),12.5,0.5,10.0);
	


	v.run();
	return 0;
}

int main(int argc, char* argv[]){
	boost::thread(&coiso,argc,argv);
	
	images = new std::vector<IplImage*>();

	char buff[512];
	for(unsigned int i = 1 ; i < 4 ; i++){
		sprintf(buff,"Imagens/image%d.jpg",i);
		images->push_back(cvLoadImage(buff,0));
	}

	char c = -1; 	
	IplImage*temp = cvCreateImage(cvSize(590,440),8,1);
	while( c != 27 ){
		processKey(c);
		cvZero(temp);
		//temp = images->at(index);
		cvCopy(images->at(index),temp);

		v.processeImage(temp);
		
		c = cvWaitKey(10000);
		index = ( index + 1 ) % 3;
	}

	//while(true){
	//	Sleep(1000);
	//	printf("sleep\n");
	//}

	return 0;
}

