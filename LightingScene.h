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
	void drawNode(Node *n,Appearence * t);
	void createDisplayLists(Node * node,Appearence * t);


	CGFappearance* materialA;
	CGFappearance* materialB;


	~LightingScene();
};

#endif