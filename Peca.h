#pragma once
#include "cylinder.h"
#include "CGFappearance.h"
#include "linearAnimation.h"
#include "circularAnimation.h"

class Peca
{
	int cor;
	int x,y,z;
	int initx,inity;
	bool aniWork;
	cylinder *innerCylinder, *outerCylinder;
	CGFappearance *corPeca;
	unsigned long prevTime;
	float speedx,speedy,speedz;
	linearAnimation * ani;
public:
	Peca(int cor);
	Peca(void);
	void draw();
	~Peca(void);
	void setMoveAnimation(int x, int y,int z);
	void setExitAnimation(int x, int y,int z);
	void setMergeAnimation(int x, int y,int z);
	void update(unsigned long millis);
};

