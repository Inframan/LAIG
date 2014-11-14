#pragma once
#include "primitive.h"
class plane :
	public primitive
{
	int parts;
	float ***ctrlpoints;
	float ***nrmcomponents;
	float ***texpoints;

public:
	plane(void);
	plane(int p);
	void draw();
	~plane(void);
};

