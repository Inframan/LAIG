#include "camera.h"


camera::camera()
{
}


camera::camera(string id,float near,float far)
{
	this->id = id;
	this->near = near;
	this->far = far;
}

void camera::setType(string t)
{
	type = t;
}

string camera::getType()const
{
	return type;
}


string camera::getID()const
{
	return id;
}

float camera::getNear()const
{
		return near;
}

float camera::getFar()const
{
	return far;
}

camera::~camera(void)
{
}
