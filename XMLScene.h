#ifndef _XMLSCENE_H_
#define _XMLSCENE_H_


#include "sceneGraph.h"
#include "tinyxml.h"
#include "orthogonal.h"
#include "perspective.h"
#include "linearAnimation.h"
#include "circularAnimation.h"

class XMLScene
{
public:
	XMLScene(char *filename, sceneGraph * graph);
	~XMLScene();

	static TiXmlElement *findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val);
	
protected:

	TiXmlDocument* doc;
	
	TiXmlElement* animeElement;
	TiXmlElement* globElement; 
	TiXmlElement* lightsElement;
	TiXmlElement* textsElement;
	TiXmlElement* appearancesElement;
	TiXmlElement* camerasElement;
	TiXmlElement* graphElement;
};

#endif