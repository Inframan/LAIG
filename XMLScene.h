#ifndef _XMLSCENE_H_
#define _XMLSCENE_H_


#include "sceneGraph.h"
#include "tinyxml.h"

class XMLScene
{
public:
	XMLScene(char *filename, sceneGraph * graph);
	~XMLScene();

	static TiXmlElement *findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val);
	
protected:

	TiXmlDocument* doc;

	TiXmlElement* globElement; 
	TiXmlElement* matsElement;
	TiXmlElement* textsElement;
	TiXmlElement* leavesElement;
	TiXmlElement* nodesElement;
	TiXmlElement* graphElement;
};

#endif