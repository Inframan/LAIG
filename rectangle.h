#pragma once
class rectangle
{
	float x1, y1, x2, y2;
public:
	rectangle(float x1,float y1,float x2,float y2);
	float* getCoords() const;
	~rectangle(void);
};

