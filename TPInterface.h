#ifndef TPinterface_H
#define TPinterface_H

#include "CGFinterface.h"
#include "camera.h"
#include "sceneGraph.h"
#include "LightingScene.h"
#include "CGFapplication.h"

class TPinterface: public CGFinterface {
	vector<string> cameras;
	sceneGraph * pgraph;
	void doMove(string move,int previousX, int previousY , int selectedX, int selectedY,int play);
	GLUI_Panel *gameModepanel;
	GLUI_Panel* windpanel;
	GLUI_Panel* lightspanel;
	GLUI_Panel* cammodel;
	GLUI_Panel* modepanel;
	GLUI_Panel* movepanel;
	GLUI_Panel* endGamepanel;
	GLUI_Button* undo;
	GLUI_Button* endTurn;
	GLUI_Button* movebutton;
	GLUI_Button* exitbutton;
	GLUI_Button* mergebutton;
	GLUI_Button* endGame;
	GLUI_Button* gameMovie;
	GLUI_Button* forward;
	GLUI_Button* backwards;

		int movieIndex;
	public:
		TPinterface(sceneGraph *graph);
		void getCameraList();
		virtual void initGUI();
		virtual void processGUI(GLUI_Control *ctrl);
		virtual void processMouse(int button, int state, int x, int y);	
		void performPicking(int x, int y);
		void processHits(GLint hits, GLuint buffer[]);
		void prepareGameMove(int previousX, int previousY, int selectedX, int selectedY);
		void prepareRandomMove();
		void gameOver();
};


#endif