#include "ovni.h"


ovni::ovni(void)
{
	
	//<cylinder base="5" top="2" height="0.5" slices="20" stacks="6" />
	upperDisk =new cylinder(5,2,0.5,20,6);
	lowerDisk =new cylinder(2,5,0.5,20,6);
	pole =new cylinder(0.2,0.2,5,20,6);

	vector<float> controlPoints;

	


	controlPoints.push_back(0);
	controlPoints.push_back(0);
	controlPoints.push_back(0);

	controlPoints.push_back(0.33);
	controlPoints.push_back(0);
	controlPoints.push_back(0);

	controlPoints.push_back(0.66);
	controlPoints.push_back(0);
	controlPoints.push_back(0);

	controlPoints.push_back(1);
	controlPoints.push_back(0);
	controlPoints.push_back(0);
	////
	controlPoints.push_back(0);
	controlPoints.push_back(0);
	controlPoints.push_back(0.33);

	controlPoints.push_back(-0.25);
	controlPoints.push_back(0.2);
	controlPoints.push_back(-0.25);

	
	controlPoints.push_back(0.9);
	controlPoints.push_back(0.2);
	controlPoints.push_back(-0.2);

	controlPoints.push_back(1);
	controlPoints.push_back(0.3);
	controlPoints.push_back(0.33);

	////
	controlPoints.push_back(0);
	controlPoints.push_back(0);
	controlPoints.push_back(0.66);

	
	controlPoints.push_back(0.7);
	controlPoints.push_back(0.5);
	controlPoints.push_back(0);

	controlPoints.push_back(0.25);
	controlPoints.push_back(0.4);
	controlPoints.push_back(-0.25);

	controlPoints.push_back(1);
	controlPoints.push_back(0.5);
	controlPoints.push_back(0.66);

	////
	controlPoints.push_back(0);
	controlPoints.push_back(0);
	controlPoints.push_back(0.66);

	controlPoints.push_back(0.75);
	controlPoints.push_back(0.66);
	controlPoints.push_back(0.15);

	controlPoints.push_back(0.66);
	controlPoints.push_back(0);
	controlPoints.push_back(0.15);

	controlPoints.push_back(1);
	controlPoints.push_back(0);
	controlPoints.push_back(1);
	
	char* compute = "fill";
	cockpit =new patch(3,20,20,compute,controlPoints);
	flag = new Flag(new CGFtexture("textures/flagOfMyPeople.gif"));
}

void ovni::draw()
{
	glPushMatrix();
	glRotated(-90,1,0,0);
	glPushMatrix();
	
	glTranslated(0,0,0);
	lowerDisk->draw();
	glPopMatrix();
	
	glPushMatrix();	
	glTranslated(0,0,0.5);
	upperDisk->draw();
	glPopMatrix();


	glPushMatrix();
	glTranslated(3,0,0.5);
	pole->draw();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0,0,5);
	glRotated(180,1,0,0);
	glRotated(90,0,1,0);
	flag->draw();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-3,0,0.5);
	pole->draw();
	glPopMatrix();
	
	glPushMatrix();
	glTranslated(0,0,0.2);
	glScaled(1,1,1.2);
	pole->draw();
	glPopMatrix();

	glPushMatrix();
	flag->draw();
	glPopMatrix();
	glPopMatrix();

	
	glPushMatrix();
	glTranslated(-4,2,0.8);
	glScaled(4,4,4);
	glRotated(180,0,0,1);
	glRotated(-75,1,0,0);
	glScaled(-2,-1,-1);
	cockpit->draw();
	glPopMatrix();
	
}


void ovni::update(unsigned long millis)
{
	flag->update(millis);
}

void ovni::setWind(int wind)
{
	flag->setWind(wind);
}

ovni::~ovni(void)
{
}
