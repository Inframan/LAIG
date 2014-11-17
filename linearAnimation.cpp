#include "linearAnimation.h"

using namespace std;

linearAnimation::linearAnimation(void)
{
	current_point = 0;
	firstTime = true;
	setFinish(false);
}

linearAnimation::linearAnimation(string id,float span):animation(id,span)
{
	current_point = 0;
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
			unsigned long delta = t - firstTime;
			float thisSpan = (float) (t - getStartTime())*1000;
			if(thisSpan > getSpan())
			{
				setFinish(true);
			}


			previousTime = t;
		}
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

}

linearAnimation::~linearAnimation(void)
{
}
