#include "LightingScene.h"
#include "CGFaxis.h"
#include "CGFapplication.h"
#include "perspective.h"
#include "orthogonal.h"
#include <math.h>

float pi = acos(-1.0);
float deg2rad=pi/180.0;
/*
float ambA[3] = {0.2, 0.2, 0.2};
float difA[3] = {0.0, 0.0, 0.0};
float specA[3] = {0.0, 0.0, 0.0};
float shininessA = 1000.0f;

*/
float ambientNull[4]={0,0,0,1};


unsigned int lightArray[8] = {GL_LIGHT0,GL_LIGHT1,GL_LIGHT2,GL_LIGHT3,GL_LIGHT4,GL_LIGHT5,GL_LIGHT6,GL_LIGHT7};

void LightingScene::init() 
{
	Appearence * t = NULL;
	createDisplayLists(pgraph.getRootNode(),t);

	glClearColor(pgraph.getBackground()[0], pgraph.getBackground()[1], pgraph.getBackground()[2], pgraph.getBackground()[3]);

	cams = pgraph.getCameras();
	it = cams.begin();
	for(int i = 0; it != cams.end(); i++,it++) 
	{
		if((*it)->getID() == pgraph.getRootCamera())
		{
			activCam = i;
			break;
		}
	}

	glEnable(GL_NORMALIZE);

	if(pgraph.getCulFace() == "none")
		glCullFace(GL_NONE);
	else if(pgraph.getCulFace() == "back")
		glCullFace(GL_BACK);
	else  if(pgraph.getCulFace() == "front")
		glCullFace(GL_FRONT);
	else  if(pgraph.getCulFace() == "both")
		glCullFace(GL_FRONT_AND_BACK);

	if(pgraph.getCulOrder() == "ccw")
		glFrontFace(GL_CCW);
	else if(pgraph.getCulOrder() == "cw")
		glFrontFace(GL_CW);


	if(pgraph.getLightEnable())
		glEnable(GL_LIGHTING);
	// Sets up some lighting parameters
	// Computes lighting only using the front face normals and materials

	if(pgraph.getDoubleSided())
	{
		glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);  
	}
	else
	{
		glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE); 
	}

	if(pgraph.getLocalLight())
		glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
	else
	{
		glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_FALSE);
	}

	// Define ambient light (do not confuse with ambient component of individual lights)


	float backAmbientLight[4] = {0,0,0,0};
	for(int i = 0; i < 4;i++)
		backAmbientLight[i] = pgraph.getAmbient()[i];

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, backAmbientLight);  

	// Declares and enables two lights, with null ambient component

	if(pgraph.getShading() == "gouraud")
		glShadeModel(GL_SMOOTH);
	else if(pgraph.getShading() == "flat")
		glShadeModel(GL_FLAT);

	if(pgraph.getDrawingMode() == "fill")
		wire = 0;
	else if(pgraph.getDrawingMode() == "line")
		wire = 1;
	else if(pgraph.getDrawingMode() == "point")
		wire = 2;

	vector<myLight> mL = pgraph.getLights();
	int i = 0;
	for(vector<myLight>::iterator mIt = mL.begin(); mIt != mL.end();mIt++,i++)
	{

		float pos[4] = {mIt->getPos()[0],mIt->getPos()[1],mIt->getPos()[2],1.0};
		float ambient[4] = {mIt->getAmbient()[0],mIt->getAmbient()[1],mIt->getAmbient()[2],mIt->getAmbient()[3]};
		float diffuse[4] =  {mIt->getDiffuse()[0],mIt->getDiffuse()[1],mIt->getDiffuse()[2],mIt->getDiffuse()[3]};
		float specular[4] =  {mIt->getSpecular()[0],mIt->getSpecular()[1],mIt->getSpecular()[2],mIt->getSpecular()[3]};
		CGFlight* newLight;

		if( mIt->getType() == "spot")
		{

			float angle = mIt->getAngle(), exp = mIt->getExponent();
			float target[3]={mIt->getTarget()[0] - pos[0],mIt->getTarget()[1]- pos[1],mIt->getTarget()[2]- pos[2]};
			float unit = sqrt(target[0] * target[0] + target[1] * target[1] + target[2] * target[2]);
			for (int i = 0; i < 3; i++) 
				target[i] = target[i] / unit;
			glLightf(lightArray[i],GL_SPOT_EXPONENT,exp);
			glLightf(lightArray[i],GL_SPOT_CUTOFF,angle);
			glLightfv(lightArray[i],GL_SPOT_DIRECTION,target);	
			newLight =new CGFlight(lightArray[i],pos,target);
		}
		else
			newLight =new CGFlight(lightArray[i],pos);
		newLight->setAmbient(ambient);
		newLight->setDiffuse(diffuse);
		newLight->setSpecular(specular);

		if(mIt->getEnabled())
			newLight->enable();
		else
			newLight->disable();

		newLight->update();

		lightsVector.push_back(newLight);
	}


	//Declares materials
	/*	
	materialA = new CGFappearance(ambientNull,difA,specA,shininessA);
	/*	materialB = new CGFappearance(ambientNull,difB,specB,shininessB);
	*/

	setUpdatePeriod(1);
}

