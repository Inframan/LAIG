#include "rectangle.h"


rectangle::rectangle(float x1,float y1,float x2,float y2)
{
	this->x1 = x1;
	this->x2 = x2;
	this->y1 = y1;
	this->y2 = y2;

}


vector<float> rectangle:: getCoords() const
{
	vector<float> temp;
	temp.push_back(x1);
	temp.push_back(y1);
	temp.push_back(x2);
	temp.push_back(y2);
	return temp;
}

rectangle::~rectangle(void)
{
}
