#pragma once
#include "camera.h"
class orthogonal :
	public camera
{
	char direction;
	float left,right,top,bottom;
public:
	orthogonal(string id, char direction,float near,float far,float left,float right,float top,float bottom );
	float getLeft()const;
	float getRight()const;
	float getTop()const;
	float getBot()const;
	char getDirection()const;
	void apply();
	~orthogonal(void);
};

