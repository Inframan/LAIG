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
		float ambient[4] = {mIt->getAmbient()[0],mIt->getAmbient()[i],mIt->getAmbient()[2],mIt->getAmbient()[3]};
		float diffuse[4] =  {mIt->getDiffuse()[0],mIt->getDiffuse()[i],mIt->getDiffuse()[2],mIt->getDiffuse()[3]};
		float specular[4] =  {mIt->getSpecular()[0],mIt->getSpecular()[i],mIt->getSpecular()[2],mIt->getSpecular()[3]};
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
		(*it)->apply();
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
		if( n->getAppearence()->getTextureref()!= "" )
		{
			n->getAppearence()->getAppearance()->setTexture( n->getAppearence()->getTexture()->getFile().c_str());
			n->getAppearence()->getAppearance()->apply();
		}
		else
			n->getAppearence()->getAppearance()->apply();
	}

	vector<rectangle> r = n->getRectangle();
	
	for(vector<rectangle>::iterator rIt = r.begin(); rIt < r.end();rIt++)
	{
		if(n->getAppearenceRef() != "inherit")
		{
			if(n->getAppearence()->getTextureref() != "" )
				drawRectangle(rIt->getCoords(),n->getAppearence()->getTexture());
			else
				drawRectangle(rIt->getCoords());
		}
		else
			drawRectangle(rIt->getCoords());
	}

	vector<triangle> t = n->getTriangle();
	for(vector<triangle>::iterator tIt=t.begin(); tIt < t.end();tIt++)
	{
		if(n->getAppearenceRef() != "inherit")
		{
			if(n->getAppearence()->getTextureref() != "")
				drawTriangle(tIt->getCoords(),n->getAppearence()->getTexture());
			else
				drawTriangle(tIt->getCoords());
		}
		else
			drawTriangle(tIt->getCoords());

	}

	vector<cylinder> c = n->getCylinder();
	for(vector<cylinder>::iterator cIt=c.begin(); cIt!=c.end();cIt++)
	{
		drawCylinder(cIt->getCoords(),cIt->getStacks(),cIt->getSlices());
	}

	vector<sphere> s = n->getSphere();
	for(vector<sphere>::iterator sIt=s.begin(); sIt !=s.end();sIt++)
	{

		drawSphere( sIt->getRadius(),sIt->getStacks(),sIt->getSlices());
	}

	vector<torus> to = n->getTorus();
	for(vector<torus>::iterator tIt = to.begin(); tIt != to.end();tIt++)
	{
		tIt->draw();
	}

	vector<Node*> nV = n->getDescendantNode();
	
	for(vector<Node*>::iterator nIt = nV.begin(); nIt != nV.end();nIt++)
		drawNode(*nIt);

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

