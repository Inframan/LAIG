#pragma once
#include "primitive.h"

using namespace std;

class rectangle : public primitive
{
	float x1, y1, x2, y2;

public:
	rectangle(float x1,float y1,float x2,float y2);
	vector<float> getCoords() const;
	void draw();
	void draw(Texture * t);
	~rectangle(void);
};

