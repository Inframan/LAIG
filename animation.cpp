#include "animation.h"

using namespace std;

animation::animation(void)
{
}

animation::animation(string id,float span)
{
	this->finished = false;
	this->id = id;
	this->span = span;
	this->loop = false;
}

animation::animation(string id,float span,bool loop)
{
	this->finished = false;
	this->id = id;
	this->span = span;
	this->loop = loop;
}

bool animation::getLoop()const
{
	return loop;
}

string animation::getId()const
{
	return id;
}

void animation::setStartTime(unsigned long t)
{
	startTime = t;
}

unsigned long animation::getStartTime()const
{
	return startTime;
}

float animation::getSpan()const
{
	return span;
}

void animation::setFinish(bool f)
{
	finished = f;
}

bool animation::isFinished()const
{
	return finished;
}

animation::~animation(void)
{
}
