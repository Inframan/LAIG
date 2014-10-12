#pragma once

#include "CGFobject.h"
#include <cmath>

class myTorus
{
	int slices, loops;
	bool smooth;
	float inner, outer;

public:
	myTorus(float inner, float outer, int slices, int loops);
	void draw();
	~myTorus(void);
};

