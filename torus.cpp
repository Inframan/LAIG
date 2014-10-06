#include "torus.h"


torus::torus(float inner, float outer, int slices, int loops)
{
	this->inner = inner;
	this->outer = outer;
	this->slices= slices;
	this->loops = loops;
}


torus::~torus(void)
{
}
