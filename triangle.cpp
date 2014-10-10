#include "triangle.h"

using namespace std;

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

vector<float> triangle::getCoords()const
{
	vector<float> temp;
	temp.push_back(x1);
	temp.push_back(y1);
	temp.push_back(z1);
	temp.push_back(x2);
	temp.push_back(y2);
	temp.push_back(z2);
	temp.push_back(x3);
	temp.push_back(y3);
	temp.push_back(z3);
	return temp;
}

triangle::~triangle(void)
{
}
