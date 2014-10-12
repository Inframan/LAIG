#include "myTorus.h"


myTorus::myTorus(float inner, float outer, int slices, int loops)
{
	this->inner = inner;
	this->outer = outer;
	this->slices = slices;
	this->loops = loops;
}

void myTorus::draw()
{
	double myPi = acos(-1.0);
	double a=0;
	double l = 0;
	double da =360/ (double) slices;
	double dl = 360/ (double) loops;

	double x1 = inner , y1=0.0; 
	a+=da;
	l+=dl;
	double x2=cos(a*myPi/180);
	double y2=sin(a*myPi/180);
	double z1 = 1;
	double z2 = sin(l*myPi/180);

	for (int i = 0 ; i < slices ; i++)
	{

		for ( int j=0 ; j < loops ;j++)
		{

			glBegin(GL_QUADS);
			glVertex3d(x1,y1,z1);
			
			glVertex3d(x2,y2,z1);
			
			glVertex3d(x2,y2,z2);
			
			glVertex3d(x1,y1,z2);
			glEnd();
			z1 = z2;
			z2 =sin(l*myPi/180);
			l+=dl;
		}

		x1 = x2;
		y1 = y2;

		a+=da;

		x2=cos(a*myPi/180);
		y2=sin(a*myPi/180);
	}	


}


myTorus::~myTorus(void)
{
}
