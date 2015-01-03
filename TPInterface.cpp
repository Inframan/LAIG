#include "TPinterface.h"

#define BUFSIZE 256
GLuint selectBuf[BUFSIZE];


TPinterface::TPinterface(sceneGraph *graph)
{
	pgraph = graph;
	getCameraList();
}

void TPinterface::getCameraList()
{
	vector<camera *> cams = pgraph->getCameras();
	for(vector<camera *>::iterator it = cams.begin(); it != cams.end(); it++) 
	{
		cameras.push_back((*it)->getID());
	}

}


void TPinterface::initGUI()
{

	socketConnect();
	pgraph = &(((LightingScene*) scene)->pgraph);

	int* wire = &(((LightingScene*) scene)->wire);

	int* wind = &(((LightingScene*) scene)->wind);

	int * cam = &(((LightingScene*) scene)->activCam);

	// Check CGFinterface.h and GLUI documentation for the types of controls available
	GLUI_Panel *varPanel= addPanel("Settings:", 1);


	GLUI_Button* movebutton = addButtonToPanel(varPanel,"Move", 13);
	GLUI_Button* exitbutton = addButtonToPanel(varPanel,"Exit", 14);
	GLUI_Button* mergebutton = addButtonToPanel(varPanel,"Merge", 15);

	addColumnToPanel(varPanel);
	GLUI_Panel *modepanel = addPanelToPanel(varPanel, "Mode", 1);
	GLUI_RadioGroup* wireFrameGroup = addRadioGroupToPanel(modepanel,wire);
	addRadioButtonToGroup(wireFrameGroup, "\tFill");
	addRadioButtonToGroup(wireFrameGroup, "\tWire");
	addRadioButtonToGroup(wireFrameGroup, "\tPoint");

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

	addColumnToPanel(varPanel);
	GLUI_Panel *windpanel = addPanelToPanel(varPanel, "Wind", 1);
	GLUI_Spinner *spin=   addSpinnerToPanel(windpanel,"wind",GLUI_SPINNER_INT,wind,11);
	spin->set_int_limits(0,11,GLUI_LIMIT_WRAP);	


	addColumnToPanel(varPanel);


}


void TPinterface::processGUI(GLUI_Control *ctrl)
{
	printf ("GUI control id: %d\n  ",ctrl->user_id);
	switch (ctrl->user_id)
	{

	case 13:
		((LightingScene *) scene) ->setPlaymove(0);
		break;
	case 14:
		((LightingScene *) scene) ->setPlaymove(1);
		break;
	case 15:
		((LightingScene *) scene) ->setPlaymove(2);
		break;
	}

	if (ctrl->user_id >= 0 && ctrl->user_id <13)
		if (ctrl->get_int_val() == 1) {
			pgraph->getLights()[ctrl->user_id].enabled = true;
			((LightingScene *) scene)->lightsVector[ctrl->user_id]->enable();
		} else {
			pgraph->getLights()[ctrl->user_id].enabled = false;
			((LightingScene *) scene)->lightsVector[ctrl->user_id]->disable();
		}



}


void TPinterface::processMouse(int button, int state, int x, int y) 
{
	CGFinterface::processMouse(button,state, x, y);

	// do picking on mouse press (GLUT_DOWN)
	// this could be more elaborate, e.g. only performing picking when there is a click (DOWN followed by UP) on the same place
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		performPicking(x,y);
}

void TPinterface::performPicking(int x, int y) 
{
	// Sets the buffer to be used for selection and activate selection mode
	glSelectBuffer (BUFSIZE, selectBuf);
	glRenderMode(GL_SELECT);

	// Initialize the picking name stack
	glInitNames();

	// The process of picking manipulates the projection matrix
	// so we will be activating, saving and manipulating it
	glMatrixMode(GL_PROJECTION);

	//store current projmatrix to restore easily in the end with a pop
	glPushMatrix ();

	//get the actual projection matrix values on an array of our own to multiply with pick matrix later
	GLfloat projmat[16];
	glGetFloatv(GL_PROJECTION_MATRIX,projmat);

	// reset projection matrix
	glLoadIdentity();

	// get current viewport and use it as reference for 
	// setting a small picking window of 5x5 pixels around mouse coordinates for picking
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	// this is multiplied in the projection matrix
	gluPickMatrix ((GLdouble) x, (GLdouble) (CGFapplication::height - y), 5.0, 5.0, viewport);

	// multiply the projection matrix stored in our array to ensure same conditions as in normal render
	glMultMatrixf(projmat);

	// force scene drawing under this mode
	// only the names of objects that fall in the 5x5 window will actually be stored in the buffer
	scene->display();

	// restore original projection matrix
	glMatrixMode (GL_PROJECTION);
	glPopMatrix ();

	glFlush();

	// revert to render mode, get the picking results and process them
	GLint hits;
	hits = glRenderMode(GL_RENDER);
	processHits(hits, selectBuf);
}

