#pragma once
#include <vector>
#include "CGFobject.h"

class cylinder
{
	float base;
	float top;
	float height;
	int slices;
	int stacks;
	GLUquadric * quad,*disk1,*disk2;
public:
	cylinder(float base,float top,float height,int slices,int stacks);
	std::vector<float> getCoords() const;
	int getSlices()const;
	int getStacks()const;
	void draw();
	~cylinder(void);
};

