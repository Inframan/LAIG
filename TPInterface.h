#ifndef TPinterface_H
#define TPinterface_H

#include "CGFinterface.h"
#include "camera.h"
#include "sceneGraph.h"

class TPinterface: public CGFinterface {
	vector<string> cameras;
	sceneGraph * pgraph;
	public:
		TPinterface(sceneGraph *graph);
		void getCameraList();
		virtual void initGUI();
		virtual void processGUI(GLUI_Control *ctrl);

};


#endif