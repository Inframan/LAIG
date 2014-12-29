#include "Peca.h"


Peca::Peca(void)
{
	cor = 0;
	x = 0;
	y = 0;
	innerCylinder = new cylinder(0.1,0.1,0.2,10,10);
	outerCylinder = new cylinder(0.3,0.3,0.1,10,10);
}

Peca::Peca(int cor)
{
	this->cor = cor;
	this->x = x;
	this->y = y;
	innerCylinder = new cylinder(0.1,0.1,0.2,10,10);
	outerCylinder = new cylinder(0.3,0.3,0.1,10,10);
}

Peca::~Peca(void)
{
}

void Peca::draw(){
	glPushMatrix();
	
	glRotated(-90,1,0,0);
	innerCylinder->draw();
	outerCylinder->draw();
	glPopMatrix();
}

void Peca::setCoords(int x, int y){
	this->x = x;
	this->y = y;
}

vector<int> Peca::getCoords() const
{
	vector<int> ret;
	ret.push_back(x);
	ret.push_back(y);	
	return ret;
}