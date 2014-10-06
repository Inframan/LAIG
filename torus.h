#pragma once
class torus
{
	float inner;
	float outer;
	int slices;
	int loops;
public:
	torus(float inner, float outer, int slices, int loops);
	~torus(void);
};

