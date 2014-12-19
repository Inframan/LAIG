#pragma once
#include "primitive.h"
#include "cylinder.h"

class tabuleiro :
	public primitive
{
	void drawCylinders();
public:
	tabuleiro(void);
	void draw();
	void draw(Texture *t);
	~tabuleiro(void);
};

