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

Node * sceneGraph::getRootNode() const{
	return rootNode;
}
void sceneGraph::setRootNode(){
	rootNode = &nodes.find(rootId)->second;
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

void sceneGraph::setCameraID(string id)
{
	rootCamera = id;
}

string sceneGraph::getRootCamera()const
{
	return rootCamera;
}

void sceneGraph::setDescendantNode(){

	

	map<string,Node>::iterator it;

	for(it = nodes.begin(); it != nodes.end(); it++) {
		vector<Node*>tmp;
		
		for (int i = 0 ; i<it->second.getDescendants().size();i++)
		{
			tmp.push_back(&nodes.find(it->second.getDescendants()[i])->second);
		}
		it->second.setDescendants(tmp);
	}
}

void sceneGraph::addLight(myLight light)
{
	lights.push_back(light);
}

vector<float> sceneGraph::getAmbient() const
{
	return lAmbient;
}

void sceneGraph::addAppearence(Appearence appearence){
	appearences.push_back(appearence);	
}
vector <Appearence> sceneGraph::getAppearence(){
	return appearences;
}
vector<myLight> sceneGraph::getLights()const
{
	return lights;
}

vector<Texture> sceneGraph::getTextures() const{
return textures;
}
void sceneGraph::setTextures(vector<Texture> textures)
{
	this->textures=textures;
}
void sceneGraph::addTexture(Texture t)
{
	textures.push_back(t);
}
/*
void sceneGraph::addCamera(camera* cam)
{
	cameras[cam->getID()] = cam;
}
	
map<string,camera *> sceneGraph::getCameras() const
{
	return cameras;
}


*/
sceneGraph::~sceneGraph(void)
{
}
