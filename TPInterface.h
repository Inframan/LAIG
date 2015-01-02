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
	public:
		TPinterface(sceneGraph *graph);
		void getCameraList();
		virtual void initGUI();
		virtual void processGUI(GLUI_Control *ctrl);
		virtual void processMouse(int button, int state, int x, int y);	
		void performPicking(int x, int y);
		void processHits(GLint hits, GLuint buffer[]);
		void prepareGameMove(int previousX, int previousY, int selectedX, int selectedY);

};


#endif