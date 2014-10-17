#pragma once
#include <string>
#include <vector>
#include "CGFappearance.h"
#include "texture.h"
using namespace std;

class Appearence
{
	string id;
	float shininess;
	string textureref;
	vector<float> ambient_comp;
	vector<float> diffuse_comp;
	vector<float> specular_comp;
	CGFappearance* app;
	Texture* t;

public:
	Appearence(void);
	Appearence(string id, float shininess,string textureref);
	CGFappearance* getAppearance() const;
	void setAppearance(CGFappearance* app);
	string getID() const;
	void setID(string id);
	float getShininess() const;
	Texture* getTexture() const;
	void setTexture(Texture* t);
	void setShininess(float shininess);
	string getTextureref() const;
	void setTextureref(string textureref);
	vector<float> getAmbient() const;
	vector<float>  getDiffuse() const;
	vector<float>  getSpecular() const;

	void setAmbient(vector<float>  ambient_comp);
	void setDiffuse(vector<float>  diffuse_comp);
	void setSpecular(vector<float>  specular_comp);
	~Appearence(void);
};

