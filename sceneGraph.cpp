#include "sceneGraph.h"


sceneGraph::sceneGraph(void)
{
}


void sceneGraph::setDrawingMode(string mode)
{
	drawingMode = mode;
}

void sceneGraph::setShading(string mode)
{
	shading = mode;
}

void sceneGraph::setBackground(vector<float> backg)
{
	background = backg;
}

void sceneGraph::setCullingFace(string face)
{
	cullingFace = face;
}

void sceneGraph::setCullOrder(string order)
{
	cullingOrder = order;
}

void sceneGraph::setDSided(bool doublesided)
{
	lDoubleSided = doublesided;
}
void sceneGraph::setlLocal(bool local)
{
	lLocal = local;
}
void sceneGraph::setlEnabled(bool enable)
{
	lEnabled = enable;
}

void sceneGraph::setLAmbient(vector<float> ambient)
{
	lAmbient = ambient;
}


void sceneGraph:: addNode(Node n)
{
	nodes[n.getID()] = n;
}

string sceneGraph:: getRootID() const 
{
	return rootId;
}

map<string,Node> sceneGraph:: getNodes() const
{
	return nodes;
}

bool sceneGraph:: getDoubleSided()const
{
	return lDoubleSided;
}

bool sceneGraph:: getLocalLight()const
{
	return lLocal;
}

bool sceneGraph::getLightEnable()const
{
	return lEnabled;
}

string sceneGraph::getCulFace()const
{
	return cullingFace;
}
	
string sceneGraph::getCulOrder()const
{
	return cullingOrder;
}
	
string sceneGraph::getDrawingMode()const
{
	return drawingMode;
}
	
string sceneGraph::getShading()
{
	return shading;
}


vector<float> sceneGraph::getBackground()const
{
	return background;
}




sceneGraph::~sceneGraph(void)
{
}
