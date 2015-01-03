#include "Peca.h"


Peca::Peca(void)
{
	aniWork = false;
	prevTime =0;
	speedx = speedy = speedz = 0;
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
	z = 0;
	innerCylinder = new cylinder(0.1,0.1,0.2,10,10);
	outerCylinder = new cylinder(0.3,0.3,0.1,10,10);
}

Peca::Peca(int cor)
{
	speedx = speedy = speedz = 0;
	aniWork = false;
	prevTime = 0;
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
	x = 0; 
	y = 0;
	z = 0;
	innerCylinder = new cylinder(0.1,0.1,0.2,10,10);
	outerCylinder = new cylinder(0.3,0.3,0.1,10,10);
}

Peca::~Peca(void)
{
}

void Peca::draw(){
	corPeca->apply();
	glPushMatrix();
	if(aniWork)
		ani->transform();
	glTranslated(x,z,y);
	glRotated(-90,1,0,0);
	innerCylinder->draw();
	outerCylinder->draw();
	glPopMatrix();
}

void Peca::setMoveAnimation(int x, int y,int z){
	
	ani = new linearAnimation("this ani",0.5);
	ani->addPoint(x,y,z);
	ani->addPoint(0,0,0);
	ani->changeControlPoint();
	ani->calculateTotalDistance();
	aniWork = true;
	
}

void Peca::setExitAnimation(int x, int y, int z){
	ani=new linearAnimation("this ani",1);
	ani->addPoint(x,y,z);
	ani->addPoint(x/1.125,y+0.25,z/1.125);
	ani->addPoint(x/2,y+0.5,z/2);
	ani->addPoint(0,y,0);
	ani->addPoint(0,y/2,0);
	ani->addPoint(0,0,0);
	
	ani->changeControlPoint();
	ani->calculateTotalDistance();
	aniWork = true;
}

void Peca::setMergeAnimation(int x, int y, int z){
	ani=new linearAnimation("this ani",1);
	ani->addPoint(x,y,z);
	ani->addPoint(x/1.125,y+0.25,z/1.125);
	ani->addPoint(x/2,y+0.5,z/2);
	ani->addPoint(x/4,y+0.25,z/4);
	ani->addPoint(0,0,0);
	
	ani->changeControlPoint();
	ani->calculateTotalDistance();
	aniWork = true;
}

void Peca::update(unsigned long millis)
{
	if(aniWork)
	{
		ani->update(millis);
		if(ani->isFinished())
			aniWork = false;
	}
}

