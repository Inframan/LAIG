#ifndef LightingScene_H
#define LightingScene_H

#include "CGFscene.h"
#include "CGFappearance.h"
#include "sceneGraph.h"


class LightingScene : public CGFscene
{
	 sceneGraph pgraph;
public:
	int light0On, light1On, light2On, light3On;
	void init();
	void display();
	void update(unsigned long millis);
	void toggleSomething(unsigned char key);
	int resetClock(int call);
	int pauseClock(int call);
	int pauseResetClock(int call);
	void setGraph(sceneGraph pgraph);
	void drawRectangle(vector<float> coords);
	void drawTriangle(vector<float> coords);
	void drawNode(string id);
	void drawCylinder(vector<float> coords,int stacks,int slices);
	void drawSphere(float radius,int stacks,int slices);

	CGFlight* light0;
	CGFlight* light1;
	CGFlight* light2;
	CGFlight* light3;


	CGFappearance* materialA;
	CGFappearance* materialB;


	~LightingScene();
};

#endif