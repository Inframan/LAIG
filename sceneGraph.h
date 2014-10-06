#pragma once
#include <string>

using namespace std;

class sceneGraph
{
	string drawingMode;
	string shading;
	float *background;//array
	string cullingFace;
	string cullingOrder;
	bool lDoubleSided;
	bool lLocal;
	bool lEnabled;
	float *lAmbient;//array

public:
	sceneGraph(void);
	void setDrawingMode(string mode);
	void setShading(string mode);
	void setBackground(float background[4]);
	void setCullingFace(string face);
	void setCullOrder(string order);
	void setDSided(bool doublesided);
	void setlLocal(bool local);
	void setlEnabled(bool enable);
	void setLAmbient(float ambient[4]);

	~sceneGraph(void);
};

