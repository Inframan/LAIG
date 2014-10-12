#pragma once
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
	~torus(void);
};

