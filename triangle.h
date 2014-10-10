#pragma once
#include <vector>

class triangle
{
	float x1, y1, z1, x2, y2, z2, x3, y3, z3;
public:
	triangle(float x1,float y1,float z1,float x2,float y2,float z2,float x3,float y3,float z3);
	std::vector<float> getCoords() const;
	~triangle(void);
};

