#pragma once
#include "camera.h"
class perspective :
	public camera
{
	float angle;
	vector<float> pos,target;

public:
	perspective(string id,float near, float far, float angle,float x,float y,float z, float targetX,float targetY,float targetZ);
	float getAngle()const;
	vector<float> getPos()const;
	vector<float> getTarget()const;
	void apply();
	void applyView();
	~perspective(void);
};

