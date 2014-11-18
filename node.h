#pragma once
#include <string>
#include <vector>
#include "primitive.h"
#include "triangle.h"
#include "rectangle.h"
#include "cylinder.h"
#include "torus.h"
#include "sphere.h"
#include "camera.h"
#include "Appearence.h"
#include "plane.h"
#include "patch.h"
#include "animation.h"
#include "linearAnimation.h"
#include "Flag.h"

using namespace std;

class Node
{
	string id;
	string appRef;
	bool displayList;
	GLuint theList;//the one and only DISPLAYLIST
	vector<string> descendants;
	vector<Node*> descendantNode;
	vector<primitive*> primitives;
	Appearence * app;
public:
	vector<animation *> animations;
	float matrix[16];
	Node();
	Node(string id);
	Node(string id,bool dL);
	void setMatrix(float m[4][4]);
	void setAppearenceRef(string appRef);
	void setAppearence(Appearence* app);
	Appearence* getAppearence()const;
	string getAppearenceRef()const;
	void addDescendant(string id);
	void addRectangle(float x1,float y1,float x2,float y2);
	void addTriangle(float x1,float y1,float z1,float x2,float y2,float z2,float x3,float y3,float z3);
	void addCylinder(float base,float top,float height,int slices,int stacks);
	void addSphere(float radius, int slices,int stacks);
	void addTorus(float inner, float outer, int slices, int loops);
	void addPlane(int parts);
	void addPatch(int order,int partsU,int partsV,string compute,float ** controlPoints);
	vector<primitive*> getPrimitives()const;
	string getID() const {return id;}
	vector<string> getDescendants()const { return descendants;}
	vector<Node *> getDescendantNode() const { return descendantNode;}
	float* getMatrix()const;
	void setDescendants(vector<Node *> descendantNode);
	void setIsDisplayList(bool d){displayList = d;}
	bool isDisplayList()const{return displayList;}
	GLuint getDisplayList()const{return theList;}
	void setDisplayList(GLuint list){theList = list;}
	vector<animation *> getAnimations()const{return animations;}
	void addAnimation(animation* anime);
	void update(unsigned long millis);
	~Node(void);
};

