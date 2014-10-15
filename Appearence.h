#pragma once
#include <string>
#include <vector>
using namespace std;
class Appearence
{
	string id;
	float shininess;
	string textureref;
	vector<float> ambient_comp;
	vector<float> diffuse_comp;
	vector<float> specular_comp;

public:
	Appearence(void);
	Appearence(string id, float shininess,string textureref);
	string getID() const;
	void setID(string id);
	float getShininess() const;
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

