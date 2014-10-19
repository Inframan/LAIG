#pragma once
#include <cmath>
#include "CGFobject.h"

class torus
{
	float inner;
	float outer;
	int slices;
	int loops;
public:
	torus(float inner, float outer, int slices, int loops);
	float getInner()const;
	float getOuter()const;
	int getSlices()const;
	int getLoops()const;
	void draw();
	~torus(void);
};

