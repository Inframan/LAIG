#pragma once
#include <cmath>
#include <string>
#include <vector>
#include "CGFobject.h"
#include "texture.h"

using namespace std;

class primitive
{
public:
	primitive(void);
	virtual void draw() =0;
	virtual void draw(Texture * t){draw();}
	virtual void update (unsigned long millis){}
	virtual void setWind(int wind){}
	~primitive(void);
};

