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
	angle = 0.0;
}

linearAnimation::linearAnimation(string id,float span):animation(id,span)
{
	angle = 0.0;
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
			float delta = (t - previousTime)/1000.0;
			float thisSpan = (float) (t - getStartTime())/1000;
			float span = getSpan();
			if(thisSpan > span)
			{
				setFinish(true);
			}

			x += dx*speed*delta;
			y +=dy*speed*delta;
			z +=dz*speed*delta;
			if(checkControlPoint())
				changeControlPoint();

			previousTime = t;
		}
	}
}

void linearAnimation::transform()
{
	glTranslated(x,y,z);
	glRotated(angle,0,1,0);
}


bool linearAnimation::checkControlPoint()
{
	if(dx > 0)
	{
		if(x > controlPoints[current_point+1][0])
			return true;
	}
	else	if(dx < 0)
	{
		if(x < controlPoints[current_point+1][0])
			return true;
	}

	if(dy > 0)
	{
		if(y > controlPoints[current_point+1][1])
			return true;
	}
	else if(dy < 0)
	{
		if(y < controlPoints[current_point+1][1])
			return true;
	}

	if(dz > 0)
	{
		if(z > controlPoints[current_point+1][2])
			return true;
	}
	else if(dz < 0)
	{
		if(z < controlPoints[current_point+1][2])
			return true;
	}

	return false;
}


void linearAnimation::changeControlPoint()
{
	float odx = dx,ody =dy,odz = dz;
	
	current_point++;
	int nextPoint = current_point+1;
	if(nextPoint == controlPoints.size())
		setFinish(true);
	else
	{
		float pointDistance;
		dx = controlPoints[nextPoint][0] - controlPoints[current_point][0];
		dy = controlPoints[nextPoint][1] - controlPoints[current_point][1];
		dz = controlPoints[nextPoint][2] - controlPoints[current_point][2];

		pointDistance = sqrt(dx*dx + dy*dy+dz*dz);

		dx /= pointDistance;
		dy /= pointDistance;
		dz /= pointDistance;

		angle += acos(dx*odx+dy*ody+dz*odz) *(180/acos(-1.0));
		
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
		float d1 = p1[0]-p2[0];
		float d2 = p1[1]-p2[1];
		float d3 = p1[2]-p2[2];

		totalDistance += sqrt(d1*d1 + d2*d2+d3*d3);
	}
	float span = getSpan();
	speed = totalDistance / getSpan();

	x = controlPoints[0][0];
	y = controlPoints[0][1];
	z = controlPoints[0][2];

}

linearAnimation::~linearAnimation(void)
{
}
