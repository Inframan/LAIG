#pragma once
#include <string>
#include <vector>
using namespace std;

class myLight
{
	string id,type;
	vector<float> pos, ambient, diffuse,specular,target;
	float angle, exponent;
	bool enabled,marker;	
public:
	myLight(void);
	myLight(string id,string type, bool enabled,bool marker, vector<float> pos);
	void setSpecular(vector<float> specular);
	void setAmbient(vector<float> ambient);
	void setDiffuse(vector<float> diffuse);
	bool getEnabled()const;
	bool getMarker()const;
	void setTarget(vector<float> target);
	void setAngle(float angle);
	void setExponent(float exponent);
	vector<float> getAmbient()const;
	vector<float> getSpecular()const;
	vector<float> getDiffuse()const;
	vector<float> getPos()const;
	vector<float> getTarget()const;
	float getExponent()const;
	string getType()const;
	float getAngle()const;
	~myLight(void);
};

