#include "linearAnimation.h"

using namespace std;

linearAnimation::linearAnimation(void)
{
	dx = 0;
	dy = 0;
	dz = 0;
	x = 0;
	y = 0;
	z = 0;
	totalDistance = 0;
	speed = 0;
	current_point = -1;
	firstTime = true;
	setFinish(false);
}

linearAnimation::linearAnimation(string id,float span):animation(id,span)
{
	dx = 0;
	dy = 0;
	dz = 0;
	x = 0;
	y = 0;
	z = 0;
	totalDistance = 0;
	speed = 0;
	current_point = -1;
	firstTime = true;
	setFinish(false);
}

void linearAnimation::addPoint(float x,float y,float z)
{
	vector<float> point;
	point.push_back(x);
	point.push_back(y);
	point.push_back(z);
	controlPoints.push_back(point);
}

void linearAnimation::update(unsigned long t)
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
			unsigned long delta = t - getStartTime();
			float thisSpan = (float) (t - getStartTime())/1000;
			if(thisSpan > getSpan())
			{
				setFinish(true);
			}

			x += dx*speed*delta/1000;
			y +=dy*speed*delta/1000;
			z +=dz*speed*delta/1000;
			if(checkControlPoint())
				changeControlPoint();

			previousTime = t;
		}
	}
}

void linearAnimation::transform()
{
	glTranslated(x,y,z);
}


bool linearAnimation::checkControlPoint()
{
	if(dx > 0)
	{
		if(x > controlPoints[current_point+1][0])
			return true;
	}
	else	if(dx > 0)
	{
		if(x < controlPoints[current_point+1][0])
			return true;
	}

	if(dy > 0)
	{
		if(y > controlPoints[current_point+1][1])
			return true;
	}
	else if(dy > 0)
	{
		if(y < controlPoints[current_point+1][1])
			return true;
	}

	if(dz > 0)
	{
		if(z > controlPoints[current_point+1][2])
			return true;
	}
	else if(dz > 0)
	{
		if(z < controlPoints[current_point+1][2])
			return true;
	}

	return false;
}


void linearAnimation::changeControlPoint()
{
	current_point++;
	if(current_point == controlPoints.size()-1)
		setFinish(true);
	else
	{
		float pointDistance;
		dx = controlPoints[current_point+1][0] - controlPoints[current_point][0];
		dy = controlPoints[current_point+1][1] - controlPoints[current_point][1];
		dz = controlPoints[current_point+1][2] - controlPoints[current_point][2];

		pointDistance = sqrt(dx*dx + dy*dy+dz*dz);

		dx /= pointDistance;
		dy /= pointDistance;
		dz /= pointDistance;

		x = controlPoints[current_point][0];
		y = controlPoints[current_point][1];
		z = controlPoints[current_point][2];
	}
}

void linearAnimation::calculateTotalDistance()
{
	totalDistance = 0.0;
	vector<float> p1;
	vector<float> p2;
	for(int i =0;  i < controlPoints.size()-1;i++)
	{
		p1 = controlPoints[i];
		p2 = controlPoints[i+1];
		float x = p1[0]-p2[0];
		float y = p1[1]-p2[1];
		float z = p1[2]-p2[2];

		totalDistance += sqrt(x*x + y*y+z*z);
	}

	speed = totalDistance / getSpan();

	x = controlPoints[0][0];
	y = controlPoints[0][1];
	z = controlPoints[0][2];

}

linearAnimation::~linearAnimation(void)
{
}
