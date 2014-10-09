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

void sceneGraph::setBackground(float backg[4])
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

void sceneGraph::setLAmbient(float ambient[4])
{
	lAmbient = ambient;
}



sceneGraph::~sceneGraph(void)
{
}
