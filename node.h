#pragma once
#include <string>
#include <vector>
#include "triangle.h"
#include "rectangle.h"
#include "cylinder.h"
#include "torus.h"
#include "sphere.h"
#include "camera.h"
#include "Appearence.h"
using namespace std;

class Node
{
	string id;
	string appRef;
	vector<string> descendants;
	vector<Node*> descendantNode;
	vector<vector<float>> matrix;
	vector<triangle> triangles;
	vector<rectangle> rectangles;
	vector<cylinder> cylinders;
	vector<torus> torusses;
	vector<sphere> spheres;
	Appearence * app;

public:
	Node();
	Node(string id);
	void setMatrix(float m[4][4]);
	void setAppearenceRef(string appRef);
	void setAppearence(Appearence* app);
	Appearence* getAppearence();
	string getAppearenceRef();
	void addDescendant(string id);
	void addRectangle(float x1,float y1,float x2,float y2);
	void addTriangle(float x1,float y1,float z1,float x2,float y2,float z2,float x3,float y3,float z3);
	void addCylinder(float base,float top,float height,int slices,int stacks);
	void addSphere(float radius, int slices,int stacks);
	void addTorus(float inner, float outer, int slices, int loops);
	vector<rectangle> getRectangle() const{return rectangles;}
	vector<triangle> getTriangle() const{return triangles;}
	vector<cylinder> getCylinder() const{return cylinders;}
	vector<torus> getTorus() const{return torusses;}
	vector<sphere> getSphere() const{return spheres;}
	string getID() const {return id;}
	vector<string> getDescendants()const { return descendants;}
	vector<Node *> getDescendantNode() const { return descendantNode;}
	vector<vector<float>> getMatrix()const;
	void setDescendants(vector<Node *> descendantNode);


	~Node(void);
};

