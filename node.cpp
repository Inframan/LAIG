#include "node.h"


Node::Node(string id)
{
	this->id = id;

}

void Node:: setMatrix(vector<vector<int>> m)
{
	matrix = m;
}

void Node::addDescendant(string id)
{
	descendants.push_back(id);
}

void Node::addRectangle(float x1,float y1,float x2,float y2)
{
	rectangle r(x1,y1,x2,y2);
	rectangles.push_back(r);
}

void Node::addTriangle(float x1,float y1,float z1,float x2,float y2,float z2,float x3,float y3,float z3)
{
	triangle t(x1,y1,z1,x2,y2,z2,x3,y3,z3);
	triangles.push_back(t);
}

void Node::addCylinder(float base,float top,float height,int slices,int stacks)
{
	cylinder c(base,top,height,slices,stacks);
	cylinders.push_back(c);
}

void Node::addSphere(float radius, int slices,int stacks)
{
	sphere s(radius,slices,stacks);
	spheres.push_back(s);
}
void Node::addTorus(float inner, float outer, int slices, int loops)
{
	torus t(inner,outer,slices,loops);
	torusses.push_back(t);
}

Node::~Node(void)
{
}
