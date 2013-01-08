#include "MagnetPoint.h"

MagneticPoint::MagneticPoint() : MyPoint(), gravity(false), home(true){
	this->direction[0] = 0.0;
	this->direction[1] = 1.0;
	this->direction[2] = 0.0;

	this->origin[0] = 0.0;
	this->origin[1] = 0.0;
	this->origin[2] = 0.0;

	this->center[0] = 0.0;
	this->center[1] = 0.0;
	this->center[2] = 0.0;

	this->step = 0.01;
}

MagneticPoint::MagneticPoint(int posX, int posY, int posZ) : MyPoint(posX, posY, posZ), gravity(false), home(true){
	this->direction[0] = 0.0;
	this->direction[1] = 1.0;
	this->direction[2] = 0.0;

	this->center[0] = 0.0;
	this->center[1] = 0.0;
	this->center[2] = 0.0;

	this->origin[0] = posX;
	this->origin[1] = posY;
	this->origin[2] = posZ;

	this->step = 0.01;
}

MagneticPoint::MagneticPoint(double posX, double posY, double posZ) : MyPoint(posX, posY, posZ), gravity(false), home(true){
	this->direction[0] = 0.0;
	this->direction[1] = 1.0;
	this->direction[2] = 0.0;

	this->origin[0] = posX;
	this->origin[1] = posY;
	this->origin[2] = posZ;

	this->center[0] = 0.0;
	this->center[1] = 0.0;
	this->center[2] = 0.0;

	this->step = 0.01;
}

MagneticPoint::~MagneticPoint(){

}


void MagneticPoint::setDirection(double xx, double yy, double zz){
	this->direction[0] = xx;
	this->direction[1] = yy;
	this->direction[2] = zz;
}

void MagneticPoint::incDirection(double xx, double yy, double zz){
	this->direction[0] += xx;
	this->direction[1] += yy;
	this->direction[2] += zz;
}

void MagneticPoint::updatePosition(){
	if(gravity){
		if(newCenter){
			this->setDirection(this->center[0] - this->x(),this->center[1] - this->y(),this->center[2] - this->z());
			normaliza(this->direction);
			this->newCenter = false;
		}
		float dist = distancia(this->coord,this->center);
		if(dist > 0.2){
				this->increment((this->step * this->direction[0]),
						(this->step * this->direction[1]),
						(this->step * this->direction[2]));
		}
		/*if(dist < 4){
			this->setColor(AMARELO);
		}
		else{
			this->setColor(BRANCO);
		}*/
	}
	else{
		//this->setColor(BRANCO);
		if(home){
			if(newCenter){
				this->setGravityPoint(randomDouble(origin[0] - 2.5, origin[0] + 2.5),0.0,randomDouble(origin[2] - 2.5, origin[2] + 2.5));
				//this->setGravityPoint(randomDouble(-60, 60),0.0,randomDouble(-45, 45));
				this->setDirection(this->center[0] - this->x(),this->center[1] - this->y(),this->center[2] - this->z());
				normaliza(this->direction);
				this->newCenter = false;
			}

			this->increment((this->step * this->direction[0]),
							(this->step * this->direction[1]),
							(this->step * this->direction[2]));

			if(distancia(this->coord,this->center) < 0.2){
				this->newCenter = true;
			}
			//if(!newCenter){
			//	this->setGravityPoint(randomDouble(origin[0] - 2.5, origin[0] + 2.5),0.0,randomDouble(origin[2] - 2.5, origin[2] + 2.5));

			//	this->setDirection(this->center[0] - this->x(),this->center[1] - this->y(),this->center[2] - this->z());
			//	normaliza(this->direction);
			//}
			//else{
			//	this->increment((this->step * this->direction[0]),
			//					(this->step * this->direction[1]),
			//					(this->step * this->direction[2]));

			//	if(distancia(this->coord,this->origin) < 0.2){
			//		this->newCenter = false;
			//	}
			//}
		}
		else{
			this->setDirection(this->origin[0] - this->x(),this->origin[1] - this->y(),this->origin[2] - this->z());
			normaliza(this->direction);

			this->increment((this->step * this->direction[0]),
							(this->step * this->direction[1]),
							(this->step * this->direction[2]));

			if(distancia(this->coord,this->origin) < 0.2){
				this->home = true;
				this->newCenter = true;
			}
		}
	}
}

void MagneticPoint::setGravityPoint(double xx, double yy, double zz){
	this->center[0] = xx;
	this->center[1] = yy;
	this->center[2] = zz;

	this->newCenter = true;
}
