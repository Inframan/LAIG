#pragma once
#include <string>
#include "node.h"
#include <vector>
#include <map>


using namespace std;

class sceneGraph
{
	string rootId;
	Node * rootNode;
	string drawingMode;
	string shading;
	vector<float> background;//array
	string cullingFace;
	string cullingOrder;
	bool lDoubleSided;
	bool lLocal;
	bool lEnabled;
	vector<float> lAmbient;//array
	map<string,Node> nodes;
	string rootCamera;
	map<string,camera *> cameras;
	

public:
	
	sceneGraph(void);
	void setRootID(string id){rootId = id;}
	void setDrawingMode(string mode);
	void setShading(string mode);
	void setBackground(vector<float> background);
	void setCullingFace(string face);
	void setCullOrder(string order);
	void setDSided(bool doublesided);
	void setlLocal(bool local);
	void setlEnabled(bool enable);
	void setLAmbient(vector<float> ambient);
	void addNode(Node n);
	string getRootID() const;
	Node * getRootNode() const;
	void setRootNode();
	map<string,Node> getNodes() const;
	void addCamera(camera * cam);
	map<string,camera *> getCameras() const;
	void setCameraID(string id);

	string getRootCamera()const;
	bool getDoubleSided()const;
	bool getLocalLight()const;
	bool getLightEnable()const;
	string getCulFace()const;
	string getCulOrder()const;
	string getDrawingMode()const;
	string getShading();
	vector<float> getBackground()const;
	void setDescendantNode();
	~sceneGraph(void);
};

