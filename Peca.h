#pragma once
#include "cylinder.h"

class Peca
{
	int cor;
	int x,y;
	cylinder *innerCylinder, *outerCylinder;
public:
	Peca(int cor);
	Peca(void);
	void draw();
	~Peca(void);
	void setCoords(int x, int y);
	int* getCoords();
};

