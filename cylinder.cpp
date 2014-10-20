#include "cylinder.h"

using namespace std;

cylinder::cylinder(float base,float top,float height,int slices,int stacks)
{
	this->base = base;
	this->top = top;
	this->height = height;
	this->slices = slices;
	this->stacks = stacks;

	quad = gluNewQuadric();
	disk1 = gluNewQuadric();
	disk2 = gluNewQuadric();

	gluQuadricTexture(quad,GL_TRUE);
	gluQuadricTexture(disk1,GL_TRUE);
	gluQuadricTexture(disk2,GL_TRUE);

	gluQuadricDrawStyle(quad,GLU_FILL);
	gluQuadricNormals(quad,GLU_SMOOTH);
	gluQuadricOrientation(quad,GLU_OUTSIDE);
}

void cylinder::draw()
{
	gluCylinder(quad,base,top,height,slices,stacks);

	if(top > 0)
	{
		glPushMatrix();
		glTranslated(0,0,height);
		gluDisk(disk1,0,top,slices,stacks);
		glPopMatrix();
	}
	glPushMatrix();
	glRotated(180,0,1,0);
	gluDisk(disk2,0,base,slices,stacks);
	glPopMatrix();

}

vector<float> cylinder::getCoords() const{
	vector<float> ret;

	ret.push_back(base);
	ret.push_back(top);
	ret.push_back(height);

	return ret;
}

int cylinder::getSlices()const
{
	return slices;
}

int cylinder::getStacks()const
{
	return stacks;
}




cylinder::~cylinder(void)
{
	/*
	gluDeleteQuadric(quad);
	gluDeleteQuadric(disk1);
	gluDeleteQuadric(disk2);
	*/
}
