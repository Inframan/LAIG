#pragma once
#include "cylinder.h"
#include "CGFappearance.h"

class Peca
{
	int cor;
	int x,y;
	cylinder *innerCylinder, *outerCylinder;
	CGFappearance *corPeca;
	
public:
	Peca(int cor);
	Peca(void);
	void draw();
	~Peca(void);
	void setCoords(int x, int y);
	vector<int> getCoords()const;
	void move(int dx, int dy);
	void exit(int dx,int dy);
	void merge(int coordx,int coordy);	
	void update(long millis);
};

