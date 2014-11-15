#pragma once
#include "primitive.h"
class plane :
	public primitive
{
	int parts;

public:
	plane(void);
	plane(int p);
	void draw();
	~plane(void);
};

