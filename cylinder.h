#pragma once
#include <vector>

class cylinder
{
	float base;
	float top;
	float height;
	int slices;
	int stacks;
public:
	cylinder(float base,float top,float height,int slices,int stacks);
	std::vector<float> getCoords() const;
	int getSlices()const;
	int getStacks()const;
	~cylinder(void);
};

