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
		vector<string> desc = it->second.getDescendants();
		for(vector<string>::iterator it2 = desc.begin(); it2 != desc.end();it2++)
		{
			tmp.push_back(&nodes.find((*it2))->second);
		}
		it->second.setDescendants(tmp);
	}
}


void sceneGraph::update(unsigned long millis)
{
	rootNode->update(millis);
}
void sceneGraph::addLight(myLight light)
{
	lights.push_back(light);
}

vector<float> sceneGraph::getAmbient() const
{
	return lAmbient;
}


void sceneGraph::addAnimation(animation* anime)
{
	animations[anime->getId()] = anime;
}

map<string,animation*> sceneGraph::getAnimations()const
{
	return animations;
}

animation* sceneGraph::getAnimation(string id)
{
	return animations[id];
}

void sceneGraph::addAppearence(Appearence appearence){
	appearences[appearence.getID()] = appearence;	
}
map<string,Appearence> sceneGraph::getAppearence(){
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

void sceneGraph::addCamera(camera* cam)
{
	cameras.push_back(cam);
}
	
vector<camera *> sceneGraph::getCameras() const
{
	return cameras;
}



sceneGraph::~sceneGraph(void)
{
}
