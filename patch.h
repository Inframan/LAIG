#pragma once
#include "primitive.h"
class patch :
	public primitive
{
	int order,partsU,partsV;
	float ** controlPoints;
	int compute;
public:
	patch(void);
	patch(int order,int partsU,int partsV,string compute,float ** controlPoints);
	void draw();
	~patch(void);
};

