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
	~primitive(void);
};

