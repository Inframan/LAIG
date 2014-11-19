#pragma once
#include "primitive.h"
class plane :
	public primitive
{
	int parts;

public:
	plane(void);
	plane(int p);
	virtual void draw();
	~plane(void);
	void setWind(int wind){}
};

