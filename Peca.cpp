#include "Peca.h"


Peca::Peca(void)
{
	float amb[3] = {0.2, 0.2, 0.2};
	float difA[3] = {0.0, 0.0, 0.6};
	float specA[3] = {0.0, 0.0, 0.8};
	float shininessA = 120.f;

	float difB[3] = {0.6, 0.0, 0.6};
	float specB[3] = {0.8, 0.0, 0.8};
	float shininessB = 120.f;

	cor = 0;
	if(cor)
		corPeca = new CGFappearance(amb,difA,specA,shininessA);
	else
		corPeca = new CGFappearance(amb,difB,specB,shininessB);

	x = 0;
	y = 0;
	innerCylinder = new cylinder(0.1,0.1,0.2,10,10);
	outerCylinder = new cylinder(0.3,0.3,0.1,10,10);
}

Peca::Peca(int cor)
{

		float amb[3] = {0.2, 0.2, 0.2};
	float difA[3] = {0.0, 0.0, 0.6};
	float specA[3] = {0.0, 0.0, 0.8};
	float shininessA = 120.f;

	float difB[3] = {0.6, 0.0, 0.6};
	float specB[3] = {0.8, 0.0, 0.8};
	float shininessB = 120.f;


	this->cor = cor;
	if(cor)
		corPeca = new CGFappearance(amb,difA,specA,shininessA);
	else
		corPeca = new CGFappearance(amb,difB,specB,shininessB);
	this->x = x;
	this->y = y;
	innerCylinder = new cylinder(0.1,0.1,0.2,10,10);
	outerCylinder = new cylinder(0.3,0.3,0.1,10,10);
}

Peca::~Peca(void)
{
}

void Peca::draw(){
	corPeca->apply();
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