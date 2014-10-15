#pragma once
#include <string>
#include <vector>
using namespace std;

class myLight
{
	string id,type;
	vector<float> pos, ambient, diffuse,specular;
	bool enabled,marker;	
public:
	myLight(void);
	myLight(string id,string type, bool enabled,bool marker, vector<float> pos);
	void setSpecular(vector<float> specular);
	void setAmbient(vector<float> ambient);
	void setDiffuse(vector<float> diffuse);
	bool getEnabled()const;
	bool getMarker()const;
	vector<float> getAmbient()const;
	vector<float> getSpecular()const;
	vector<float> getDiffuse()const;
	vector<float> getPos()const;
	~myLight(void);
};

