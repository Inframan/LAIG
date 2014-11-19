#pragma once
#include "primitive.h"
class patch :
	public primitive
{
	int order,partsU,partsV,compute;
	vector<float> controlPoints;
	vector<float> textPoints;
public:
	patch(void);
	patch(int order,int partsU,int partsV,string compute,vector<float> controlPoints);
	void draw();
	~patch(void);
};

