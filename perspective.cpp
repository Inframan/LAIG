#include "perspective.h"


perspective::perspective(string id,float near, float far, float angle,float x,float y,float z, float targetX,float targetY,float targetZ):camera(id,near,far)
{	
	this->angle = angle;
	pos.push_back(x);
	pos.push_back(y);
	pos.push_back(z);
	target.push_back(targetX);
	target.push_back(targetY);
	target.push_back(targetZ);
	setType("perspective");
}

float perspective::getAngle()const
{
	return angle;
}
	
vector<float> perspective::getPos()const
{
	return pos;
}
	
vector<float> perspective::getTarget()const
{
	return target;
}


perspective::~perspective(void)
{
}
