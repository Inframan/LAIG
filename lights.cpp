#include "lights.h"


myLight::myLight(void)
{
}

myLight::myLight(string id,string type, bool enabled,bool marker, vector<float> pos)
{
	this->id=id;
	this->type=type;
	this->enabled = enabled;
	this->marker=marker;
	this->pos=pos;
}


void myLight::setSpecular(vector<float> specular)
{
	this->specular = specular;
}

void myLight::setAmbient(vector<float> ambient)
{
	this->ambient = ambient;
}

void myLight::setDiffuse(vector<float> diffuse)
{
	this->diffuse = diffuse;
}

vector<float> myLight::getAmbient()const
{
	return ambient;
}
	
vector<float> myLight::getSpecular()const
{
	return specular;
}
	
vector<float> myLight::getDiffuse()const
{
	return diffuse;
}



myLight::~myLight(void)
{
}
