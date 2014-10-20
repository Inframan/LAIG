#ifndef LightingScene_H
#define LightingScene_H

#include "CGFscene.h"
#include "CGFappearance.h"
#include "sceneGraph.h"


class LightingScene : public CGFscene
{
	
public:
	vector<camera*> cams;
	vector<camera*>::iterator it;
	vector<CGFlight *> lightsVector;
	sceneGraph pgraph;
	int  activCam;
	int wire;
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
	void drawRectangle(vector<float> coords);
	void drawTriangle(vector<float> coords,Texture* t);	
	void drawTriangle(vector<float> coords);
	void drawNode(Node *n);
	void drawCylinder(vector<float> coords,int stacks,int slices);
	void drawSphere(float radius,int stacks,int slices);



	CGFappearance* materialA;
	CGFappearance* materialB;


	~LightingScene();
};

#endif