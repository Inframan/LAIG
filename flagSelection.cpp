#include "flagSelection.h"


flagSelection::flagSelection(CGFtexture *t)
{	//<cylinder base="5" top="2" height="0.5" slices="20" stacks="6" />
	pole =new cylinder(0.2,0.2,5,20,6);

	flag = new Flag(t);

}


flagSelection::~flagSelection(void)
{
}


void flagSelection::draw()
{
	
	glPushMatrix();
	glTranslated(0,0,0.2);
	glScaled(1,1,1.2);
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