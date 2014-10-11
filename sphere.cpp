#include "sphere.h"


sphere::sphere(float radius, int slices,int stacks)
{
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


sphere::~sphere(void)
{
}
