#pragma once
#include <cmath>
#include "CGFobject.h"
#include <vector>

using namespace std;

class torus
{
	float inner;
	float outer;
	int slices;
	int loops;
	vector<float> x;
	vector<float> y;
	vector<float> c;
	vector<float> r;
	vector<float> z;

	double pi;
	float vNormal[3];   
	double majorStep;
	double minorStep;   
public:
	torus(float inner, float outer, int slices, int loops);
	float getInner()const;
	float getOuter()const;
	int getSlices()const;
	int getLoops()const;
	void draw();
	~torus(void);
};

