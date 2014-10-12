#include "LightingScene.h"
#include "CGFaxis.h"
#include "CGFapplication.h"
#include "perspective.h"
#include "orthogonal.h"
#include <math.h>

float pi = acos(-1.0);
float deg2rad=pi/180.0;

#define BOARD_HEIGHT 6.0
#define BOARD_WIDTH 6.4

// Positions for two lights
float light0_pos[4] = {4, 6.0, 1.0, 1.0};
float light1_pos[4] = {10.5, 6.0, 1.0, 1.0};

float light2_pos[4] = {10.5, 6.0, 5.0, 1.0};
float light3_pos[4] = {4, 6.0, 5.0, 1.0};

// Global ambient light (do not confuse with ambient component of individual lights)
float globalAmbientLight[4]= {0.2,0.2,0.2,1.0};
// number of divisions
#define BOARD_A_DIVISIONS 30
#define BOARD_B_DIVISIONS 100

// Coefficients for material A
float ambA[3] = {0.2, 0.2, 0.2};
float difA[3] = {0.6, 0.6, 0.6};
float specA[3] = {0.0, 0.8, 0.8};
float shininessA = 120.f;

// Coefficients for material B
float ambB[3] = {0.2, 0.2, 0.2};
float difB[3] = {0.6, 0.6, 0.6};
float specB[3] = {0.8, 0.8, 0.8};
float shininessB = 120.f;

// Coefficients for slide texture
float ambSlides[3] = {0.2, 0.2, 0.2};
float difSlides[3] = {0.8, 0.8, 0.8};
float specSlides[3] = {0.1, 0.1, 0.1};
float shininessSlides = 10.f;

// Coefficients for board texture
float ambBoard[3] = {0.2, 0.2, 0.2};
float difBoard[3] = {0.3, 0.3, 0.3};
float specBoard[3] = {0.6, 0.6, 0.6};
float shininessBoard = 200.f;



float ambientNull[4]={0,0,0,1};
float yellow[4]={1,1,0,1};

void LightingScene::init() 
{

	
	light0On = 1;
	light1On = 1;
	light2On = 0;
	light3On = 0;
	// Enables lighting computations
	map<string,camera *> copyCam;
	map<string,camera *>::iterator it;

	copyCam = pgraph.getCameras(); // para evitar que o iterador fique a apontar para o vazio
	it =  pgraph.getCameras().find(pgraph.getRootCamera());

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
		glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);  
	}

	if(pgraph.getLocalLight())
		glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_FALSE);

	// Define ambient light (do not confuse with ambient component of individual lights)
	float backAmbientLight[4] = {0,0,0,0};
	for(int i = 0; i < 4;i++)
		backAmbientLight[i] = pgraph.getBackground()[i];

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

	light0 = new CGFlight(GL_LIGHT0, light0_pos);
	light0->setAmbient(ambientNull);
	light0->setSpecular(yellow);

	if (light0On == 0)
		light0->disable();
	else
		light0->enable();


	light1 = new CGFlight(GL_LIGHT1, light1_pos);
	light1->setAmbient(ambientNull);

	if (light1On == 0)
		light1->disable();
	else
		light1->enable();


	light2 = new CGFlight(GL_LIGHT2, light2_pos);
	light2->setAmbient(ambientNull);

	if (light2On == 0)
		light2->disable();
	else
		light2->enable();



	light3 = new CGFlight(GL_LIGHT3, light3_pos);
	light3->setAmbient(ambientNull);
	light3->setSpecular(yellow);
	light3->setKc(0);
	light3->setKl(0);
	light3->setKq(1);

	if (light3On == 0)
		light3->disable();
	else
		light3->enable();




	// Uncomment below to enable normalization of lighting normal vectors
	// glEnable (GL_NORMALIZE);


	//Declares materials
	materialA = new CGFappearance(ambientNull,difA,specA,shininessA);
	materialB = new CGFappearance(ambientNull,difB,specB,shininessB);

}

void LightingScene::display() 
{

	// ---- BEGIN Background, camera and axis setup

	// Clear image and depth buffer everytime we update the scene
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	// Initialize Model-View matrix as identity (no transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Apply transformations corresponding to the camera position relative to the origin
	CGFscene::activeCamera->applyView();


	light0->draw();
	light0->disable();
	if (light0On != 0)
		light0->enable();

	light1->draw();
	light1->disable();
	if (light1On != 0)
		light1->enable();

	light2->draw();
	light2->disable();
	if (light2On != 0)
		light2->enable();

	light3->draw();
	light3->disable();
	if (light3On != 0)
		light3->enable();

	// Draw axis
	axis.draw();


	drawNode(pgraph.getRootID());

	
	
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



void LightingScene::drawNode(string id)
{
	map<string,Node> copyMap;
	map<string,Node>::iterator it;

	copyMap = pgraph.getNodes(); // para evitar que o iterador fique a apontar para o vazio
	it =  copyMap.find(id);

	Node n = it->second;

	float m[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


	for(int i = 0; i < 4;i++)
	{
		for(int j = 0; j<4;j++)
		{
			m[i*4+j] = n.getMatrix()[i][j];
		}
	}

	glPushMatrix();
	glMultMatrixf(m);

	for(int i = 0; i < n.getRectangle().size();i++)
	{
		drawRectangle(n.getRectangle()[i].getCoords());
	}

	for(int i = 0; i < n.getTriangle().size();i++)
	{
		drawTriangle(n.getTriangle()[i].getCoords());
	}

	
	for(int i = 0; i < n.getCylinder().size();i++)
	{
		drawCylinder(n.getCylinder()[i].getCoords(),n.getCylinder()[i].getStacks(),n.getCylinder()[i].getSlices());
	}

	for(int i = 0; i < n.getSphere().size();i++)
	{
		drawSphere( n.getSphere()[i].getRadius(),n.getSphere()[i].getStacks(),n.getSphere()[i].getSlices());
	}

	for(int i = 0; i < n.getTorus().size();i++)
	{
		drawTorus(n.getTorus()[i].getInner(),n.getTorus()[i].getOuter(),n.getTorus()[i].getLoops(),n.getTorus()[i].getSlices());
	}


	for(int i = 0; i < n.getDescendants().size();i++)
		drawNode(n.getDescendants()[i]);

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

