#ifndef LightingScene_H
#define LightingScene_H

#include "CGFscene.h"
#include "CGFappearance.h"
#include "TPInterface.h"
#include "sceneGraph.h"
#include "GameBoard.h"


class LightingScene : public CGFscene
{
	//friend PickInterface;
	//friend TPinterface;
	///for the selectiong flag
	
public:
	int player1pieces,player2pieces;
	bool playerTurn;
	bool gameOver;
	bool selected;
	int xSelected,ySelected;
	flagSelection *flag;
	vector<camera*> cams;
	vector<camera*>::iterator it;
	vector<CGFlight *> lightsVector;
	sceneGraph pgraph;
	GameBoard* board;
	int  activCam;
	int wire;
	int wind;
	int playmove;
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
	void setPlaymove(int playmove);

	CGFappearance* materialA;
	CGFappearance* materialB;


	~LightingScene();
};

#endif