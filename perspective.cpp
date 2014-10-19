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


void perspective::apply()
{
	
	float n=getNear(), f=getFar();
	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angle, 1,n, f);
	glPopMatrix();
	gluLookAt(pos[0],pos[1],pos[2],target[0],target[1],target[2],0,1,0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}