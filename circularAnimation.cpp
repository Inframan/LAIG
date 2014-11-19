#include "circularAnimation.h"

using namespace std;
circularAnimation::circularAnimation(void)
{
	firstTime = true;
}

circularAnimation::circularAnimation(string id,float span,float cx,float cy,float cz,float rotAng,float startAng,float radius):animation(id,span)
{
	firstTime = true;
	
	this->cx = cx;
	this->cy = cy;
	this->cz = cz;
	this->rotAng = rotAng;
	this->angle = startAng;
	this->radius = radius;
	speed = (float) rotAng/getSpan();
	
	float radAngle = angle*(acos(-1)/180);
	x = radius*cos(radAngle);
	z = radius*cos(radAngle);
}


circularAnimation::circularAnimation(string id,float span,float cx,float cy,float cz,float rotAng,float startAng,float radius,bool loop):animation(id,span,loop)
{
	firstTime = true;
	
	this->cx = cx;
	this->cy = cy;
	this->cz = cz;
	this->rotAng = rotAng;
	this->angle = startAng;
	this->radius = radius;
	speed = (float) rotAng/getSpan();
	
	float radAngle = angle*(acos(-1)/180);
	x = radius*cos(radAngle);
	z = radius*cos(radAngle);
}


void circularAnimation::transform()
{
	glTranslated(cx,cy,cz);
	glRotated(angle,0,1,0);	
	glTranslated(x,0,z);
}

void circularAnimation::update(unsigned long t)
{
	
	if(!isFinished())
	{
		if(firstTime)
		{
			previousTime = t;
			firstTime = false;
			setStartTime(t);
		}
		else
		{
			float delta = (t - previousTime)/1000.0;
			float thisSpan = (float) (t - getStartTime())/1000;
			float span = getSpan();
			if(thisSpan > span && !getLoop())
			{
				setFinish(true);
			}

			angle += speed*delta;

			previousTime = t;
		}
	}
}


circularAnimation::~circularAnimation(void)
{
}
