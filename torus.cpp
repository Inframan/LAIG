#include "torus.h"


torus::torus(float inner, float outer, int slices, int loops)
{
	this->inner = inner;
	this->outer = outer;
	this->slices= slices;
	this->loops = loops;
}

float torus::getInner()const
{
	return inner;
}
float torus::getOuter()const
{
	return outer;
}
int torus::getSlices()const
{
	return slices;
}
int torus::getLoops()const
{
	return loops;
}


torus::~torus(void)
{
}
