#pragma once
class cylinder
{
	float base;
	float top;
	float height;
	int slices;
	int stacks;
public:
	cylinder(float base,float top,float height,int slices,int stacks);
	~cylinder(void);
};