void LightingScene::display() 
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	switch(wire)
	{
	case 0:	
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case 1:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case 2:		
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		break;
	}


	it = cams.begin() + activCam;
	if(it != cams.end())
	{
		(*it)->applyView();
		(*it)->apply();
	}
	else
	{
		CGFscene::activeCamera->applyView();
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
	//pgraph.getCameras()[activCam]->apply(); // para evitar que o iterador fique a apontar para o vazio


	CGFapplication::activeApp->forceRefresh();

	// ---- BEGIN Background, camera and axis setup

	// Clear image and depth buffer everytime we update the scene


	// Initialize Model-View matrix as identity (no transformation

	// Apply transformations corresponding to the camera position relative to the origin

	vector<myLight> vl = pgraph.getLights();
	vector<myLight>::iterator vlit = vl.begin();

	for(int i =0; vlit != vl.end();vlit++,i++)
	{
		if(vlit->getMarker())
			lightsVector[i]->draw();
		if(vlit->getEnabled())
			glEnable(lightArray[i]);
		else
			glDisable(lightArray[i]);
		lightsVector[i]->update();
	}
	// Draw axis


	axis.draw();

	Appearence * t = NULL;
	drawNode(pgraph.getRootNode(),t);
	// ---- END Background, camera and axis setup

	// ---- BEGIN Primitive drawing section

	/*Flag f = Flag(new Appearence("foguetaoAp",0.8,"metal"));

	f.draw();
	*/

	glutSwapBuffers();
}


void LightingScene::update(unsigned long millis)
{
	pgraph.update(millis);
}

LightingScene::~LightingScene() 
{
}


void LightingScene::setGraph(sceneGraph graph)
{
	pgraph=graph;
}



void LightingScene::drawNode(Node *n,Appearence * t)
{
	if(n->isDisplayList())
		glCallList(n->getDisplayList());
	else
	{
		
		glPushMatrix();
		glMultMatrixf(n->matrix);
		
		for(vector<animation *>::iterator it = n->animations.begin();it != n->animations.end();it++)
		{
			if(!(*it)->isFinished())
			{
				(*it)->transform();
				if(!(*it)->getLoop())
					break;
			}
		}
		if(n->getAppearence())
			t = n->getAppearence();
		if(t)
			t->getAppearance()->apply();

		vector<primitive*> p = n->getPrimitives();

		for(vector<primitive*>::iterator pIt = p.begin(); pIt < p.end();pIt++)
		{
			if(t)
				if(t->getTexture())
					(*pIt)->draw(t->getTexture());					
				else
					(*pIt)->draw();
			else
				(*pIt)->draw();
		}

		vector<Node*> nV = n->getDescendantNode();

		for(vector<Node*>::iterator nIt = nV.begin(); nIt != nV.end();nIt++)
			drawNode(*nIt,t);

		glPopMatrix();
	}

}


void LightingScene::createDisplayLists(Node * node,Appearence *t)
{

	GLuint theList;

	if(node->getAppearence())
		t = node->getAppearence();
	if(t)
		t->getAppearance()->apply();

	
	vector<Node*> nV = node->getDescendantNode();

	for(vector<Node*>::iterator nIt = nV.begin(); nIt != nV.end();nIt++)
			createDisplayLists(*nIt,t);


	if(node->isDisplayList())
	{
		theList = glGenLists(1);
		node->setIsDisplayList(false);
		glNewList(theList,GL_COMPILE);
		drawNode(node,t);
		glEndList();
		node->setIsDisplayList(true);
		node->setDisplayList(theList);
	}

}