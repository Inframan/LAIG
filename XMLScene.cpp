#include "XMLScene.h"

XMLScene::XMLScene(char *filename)
{

	// Read XML from file

	doc=new TiXmlDocument( filename );
	bool loadOkay = doc->LoadFile();

	if ( !loadOkay )
	{
		printf( "Could not load file '%s'. Error='%s'. Exiting.\n", filename, doc->ErrorDesc() );
		exit( 1 );
	}

	TiXmlElement* anfElement= doc->FirstChildElement( "anf" );

	if (anfElement == NULL)
	{
		printf("Main anf block element not found! Exiting!\n");
		exit(1);
	}



	globElement = anfElement->FirstChildElement( "globals" );
	matsElement = anfElement->FirstChildElement( "Materials" );
	textsElement =  anfElement->FirstChildElement( "Textures" );
	leavesElement =  anfElement->FirstChildElement( "Leaves" );
	nodesElement =  anfElement->FirstChildElement( "Nodes" );
	graphElement =  anfElement->FirstChildElement( "Graph" );


	// Init
	// An example of well-known, required nodes

	if (globElement == NULL)
		printf("Init block not found!\n");
	else
	{
		printf("Processing init:\n");
		// frustum: example of a node with individual attributes
		TiXmlElement* drawElement= globElement->FirstChildElement("drawing");
		if (drawElement)
		{
			char *mode =NULL, *shading =NULL, *valstring;
			float r,g,b,a;
			mode = (char *) drawElement->Attribute("mode");
			shading = (char *) drawElement->Attribute("shading");
			valstring = (char *) drawElement->Attribute("background");

			if (mode&& shading&&valstring && sscanf(valstring,"%f %f %f %f",&r,&g,&b,&a) ==4)
				printf("  drawing attributes: %s %s\n , background %f %f %f %f \n", mode, shading, r ,g ,b ,a);
			else
				printf("Error drawing frustum\n");
		}
		else
			printf("drawing not found\n");


		// translate: example of a node with an attribute comprising several float values
		// It shows an example of extracting an attribute's value, and then further parsing that value 
		// to extract individual values
		TiXmlElement* culElement=globElement->FirstChildElement("culling");
		if (culElement)
		{
			char *face=NULL, *order = NULL;


			face=(char *) culElement->Attribute("face");
			order=(char *) culElement->Attribute("order");

			if(face && order)
			{
				printf("  culling values: face: %s  order: %s\n", face,order);
			}
			else
				printf("Error parsing culling");
		}
		else
			printf("culling not found\n");  

		TiXmlElement* lightElement = globElement->FirstChildElement("lighting");
		if (lightElement)
		{
			char *valStringD=NULL, *valStringL = NULL,  *valStringE = NULL,  *valStringA = NULL;//doublesided, local, enable, ambient
			int doublesided, local, enabled;
			float r,g,b,a;

			valStringD=(char *) lightElement->Attribute("doublesided");
			valStringL=(char *) lightElement->Attribute("local");
			valStringE=(char *) lightElement->Attribute("enabled");
			valStringA=(char *) lightElement->Attribute("ambient");


			if(valStringD && valStringL && valStringE && valStringA && sscanf(valStringA,"%f %f %f %f",&r,&g,&b,&a) ==4)
			{
				if(strcmp(valStringD,"true")==0)
					doublesided = 1;
				else
					doublesided = 0;
				if(strcmp(valStringL,"true")==0)
					local = 1;
				else
					local = 0;
				if(strcmp(valStringE,"true")==0)
					enabled = 1;
				else
					enabled = 0;

				printf("lightning values: doublesided: %d  , local: %d , enabled:  %d \n ambient: %f %f %f %f \n",doublesided,local,enabled,r,g,b,a);
			}
			else
				printf("Error parsing lightning");
		}
		else
			printf("lightning not found\n");


		// repeat for each of the variables as needed
	}

	// Other blocks could be validated/processed here


	// graph section
	if (graphElement == NULL)
		printf("Graph block not found!\n");
	else
	{
		char *prefix="  -";
		TiXmlElement *node=graphElement->FirstChildElement();

		while (node)
		{
			printf("Node id '%s' - Descendants:\n",node->Attribute("id"));
			TiXmlElement *child=node->FirstChildElement();
			while (child)
			{
				if (strcmp(child->Value(),"Node")==0)
				{
					// access node data by searching for its id in the nodes section

					TiXmlElement *noderef=findChildByAttribute(nodesElement,"id",child->Attribute("id"));

					if (noderef)
					{
						// print id
						printf("  - Node id: '%s'\n", child->Attribute("id"));

						// prints some of the data
						printf("    - Material id: '%s' \n", noderef->FirstChildElement("material")->Attribute("id"));
						printf("    - Texture id: '%s' \n", noderef->FirstChildElement("texture")->Attribute("id"));

						// repeat for other leaf details
					}
					else
						printf("  - Node id: '%s': NOT FOUND IN THE NODES SECTION\n", child->Attribute("id"));

				}
				if (strcmp(child->Value(),"Leaf")==0)
				{
					// access leaf data by searching for its id in the leaves section
					TiXmlElement *leaf=findChildByAttribute(leavesElement,"id",child->Attribute("id"));

					if (leaf)
					{
						// it is a leaf and it is present in the leaves section
						printf("  - Leaf id: '%s' ; type: '%s'\n", child->Attribute("id"), leaf->Attribute("type"));

						// repeat for other leaf details
					}
					else
						printf("  - Leaf id: '%s' - NOT FOUND IN THE LEAVES SECTION\n",child->Attribute("id"));
				}

				child=child->NextSiblingElement();
			}
			node=node->NextSiblingElement();
		}
	}

}

XMLScene::~XMLScene()
{
	delete(doc);
}

//-------------------------------------------------------

TiXmlElement *XMLScene::findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val)
	// Searches within descendants of a parent for a node that has an attribute _attr_ (e.g. an id) with the value _val_
	// A more elaborate version of this would rely on XPath expressions
{
	TiXmlElement *child=parent->FirstChildElement();
	int found=0;

	while (child && !found)
		if (child->Attribute(attr) && strcmp(child->Attribute(attr),val)==0)
			found=1;
		else
			child=child->NextSiblingElement();

	return child;
}


