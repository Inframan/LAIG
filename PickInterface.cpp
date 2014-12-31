#include "PickInterface.h"
#include "LightingScene.h"
#include "CGFapplication.h"

// buffer to be used to store the hits during picking
#define BUFSIZE 256
GLuint selectBuf[BUFSIZE];

void PickInterface::processMouse(int button, int state, int x, int y) 
{
	CGFinterface::processMouse(button,state, x, y);

	// do picking on mouse press (GLUT_DOWN)
	// this could be more elaborate, e.g. only performing picking when there is a click (DOWN followed by UP) on the same place
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		performPicking(x,y);
}

void PickInterface::performPicking(int x, int y) 
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

void PickInterface::processHits (GLint hits, GLuint buffer[]) 
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

			prepareGameMove(((LightingScene *) scene)->xSelected, ((LightingScene *) scene)->ySelected , selected[0] , selected[1]);

			((LightingScene *) scene)->xSelected = selected[0];
			((LightingScene *) scene)->ySelected = selected[1];
				
	}
	else
	{
		((LightingScene *) scene)->selected = false;
	}
	// if there were hits, the one selected is in "selected", and it consist of nselected "names" (integer ID's)
	if (selected!=NULL)
	{
		// this should be replaced by code handling the picked object's ID's (stored in "selected"), 
		// possibly invoking a method on the scene class and passing "selected" and "nselected"
		printf("Picked ID's: ");
		for (int i=0; i<nselected; i++)
			printf("%d ",selected[i]);
		printf("\n");

		


	}
	else
		printf("Nothing selected while picking \n");	
}


void PickInterface::prepareGameMove(int previousX, int previousY , int selectedX, int selectedY){

	int play = ((LightingScene *) scene)->playmove;

	stringstream ss;
	ss << previousX;
	string prevX = ss.str();
	ss.clear();
	ss << previousY;
	string prevY = ss.str();
	ss.clear();
	ss << selectedX;
	string newX = ss.str();
	ss.clear();
	ss<< selectedY;
	string newY=ss.str();
	ss.clear();

	int diffX= selectedX - previousX;
	int diffY= selectedY - previousY;
	int direction= -1;
	string playmove;
	string boardList = ((LightingScene *) scene)->board->transformMatrixToPrologList();

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

	ss<<direction;

	string dir = ss.str();
	string playcomand;
	switch (play)
	{
	case 0: //move
		playcomand ="move(" + boardList + ","+ newY + "," + newX + ","+ dir +",E,1).";
		break;
	case 1://exit
		playcomand ="exit("+ boardList + "," + newY + "," + newX + "," + dir + ",1,21,E,NI).";
		break;
	case 2://merge
		playcomand ="merge("+ boardList + "," + prevY + "," + newY + "," + prevX + "," + newX + ",1,E).";
		break;
	default:
		break;
	}

}