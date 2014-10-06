#include "cylinder.h"


cylinder::cylinder(float base,float top,float height,int slices,int stacks)
{
	this->base = base;
	this->top = top;
	this->height = height;
	this->slices = slices;
	this->stacks = stacks;
}


cylinder::~cylinder(void)
{
}
