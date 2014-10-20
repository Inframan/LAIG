#pragma once
#include "primitive.h"
#include "CGFobject.h"
class sphere:public primitive
{
	float radius;
	int slices;
	int stacks;
	GLUquadric * quad;

public:
	sphere(float radius, int slices,int stacks);
	float getRadius()const;
	int getSlices()const;
	int getStacks()const;
	void draw();
	~sphere(void);
};

