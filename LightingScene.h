#ifndef LightingScene_H
#define LightingScene_H

#include "CGFscene.h"
#include "CGFappearance.h"
#include "myTable.h"
#include "Plane.h"
#include "myClock.h"
#include "myClockHand.h"
#include "myCylinder.h"
#include "MyRobot.h"
#include "TPinterface.h"
#include "sceneGraph.h"

class LightingScene : public CGFscene
{
	 bool clockAnimation;
	 sceneGraph pgraph;
public:
	int sceneVar;
	int light0On, light1On, light2On, light3On;
	void init();
	void display();
	void update(unsigned long millis);
	void toggleSomething(unsigned char key);
	int resetClock(int call);
	int pauseClock(int call);
	int pauseResetClock(int call);
	void setGraph(sceneGraph pgraph);

	CGFlight* light0;
	CGFlight* light1;
	CGFlight* light2;
	CGFlight* light3;


	myTable* table;
	myCylinder* cylinder;
	myCylinder* cylinder1;
	myClock* clock;
	Plane* wall;
	Plane* boardA;
	Plane* boardB;
	myRobot* robot;
	CGFappearance* materialA;
	CGFappearance* materialB;

	CGFappearance* floorAppearence;
	CGFappearance* tableAppearence;
	CGFappearance* slidesAppearence;
	CGFappearance* wallAppearence;
	CGFappearance* boardAppearence;
	CGFappearance* windowAppearence;
	CGFappearance* robotAppearence;
	
	~LightingScene();
};

#endif