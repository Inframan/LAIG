#include "LightingScene.h"
#include "CGFaxis.h"
#include "CGFapplication.h"
#include "perspective.h"
#include "orthogonal.h"
#include <math.h>

float pi = acos(-1.0);
float deg2rad=pi/180.0;



unsigned int lightArray[8] = {GL_LIGHT0,GL_LIGHT1,GL_LIGHT2,GL_LIGHT3,GL_LIGHT4,GL_LIGHT5,GL_LIGHT6,GL_LIGHT7};

void LightingScene::init() 
{

	glClearColor(pgraph.getBackground()[0], pgraph.getBackground()[1], pgraph.getBackground()[2], pgraph.getBackground()[3]);


	// Enables lighting computations
	/*	map<string,camera *> copyCam;
	map<string,camera *>::iterator it;

	copyCam = pgraph.getCameras(); // para evitar que o iterador fique a apontar para o vazio
	it =  pgraph.getCameras().find(pgraph.getRootCamera());
	*/
	/*CGFcamera * firstCamera = new CGFcamera();

	if(it->second->getType() == "perspective")
	{
	//gluPerspective(
	firstCamera->setX(((perspective *) it->second)->getPos()[0]);
	firstCamera->setY(((perspective *) it->second)->getPos()[1]);
	firstCamera->setZ(((perspective *) it->second)->getPos()[2]);
	//firstCamera->
	}

	*/
	//CGFscene::activeCamera->applyView();

	//CGFcamera * cam = new CGFcamera(

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
	glEnable(GL_NORMALIZE);
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
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	else if(pgraph.getDrawingMode() == "line")
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else if(pgraph.getDrawingMode() == "point")
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);


	for(int i = 0; i < pgraph.getLights().size();i++)
	{
		myLight temp = pgraph.getLights()[i];

		float pos[4] = {temp.getPos()[0],temp.getPos()[1],temp.getPos()[2],1.0};
		float ambient[4] = {temp.getAmbient()[0],temp.getAmbient()[i],temp.getAmbient()[2],temp.getAmbient()[3]};
		float diffuse[4] =  {temp.getDiffuse()[0],temp.getDiffuse()[i],temp.getDiffuse()[2],temp.getDiffuse()[3]};
		float specular[4] =  {temp.getSpecular()[0],temp.getSpecular()[i],temp.getSpecular()[2],temp.getSpecular()[3]};


		if( temp.getType() == "spot")
		{
			float angle = temp.getAngle(), exp = temp.getExponent();
			float target[3]={temp.getTarget()[0],temp.getTarget()[1],temp.getTarget()[2]};
			glLightf(lightArray[i],GL_SPOT_EXPONENT,exp);
			glLightf(lightArray[i],GL_SPOT_CUTOFF ,angle);
			glLightfv(lightArray[i],GL_SPOT_DIRECTION,target);
			pos[3] = 0.0;
		}


		CGFlight* newLight = new CGFlight(lightArray[i],pos);
		newLight->setAmbient(ambient);
		newLight->setDiffuse(diffuse);
		newLight->setSpecular(specular);


		if(temp.getEnabled())
			newLight->enable();
		else
			newLight->disable();

		newLight->update();

		lightsVector.push_back(newLight);
	}

	//Declares materials
	/*
	materialA = new CGFappearance(ambientNull,difA,specA,shininessA);
	materialB = new CGFappearance(ambientNull,difB,specB,shininessB);
	*/
}

void LightingScene::display() 
{


	/*
	map<string,camera *> copyCam;
	map<string,camera *>::iterator it;
	CGFcamera * firstCamera = new CGFcamera();

	copyCam = pgraph.getCameras(); // para evitar que o iterador fique a apontar para o vazio
	it =  copyCam.find(pgraph.getRootCamera());

	/* if(it->second->getType() == "perspective")
	{
	gluPerspective(
	firstCamera->setX(((perspective *) it->second)->getPos()[0]);
	firstCamera->setY(((perspective *) it->second)->getPos()[1]);
	firstCamera->setZ(((perspective *) it->second)->getPos()[2]);
	//firstCamera->
	}
	else*//* if(it->second->getType() == "ortho")
	{
	char dir = ( (orthogonal *) it->second)->getDirection();
	switch( dir)
	{
	case 'z':
	glOrtho( ((orthogonal *) it->second)->getLeft(),((orthogonal *) it->second)->getRight(),((orthogonal *) it->second)->gotBot(),
	((orthogonal *) it->second)->getTop(),((orthogonal *) it->second)->getNear(),((orthogonal *) it->second)->getFar());
	break;
	case 'y':
	glRotated(90,1,0,0);
	glOrtho( ((orthogonal *) it->second)->getLeft(),((orthogonal *) it->second)->getRight(),((orthogonal *) it->second)->gotBot(),
	((orthogonal *) it->second)->getTop(),((orthogonal *) it->second)->getNear(),((orthogonal *) it->second)->getFar());
	break;
	case 'x':
	//glRotated(90,0,1,0);
	glOrtho( ((orthogonal *) it->second)->getLeft(),((orthogonal *) it->second)->getRight(),((orthogonal *) it->second)->gotBot(),
	((orthogonal *) it->second)->getTop(),((orthogonal *) it->second)->getNear(),((orthogonal *) it->second)->getFar());  

	break;
	}


	firstCamera->applyView();
	}
	*/

	// ---- BEGIN Background, camera and axis setup

	// Clear image and depth buffer everytime we update the scene
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	// Initialize Model-View matrix as identity (no transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Apply transformations corresponding to the camera position relative to the origin
	CGFscene::activeCamera->applyView();

	for(int i = 0; i < pgraph.getLights().size();i++)
	{
		if(pgraph.getLights()[i].getMarker())
			lightsVector[i]->draw();
		lightsVector[i]->update();
	}
	// Draw axis
	axis.draw();


	drawNode(pgraph.getRootNode());



	// ---- END Background, camera and axis setup

	// ---- BEGIN Primitive drawing section


	glutSwapBuffers();
}


