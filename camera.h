#pragma once
#include <string>
#include <vector>
#include "CGFcamera.h"
#include "CGFapplication.h"

using namespace std;
class camera :public CGFcamera
{
	string id;
	float near,far;
	string type;
public:
	camera();
	camera(string id,float near, float far);
	string getID()const;
	float getNear()const;
	float getFar()const;
	void setType(string t);
	string getType()const;
	virtual void apply() = 0;
	~camera(void);
	
};

