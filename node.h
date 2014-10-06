#pragma once
#include <string>
#include <vector>
#include "triangle.h"
#include "rectangle.h"
#include "cylinder.h"
#include "torus.h"
#include "sphere.h"

using namespace std;

class node
{
	string id;
	vector<string> descendants;
	vector<vector<int>> matrix;
	vector<triangle> triangles;
	vector<rectangle> rectangles;
	vector<cylinder> cylinders;
	vector<torus> torusses;
	vector<sphere> spheres;
public:
	node(string id);
	void setMatrix(vector<vector<int>> m);
	void addDescendant(string id);
	void addRectangle(float x1,float y1,float x2,float y2);
	void addTriangle(float x1,float y1,float z1,float x2,float y2,float z2,float x3,float y3,float z3);
	void addCylinder(float base,float top,float height,int slices,int stacks);
	void addSphere(float radius, int slices,int stacks);
	void addTorus(float inner, float outer, int slices, int loops);
	~node(void);
};

