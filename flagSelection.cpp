#include "flagSelection.h"


flagSelection::flagSelection(CGFtexture *t)
{	//<cylinder base="5" top="2" height="0.5" slices="20" stacks="6" />

	pole =new cylinder(0.2,0.2,1,20,6);

	flag = new Flag(t);

}


flagSelection::~flagSelection(void)
{
}


void flagSelection::draw()
{
	
	glPushMatrix();
	glScaled(1,1,1.2);
	pole->draw();
	glPopMatrix();

	glPushMatrix();
	flag->draw();
	glPopMatrix();
}

void flagSelection::draw(int x, int y){
	
	glPushMatrix();
	if (x == 0 || y==0 || x==4 || y==6)
		glTranslated(x+0.5,1.25,y+0.5);
	else
		glTranslated(x+0.5,2.50, y+0.5);

	glRotated(90,1,0,0);
	glPushMatrix();
	glScaled(0.5,0.5,1.2);
	pole->draw();
	glPopMatrix();

	glPushMatrix();
	flag->draw();
	glPopMatrix();
	glPopMatrix();

}



void flagSelection::update(unsigned long millis)
{
	flag->update(millis);
}

void flagSelection::setWind(int wind)
{
	flag->setWind(wind);
}