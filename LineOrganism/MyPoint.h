#ifndef _MY_POINT
#define _MY_POINT

class MagneticPoint;

class MyPoint{
	friend class MagneticPoint;
	public:
		//Contructors
		MyPoint();
		MyPoint(int xx, int yy, int zz);
		//MyPoint(float xx, float yy, float zz);
		MyPoint(double xx, double yy, double zz);
		~MyPoint();

		//Methods
		double x(){return coord[0];}
		double y(){return coord[1];}
		double z(){return coord[2];}
		double r(){return color[0];}
		double g(){return color[1];}
		double b(){return color[2];}

		void increment(double xx, double yy, double zz);

		void update(int xx, int yy, int zz);
		void update(double xx, double yy, double zz);

		void setColor(double rr, double gg, double bb);

		MyPoint* getMe(){return this;}

		//int it;
	private:
		double coord[3];
		double color[3];
};

#endif