void LightingScene::update(unsigned long millis)
{

}

LightingScene::~LightingScene() 
{
}


void LightingScene::setGraph(sceneGraph graph)
{
	pgraph=graph;
}



void LightingScene::drawNode(Node *n)
{


	float m[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


	for(int i = 0; i < 4;i++)
	{
		for(int j = 0; j<4;j++)
		{
			m[i*4+j] = n->getMatrix()[i][j];
		}
	}

	glPushMatrix();
	glMultMatrixf(m);
	if(n->getAppearence() != NULL){
	
		n->getAppearence()->getAppearance()->setTexture(n->getAppearence()->getTexture()->getFile());
		n->getAppearence()->getAppearance()->apply();
	}
	for(int i = 0; i < n->getRectangle().size();i++)
	{

		drawRectangle(n->getRectangle()[i].getCoords());
	}

	for(int i = 0; i < n->getTriangle().size();i++)
	{
		drawTriangle(n->getTriangle()[i].getCoords());
	}


	for(int i = 0; i < n->getCylinder().size();i++)
	{
		drawCylinder(n->getCylinder()[i].getCoords(),n->getCylinder()[i].getStacks(),n->getCylinder()[i].getSlices());
	}

	for(int i = 0; i < n->getSphere().size();i++)
	{

		drawSphere( n->getSphere()[i].getRadius(),n->getSphere()[i].getStacks(),n->getSphere()[i].getSlices());
	}

	for(int i = 0; i < n->getTorus().size();i++)
	{
		drawTorus(n->getTorus()[i].getInner(),n->getTorus()[i].getOuter(),n->getTorus()[i].getLoops(),n->getTorus()[i].getSlices());
	}


	for(int i = 0; i < n->getDescendants().size();i++)
		drawNode(n->getDescendantNode()[i]);

	glPopMatrix();


}

void LightingScene:: drawTorus(float inner,float outer,int loops,int slices)
{
	myTorus * torus = new myTorus(inner,outer,slices,loops);

	torus->draw();

}


void LightingScene::drawSphere(float radius,int stacks,int slices)
{
	GLUquadric * quad;

	quad = gluNewQuadric();

	gluQuadricDrawStyle(quad,GLU_FILL);
	gluQuadricNormals(quad,GLU_SMOOTH);
	gluQuadricOrientation(quad,GLU_OUTSIDE);

	gluSphere(quad,radius,slices,stacks);


	gluDeleteQuadric(quad);
}

void LightingScene::drawCylinder(vector<float> coords,int stacks,int slices)
{
	GLUquadric * quad,*disk1,*disk2;

	quad = gluNewQuadric();
	disk1 = gluNewQuadric();
	disk2 = gluNewQuadric();

	gluQuadricDrawStyle(quad,GLU_FILL);
	gluQuadricNormals(quad,GLU_SMOOTH);
	gluQuadricOrientation(quad,GLU_OUTSIDE);

	gluCylinder(quad,coords[0],coords[1],coords[2],slices,stacks);

	glPushMatrix();
	glTranslated(0,0,coords[2]);
	gluDisk(disk1,0,coords[1],slices,stacks);
	glPopMatrix();

	glPushMatrix();
	glRotated(180,0,1,0);
	gluDisk(disk2,0,coords[0],slices,stacks);
	glPopMatrix();

	gluDeleteQuadric(quad);
	gluDeleteQuadric(disk1);
}

void LightingScene::drawRectangle(vector<float> coords)
{

	glRectd(coords[0] ,coords[1],coords[2],coords[3]);
}


void LightingScene::drawTriangle(vector<float> coords)
{
	glBegin(GL_TRIANGLES);
	glVertex3f(coords[0],coords[1],coords[2]);
	glVertex3f(coords[3],coords[4],coords[5]);
	glVertex3f(coords[6],coords[7],coords[8]);
	glEnd();
}

