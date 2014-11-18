#include "node.h"


Node::Node()
{
	app = NULL;
	displayList = false;
}

Node::Node(string id)
{
	this->id = id;
	app = NULL;
	displayList = false;
}

Node::Node(string id,bool dL)
{
	this->id = id;
	app = NULL;
	displayList = dL;
}
void Node:: setMatrix(float m[4][4])
{
	for(int i = 0; i < 4;i++)
	{
		for(int j = 0; j <4;j++)
			matrix[i*4+j] = m[i][j];
	}
}


void Node::setAppearenceRef(string appRef)
{
	this->appRef=appRef;

}

void Node::setAppearence(Appearence* app)
{
	this->app=app;
	if(app->getTextureref() != "")
	app->getAppearance()->setTexture(getAppearence()->getTexture()->getFile().c_str());
}

Appearence* Node::getAppearence()const{
return app;
}

string Node::getAppearenceRef()const
{
	return appRef;
}

void Node::addDescendant(string id)
{
	descendants.push_back(id);
}

void Node::addRectangle(float x1,float y1,float x2,float y2)
{
	primitives.push_back(new rectangle(x1,y1,x2,y2) );
}

void Node::addTriangle(float x1,float y1,float z1,float x2,float y2,float z2,float x3,float y3,float z3)
{
	primitives.push_back(new triangle(x1,y1,z1,x2,y2,z2,x3,y3,z3));
}

void Node::addCylinder(float base,float top,float height,int slices,int stacks)
{
	primitives.push_back(new cylinder(base,top,height,slices,stacks));
}

void Node::addSphere(float radius, int slices,int stacks)
{
	primitives.push_back(new sphere(radius,slices,stacks));
}
void Node::addTorus(float inner, float outer, int slices, int loops)
{
	primitives.push_back(new torus(inner,outer,slices,loops));
}

void Node::addPlane(int parts)
{
	primitives.push_back(new plane(parts));
}


void Node::addPatch(int order,int partsU,int partsV,string compute,float ** controlPoints)
{
	primitives.push_back(new patch(order,partsU,partsV,compute,controlPoints));
}

float* Node::getMatrix() const
 {
	 return (float*) matrix;
 }

vector<primitive*> Node::getPrimitives()const
{
	return primitives;
}

void Node::setDescendants(vector<Node*> descendantNode){

	this->descendantNode=descendantNode;
}

void Node::addAnimation(animation* anime)
{
	animations.push_back(anime);
}

void Node::update(unsigned long millis)
{
	for(vector<animation *>::iterator it = animations.begin();it != animations.end();it++)
	{
		if(!(*it)->isFinished())
		{
			(*it)->update(millis);
			break;
		}
	}

	for(vector<Node *>::iterator it = descendantNode.begin();it != descendantNode.end();it++)
	{
		(*it)->update(millis);
	}

}

Node::~Node(void)
{
}
