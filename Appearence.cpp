#include "Appearence.h"


Appearence::Appearence(void)
{
}


Appearence::~Appearence(void)
{
}


Appearence::Appearence(string id, float shininess,string textureref){

	this->id=id;
	this->shininess=shininess;
	this->textureref=textureref;

}


CGFappearance* Appearence::getAppearance() const{

	return app;
}
	

void Appearence::setAppearance(CGFappearance* app){

	this->app=app;
}


Texture* Appearence::getTexture() const{
	return t;
}

void Appearence::setTexture(Texture* t){
	this->t = t;
}
	
string Appearence::getID() const{
	return id;
}

void Appearence::setID(string id)
{
	this->id=id;
}

float Appearence::getShininess() const{
	return shininess;
}
void Appearence::setShininess(float shininess){
	this->shininess=shininess;
}

string Appearence::getTextureref() const{
	return textureref;
}

void Appearence::setTextureref(string textureref){
	this->textureref=textureref;
}
vector<float>  Appearence::getAmbient() const{
	return ambient_comp;
}
vector<float>  Appearence::getDiffuse() const{
	return diffuse_comp;
}

vector<float> Appearence::getSpecular() const{
	return specular_comp;
}
void Appearence::setAmbient(vector<float>  ambient_comp){
	this->ambient_comp=ambient_comp;
}

void Appearence::setDiffuse(vector<float>  diffuse_comp){
	this->diffuse_comp=diffuse_comp;
}

void Appearence::setSpecular(vector<float>  specular_comp){
	this->specular_comp=specular_comp;
}