void TPinterface::processHits (GLint hits, GLuint buffer[]) 
{
	GLuint *ptr = buffer;
	GLuint mindepth = 0xFFFFFFFF;
	GLuint *selected=NULL;
	GLuint nselected;

	// iterate over the list of hits, and choosing the one closer to the viewer (lower depth)
	for (int i=0;i<hits;i++) {
		int num = *ptr; ptr++;
		GLuint z1 = *ptr; ptr++;
		ptr++;
		if (z1 < mindepth && num>0) {
			mindepth = z1;
			selected = ptr;
			nselected=num;
		}
		for (int j=0; j < num; j++) 
			ptr++;
	}
	if(selected != NULL)
	{

		((LightingScene *) scene)->selected = true;
		if (((LightingScene *) scene)->playmove != -1)
			prepareGameMove(((LightingScene *) scene)->xSelected, ((LightingScene *) scene)->ySelected , selected[0] , selected[1]);

		((LightingScene *) scene)->xSelected = selected[0];
		((LightingScene *) scene)->ySelected = selected[1];
		// this should be replaced by code handling the picked object's ID's (stored in "selected"), 
		// possibly invoking a method on the scene class and passing "selected" and "nselected"
		printf("Picked ID's: ");
		for (int i=0; i<nselected; i++)
			printf("%d ",selected[i]);
		printf("\n");

	}
	else
	{
		((LightingScene *) scene)->selected = false;
	}



}


void TPinterface::prepareGameMove(int previousX, int previousY , int selectedX, int selectedY){

	int play = ((LightingScene *) scene)->playmove;

	stringstream ss;
	ss << previousX+1;
	string prevX = ss.str();
	ss.str(std::string());
	ss << previousY+1;
	string prevY = ss.str();
	ss.str(std::string());
	ss << selectedX+1;
	string newX = ss.str();
	ss.str(std::string());
	ss<< selectedY+1;
	string newY=ss.str();
	ss.str(std::string());

	//tabuleiro tem coordenadas X e Y trocadas
	int diffY= -selectedX + previousX;
	int diffX= selectedY - previousY;
	int direction= -1;
	string playmove;
	string boardList = ((LightingScene *) scene)->board->transformMatrixToPrologList();
	
	if(abs(diffX) == abs(diffY) || diffY == 0 || diffX == 0)
	{
		if ( diffX == 0 && diffY > 0)
			direction= 1;
		else if ( diffX == 0 && diffY < 0)
			direction= 2;
		else if ( diffX < 0 && diffY == 0)
			direction= 3;
		else if ( diffX > 0 && diffY == 0)
			direction= 4;
		else if ( diffX < 0 && diffY > 0)
			direction= 5;
		else if ( diffX < 0 && diffY < 0)
			direction= 6;
		else if ( diffX > 0 && diffY > 0)
			direction= 7;
		else if ( diffX > 0 && diffY < 0)
			direction= 8;
	}

	ss<<direction;
	string player;
	if(((LightingScene*) scene)->playerTurn)
		player= "1";
	else
		player ="2";
	
	stringstream p1;
	p1 << ((LightingScene*) scene)->player1pieces;
	stringstream p2;
	p2 << ((LightingScene*) scene)->player2pieces;
	string dir = ss.str();
	string playcomand;
	switch (play)
	{
	case 0: //move
		playcomand ="move(" + boardList + ","+ prevY + "," + prevX + ","+ dir +","+player+").\n";
		break;
	case 1://exit
		playcomand ="exit("+ boardList + "," + prevY + "," + prevX + "," + dir + ","+player+",["+p1.str()+","+p2.str()+"]).\n";
		break;
	case 2://merge
		playcomand ="merge("+ boardList + "," + prevY + "," + newY + "," + prevX + "," + newX + ","+player+").\n";
		break;
	default:
		break;
	}
	if ((play == 0 || play == 2) && abs(diffX) <2 && abs(diffY) < 2)
		doMove(playcomand,previousX,previousY,selectedX,selectedY,play);
	else if (play == 1  && sqrt(diffX*diffX+ diffY*diffY) > sqrt(2))
		doMove(playcomand,previousX,previousY,selectedX,selectedY,play);


	gameOver();

}

void TPinterface::doMove(string move,int previousX, int previousY , int selectedX, int selectedY,int play)
{

	char * send = new char[move.length() + 1];
	strcpy(send, move.c_str());
	envia(send, strlen(send));
	char  ans[255];
	string answer(ans);
	char no[7] = "'NO'.\r";
	recebe(ans);
	((LightingScene*) scene)->playmove=-1;
	((LightingScene*) scene)->selected=false;
	int valid = strcmp(ans,no);
	if(ans[0] != '8')
	{
		((LightingScene*) scene)->playerTurn = !((LightingScene*) scene)->playerTurn;
		switch (play)
		{
		case 0: //move
			((LightingScene*) scene)->board->move(previousX,previousY,selectedX,selectedY);
			break;
		case 1://exit
			if(((LightingScene*) scene)->playerTurn)
				((LightingScene*) scene)->player1pieces--;
			else
				((LightingScene*) scene)->player2pieces--;
			((LightingScene*) scene)->board->exit(previousX,previousY,selectedX,selectedY);
			break;
		case 2://merge
			((LightingScene*) scene)->board->merge(previousX,previousY,selectedX,selectedY);
			break;
		}
	}
}

void TPinterface::gameOver(){

	if (((LightingScene*) scene)->player1pieces == 1){
		printf("Player 1 wins!!!\n");
		((LightingScene*) scene)->gameOver=true;
		quit();
	}
	else if (((LightingScene*) scene)->player2pieces == 1){
		printf("Player 1 wins!!!\n");
		((LightingScene*) scene)->gameOver=true;
		quit();
	}

}