#ifndef LightingScene_H
#define LightingScene_H

#include "CGFscene.h"
#include "CGFappearance.h"
#include "sceneGraph.h"
#include "myTorus.h"


class LightingScene : public CGFscene
{
	sceneGraph pgraph;
	vector<CGFlight *> lightsVector;
public:
	int light0On, light1On, light2On, light3On;
	void init();
	void display();
	void update(unsigned long millis);
	void toggleSomething(unsigned char key);
	int resetClock(int call);
	int pauseClock(int call);
	int pauseResetClock(int call);
	void setAppearences();
	void setGraph(sceneGraph pgraph);
	void drawRectangle(vector<float> coords, Texture* t);
	void drawTriangle(vector<float> coords,Texture* t);
	void drawNode(Node *n);
	void drawCylinder(vector<float> coords,int stacks,int slices);
	void drawSphere(float radius,int stacks,int slices);
	void drawTorus(float inner,float outer,int loops,int slices);



	CGFappearance* materialA;
	CGFappearance* materialB;


	~LightingScene();
};

#endif