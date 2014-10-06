#include "triangle.h"


triangle::triangle(float x1,float y1,float z1,float x2,float y2,float z2,float x3,float y3,float z3)
{
	this->x1 = x1;
	this->y1 = y1;
	this->z1 = z1;
	
	this->x2 = x2;
	this->y2 = y2;
	this->z2 = z2;
	
	this->x3 = x3;
	this->y3 = y3;
	this->z3 = z3;
}


triangle::~triangle(void)
{
}
