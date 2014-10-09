#include "LightingScene.h"
#include "CGFaxis.h"
#include "CGFapplication.h"
#include "myTable.h"
#include "Plane.h"
#include "myCylinder.h"

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

	

	sceneVar=0;
	light0On = 1;
	light1On = 1;
	light2On = 0;
	light3On = 0;
	clockAnimation = true;
	// Enables lighting computations
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	// Sets up some lighting parameters
	// Computes lighting only using the front face normals and materials
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);  

	// Define ambient light (do not confuse with ambient component of individual lights)
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbientLight);  

	// Declares and enables two lights, with null ambient component

	glShadeModel(GL_SMOOTH);


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

	//Declares scene elements
	table = new myTable();
	wall = new Plane();
	clock = new myClock();
	cylinder = new myCylinder(10,10, true);
	cylinder1 = new myCylinder(10,10,false);
	robot = new myRobot(10);

	boardA = new Plane(BOARD_A_DIVISIONS);
	boardB = new Plane(BOARD_B_DIVISIONS);

	//Declares materials
	materialA = new CGFappearance(ambientNull,difA,specA,shininessA);
	materialB = new CGFappearance(ambientNull,difB,specB,shininessB);

	//Declares Textures
	tableAppearence = new CGFappearance(ambientNull,difA,specA,shininessA);
	tableAppearence->setTexture("table.png");
	tableAppearence->setTextureWrap(GL_REPEAT,GL_REPEAT);

	slidesAppearence = new CGFappearance(ambientNull,difSlides,specSlides,shininessSlides);
	slidesAppearence->setTexture("slides.png");
	slidesAppearence->setTextureWrap(GL_CLAMP,GL_CLAMP);

	boardAppearence = new CGFappearance(ambientNull,difBoard,specBoard,shininessBoard);
	boardAppearence->setTexture("board.png");
	boardAppearence->setTextureWrap(GL_CLAMP,GL_CLAMP);

	robotAppearence = new CGFappearance (ambientNull, difA , specA, shininessA);
	robotAppearence->setTexture("robot1.jpg");
	robotAppearence->setTextureWrap(GL_CLAMP,GL_CLAMP);
	setUpdatePeriod(100);
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


	glBegin(GL_QUADS);
	glVertex2f(pgraph.getNode()[2].getRectangle()[0].getCoords()[0] , pgraph.getNode()[2].getRectangle()[0].getCoords()[1]);
	glVertex2f(pgraph.getNode()[2].getRectangle()[0].getCoords()[2] , pgraph.getNode()[2].getRectangle()[0].getCoords()[1]);
	glVertex2f(pgraph.getNode()[2].getRectangle()[0].getCoords()[2] , pgraph.getNode()[2].getRectangle()[0].getCoords()[3]);
	glVertex2f(pgraph.getNode()[2].getRectangle()[0].getCoords()[0] , pgraph.getNode()[2].getRectangle()[0].getCoords()[3]);
	glEnd();
	
	
	// ---- END Background, camera and axis setup

	// ---- BEGIN Primitive drawing section


	

	/*

	//First Table
	glPushMatrix();
	glTranslated(5,0,8);
	table->draw(materialA, tableAppearence);
	glPopMatrix();
	/*
	//Second Table
	glPushMatrix();
	glTranslated(12,0,8);
	table->draw(materialA, tableAppearence);
	glPopMatrix();
	*/
	/*materialA->apply();
	//Floor
	glPushMatrix();
	glTranslated(7.5,0,7.5);
	glScaled(15,0.2,15);
	wall->draw();
	glPopMatrix();

	//LeftWall
	glPushMatrix();
	glTranslated(0,4,7.5);
	glRotated(-90.0,0,0,1);

	glScaled(8,0.2,15);
	wall->draw();
	glPopMatrix();

	//PlaneWall
	glPushMatrix();
	glTranslated(7.5,4,0);
	glRotated(90.0,1,0,0);
	glScaled(15,0.2,8);
	wall->draw();
	glPopMatrix();


	// Board A
	glPushMatrix();
	glTranslated(4,4,0.2);
	glScaled(BOARD_WIDTH,BOARD_HEIGHT,1);
	glRotated(90.0,1,0,0);
	slidesAppearence->apply();
	boardA->draw();
	glPopMatrix();

	//PlaneB
	glPushMatrix();
	glTranslated(10.5,4,0.2);
	glScaled(BOARD_WIDTH,BOARD_HEIGHT,1);
	glRotated(90.0,1,0,0);
	boardAppearence->apply();
	boardB->draw();
	glPopMatrix();

	//cylinder
	materialA->apply();
	glPushMatrix();
	glScaled(1,8,1);
	glTranslated(1,0,2);
	glRotated(-90, 1,0,0);
	cylinder->draw();
	glPopMatrix();


	glPushMatrix();
	glScaled(1,8,1);
	glTranslated(14,0,2);
	glRotated(-90, 1,0,0);
	cylinder1->draw();
	glPopMatrix();


	//clock
	glPushMatrix();
	glTranslated(7,8,0);
	clock->draw();
	glPopMatrix();

	//robot

	glPushMatrix();
	robotAppearence->apply();
	glTranslated(4,0,4);
	robot->draw();
	glPopMatrix();
	*/
	// ---- END Primitive drawing section


	// We have been drawing in a memory area that is not visible - the back buffer, 
	// while the graphics card is showing the contents of another buffer - the front buffer
	// glutSwapBuffers() will swap pointers so that the back buffer becomes the front buffer and vice-versa
	glutSwapBuffers();
}


void LightingScene::update(unsigned long millis)
{
	if(clockAnimation)
		clock->update(millis);

}

LightingScene::~LightingScene() 
{
	delete(light0);
	delete(light1);

	delete(table);
	delete(wall);
	delete(boardA);
	delete(boardB);
	delete(materialA);
	delete(materialB);
}

void LightingScene::toggleSomething(unsigned char key)
{

	robot->processKeyboard(key);
}

int LightingScene:: pauseClock(int call)
{
	clockAnimation = !clockAnimation;
	return clockAnimation;
}

int LightingScene:: resetClock(int call)
{
	clock = new myClock();
	return 1;
}


int LightingScene:: pauseResetClock(int call)
{
	if(call = 0)
	{
		clockAnimation = !clockAnimation;
		return 0;
	}
	else
	{
		clock = new myClock();
		clockAnimation = !clockAnimation;
		return 1;
	}
}


void LightingScene::setGraph(sceneGraph graph)
{
	pgraph=graph;
}