#pragma once
class sphere
{
	float radius;
	int slices;
	int stacks;
public:
	sphere(float radius, int slices,int stacks);
	float getRadius()const;
	int getSlices()const;
	int getStacks()const;
	~sphere(void);
};

