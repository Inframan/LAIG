#include "sphere.h"


sphere::sphere(float radius, int slices,int stacks)
{
	quad = gluNewQuadric();
	this->radius = radius;
	this->slices = slices;
	this->stacks = stacks;
}

float sphere::getRadius()const
{
	return radius;
}

int sphere::getSlices()const
{
	return slices;
}

int sphere::getStacks()const
{
	return stacks;
}

void sphere::draw()
{
	
	gluQuadricTexture(quad,GL_TRUE);
	gluQuadricDrawStyle(quad,GLU_FILL);
	gluQuadricNormals(quad,GLU_SMOOTH);
	gluQuadricOrientation(quad,GLU_OUTSIDE);

	gluSphere(quad,radius,slices,stacks);


}

sphere::~sphere(void)
{
	//gluDeleteQuadric(quad);
}
