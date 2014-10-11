#include "cylinder.h"

using namespace std;

cylinder::cylinder(float base,float top,float height,int slices,int stacks)
{
	this->base = base;
	this->top = top;
	this->height = height;
	this->slices = slices;
	this->stacks = stacks;
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
}
