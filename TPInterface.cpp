#include "TPinterface.h"
#include "LightingScene.h"

TPinterface::TPinterface(sceneGraph *graph)
{
	pgraph = graph;
	getCameraList();
}

void TPinterface::getCameraList()
{
	map<string,camera *> cams = pgraph->getCameras();
	for(map<string,camera *>::iterator it = cams.begin(); it != cams.end(); it++) 
	{
		cameras.push_back(it->first);
	}

}


void TPinterface::initGUI()
{

	pgraph = &(((LightingScene*) scene)->pgraph);

	int* wire = &(((LightingScene*) scene)->wire);

	int * cam = &(((LightingScene*) scene)->activCam);

	// Check CGFinterface.h and GLUI documentation for the types of controls available
	GLUI_Panel *varPanel= addPanel("Settings:", 1);


	GLUI_Panel *modepanel = addPanelToPanel(varPanel, "Mode", 1);
	GLUI_RadioGroup* wireFrameGroup = addRadioGroupToPanel(modepanel,wire);
	addRadioButtonToGroup(wireFrameGroup, "\tFill");
	addRadioButtonToGroup(wireFrameGroup, "\tWire");
	addRadioButtonToGroup(wireFrameGroup, "\tPoint");
	
	addColumnToPanel(varPanel);
	GLUI_Panel *cammodel = addPanelToPanel(varPanel, "Camera", 1);
	GLUI_RadioGroup* camerasGroup = addRadioGroupToPanel(cammodel,cam);
	for(int i = 0; i < cameras.size();i++)
	{

		addRadioButtonToGroup(camerasGroup, (char *)cameras[i].c_str());
	}
	addRadioButtonToGroup(camerasGroup, "Free Camera");
	

	addColumnToPanel(varPanel);
	GLUI_Panel *lightspanel = addPanelToPanel(varPanel, "Lights", 1);
	for(int i = 0; i < pgraph->getLights().size();i++)
	{
		if (pgraph->getLights()[i].enabled)
			addCheckboxToPanel(lightspanel,
			(char*)pgraph->getLights()[i].id.c_str(), NULL, i)->set_int_val(
			1);
		else
			addCheckboxToPanel(lightspanel,
			(char*)pgraph->getLights()[i].id.c_str(), NULL, i)->set_int_val(
			0);
	}
	


	/*	addColumnToPanel(varPanel);

	GLUI_Listbox* texturesLand = addListboxToPanel(varPanel, "Landscape", landscapeSelect,8);

	texturesLand->add_item(1,"Mountains");
	texturesLand->add_item(2,"City");
	texturesLand->add_item(3,"Riverside");
	texturesLand->add_item(4,"City Night");
	*/

}


void TPinterface::processGUI(GLUI_Control *ctrl)
{

	if (ctrl->user_id >= 0)
		if (ctrl->get_int_val() == 1) {
			pgraph->getLights()[ctrl->user_id].enabled = true;
			((LightingScene *) scene)->lightsVector[ctrl->user_id]->enable();
		} else {
			pgraph->getLights()[ctrl->user_id].enabled = false;
			((LightingScene *) scene)->lightsVector[ctrl->user_id]->disable();

		}
}