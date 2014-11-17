#pragma once
#include "primitive.h"
class patch :
	public primitive
{
	int order,partsU,partsV,compute;
	GLfloat ** controlPoints;
	float ** textPoints;
public:
	patch(void);
	patch(int order,int partsU,int partsV,string compute,float ** controlPoints);
	void draw();
	~patch(void);
};

