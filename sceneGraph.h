#pragma once
#include <string>
#include "node.h"
#include <vector>

using namespace std;

class sceneGraph
{
	string drawingMode;
	string shading;
	vector<float> background;//array
	string cullingFace;
	string cullingOrder;
	bool lDoubleSided;
	bool lLocal;
	bool lEnabled;
	vector<float> lAmbient;//array
	vector<Node> nodes;

public:
	sceneGraph(void);
	void setDrawingMode(string mode);
	void setShading(string mode);
	void setBackground(vector<float> background);
	void setCullingFace(string face);
	void setCullOrder(string order);
	void setDSided(bool doublesided);
	void setlLocal(bool local);
	void setlEnabled(bool enable);
	void setLAmbient(vector<float> ambient);
	void addNode(Node n){nodes.push_back(n);}
	vector<Node> getNode() const{return nodes;}

	~sceneGraph(void);
};

