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

	glClearColor(pgraph.getBackground()[0], pgraph.getBackground()[1], pgraph.getBackground()[2], pgraph.getBackground()[3]);


	map<string,camera *> cams= pgraph.getCameras();
	int i = 0;
	for(map<string,camera *>::iterator it = cams.begin(); it != cams.end(); it++) 
	{
		if(it->first == pgraph.getRootCamera())
			activCam = i;
		i++;
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


	for(unsigned int i = 0; i < pgraph.getLights().size();i++)
	{
		myLight temp = pgraph.getLights()[i];

		float pos[4] = {temp.getPos()[0],temp.getPos()[1],temp.getPos()[2],1.0};
		float ambient[4] = {temp.getAmbient()[0],temp.getAmbient()[i],temp.getAmbient()[2],temp.getAmbient()[3]};
		float diffuse[4] =  {temp.getDiffuse()[0],temp.getDiffuse()[i],temp.getDiffuse()[2],temp.getDiffuse()[3]};
		float specular[4] =  {temp.getSpecular()[0],temp.getSpecular()[i],temp.getSpecular()[2],temp.getSpecular()[3]};
		CGFlight* newLight;

		if( temp.getType() == "spot")
		{

			float angle = temp.getAngle(), exp = temp.getExponent();
			float target[3]={temp.getTarget()[0] - pos[0],temp.getTarget()[1]- pos[1],temp.getTarget()[2]- pos[2]};
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
	/*	materialB = new CGFappearance(ambientNull,difB,specB,shininessB);
	*/
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


	map<string,camera *> cams = pgraph.getCameras();
	map<string,camera *>::iterator it = cams.begin();
	for(int i = 0; i <activCam;i++)
		it++;
	if(it != cams.end())
		it->second->apply();
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


	for(unsigned int i = 0; i < pgraph.getLights().size();i++)
	{
		if(pgraph.getLights()[i].getMarker())
			lightsVector[i]->draw();
		if(pgraph.getLights()[i].getEnabled())
			glEnable(lightArray[i]);
		else
			glDisable(lightArray[i]);
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
	if(n->getAppearenceRef() != "inherit"){
		if( n->getAppearence()->getTextureref()!= "" && n->getAppearenceRef() != "inherit")
		{
			n->getAppearence()->getAppearance()->setTexture( n->getAppearence()->getTexture()->getFile().c_str());
			n->getAppearence()->getAppearance()->apply();
		}
		else
			n->getAppearence()->getAppearance()->apply();
	}


	for(unsigned int i = 0; i < n->getRectangle().size();i++)
	{
		if(n->getAppearenceRef() != "inherit")
		{
			if(n->getAppearence()->getTextureref() != "" )
				drawRectangle(n->getRectangle()[i].getCoords(),n->getAppearence()->getTexture());
			else
				drawRectangle(n->getRectangle()[i].getCoords());
		}
		else
			drawRectangle(n->getRectangle()[i].getCoords());
	}

	for(unsigned int i = 0; i < n->getTriangle().size();i++)
	{
		if(n->getAppearenceRef() != "inherit")
		{
			if(n->getAppearence()->getTextureref() != "")
				drawTriangle(n->getTriangle()[i].getCoords(),n->getAppearence()->getTexture());
			else
				drawTriangle(n->getTriangle()[i].getCoords());
		}
		else
			drawTriangle(n->getTriangle()[i].getCoords());

	}


	for(unsigned int i = 0; i < n->getCylinder().size();i++)
	{
		drawCylinder(n->getCylinder()[i].getCoords(),n->getCylinder()[i].getStacks(),n->getCylinder()[i].getSlices());
	}

	for(unsigned int i = 0; i < n->getSphere().size();i++)
	{

		drawSphere( n->getSphere()[i].getRadius(),n->getSphere()[i].getStacks(),n->getSphere()[i].getSlices());
	}

	for(unsigned int i = 0; i < n->getTorus().size();i++)
	{
		n->getTorus()[i].draw();
	}


	for(unsigned int i = 0; i < n->getDescendants().size();i++)
		drawNode(n->getDescendantNode()[i]);

	glPopMatrix();


}

void LightingScene::drawSphere(float radius,int stacks,int slices)
{
	GLUquadric * quad;

	quad = gluNewQuadric();
	gluQuadricTexture(quad,GL_TRUE);
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

	gluQuadricTexture(quad,GL_TRUE);
	gluQuadricTexture(disk1,GL_TRUE);
	gluQuadricTexture(disk2,GL_TRUE);

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

void LightingScene::drawRectangle(vector<float> coords,Texture* t)
{
	float width = t->getTexLengthS(), height = t->getTexLengthT(), lengthT = coords[2]-coords[0],heightT = coords[3]-coords[1];
	float tX,tY;

	tX = lengthT/width;
	tY = heightT/height;


	glBegin(GL_QUADS);
	glNormal3f(0,0,1);
	glTexCoord2f(0,0); 
	glVertex2f(coords[0],coords[1]);
	
	glTexCoord2f(0,tY);
	glVertex2f(coords[2],coords[1]);

	glTexCoord2f(tX,tY);
	glVertex2f(coords[2],coords[3]);

	
	glTexCoord2f(tX,0);
	glVertex2f(coords[0],coords[3]);
	glEnd();
}

void LightingScene::drawRectangle(vector<float> coords)
{
	glBegin(GL_QUADS);
	glNormal3f(0,0,1);	
	glTexCoord2f(0,0); 
	glVertex2f(coords[0],coords[1]);
	glTexCoord2f(1,0); 
	glVertex2f(coords[2],coords[1]);
	glTexCoord2f(1,1); 
	glVertex2f(coords[2],coords[3]);
	glTexCoord2f(0,1); 
	glVertex2f(coords[0],coords[3]);
	glEnd();
}



void LightingScene::drawTriangle(vector<float> coords, Texture* t)
{
	float width = t->getTexLengthS(), height = t->getTexLengthT(), lengthT = coords[0]-coords[3],heightT = coords[7]-coords[1];
	float tX,tY;

	tX = lengthT/width;
	tY = heightT/height;

	glBegin(GL_TRIANGLES);

	glNormal3f(coords[0], coords[1],1);
	glTexCoord2f(0,0);
	glVertex3f(coords[0],coords[1],coords[2]);

	glNormal3f(coords[3], coords[4],1);
	glTexCoord2f(tX,0);
	glVertex3f(coords[3],coords[4],coords[5]);

	glNormal3f(coords[6], coords[7],1);
	glTexCoord2f(tX/2,tY);
	glVertex3f(coords[6],coords[7],coords[8]);
	glEnd();
}


void LightingScene::drawTriangle(vector<float> coords)
{
	glBegin(GL_TRIANGLES);
	glVertex3f(coords[0],coords[1],coords[2]);
	glVertex3f(coords[3],coords[4],coords[5]);
	glVertex3f(coords[6],coords[7],coords[8]);
	glEnd();
}

