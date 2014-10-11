#include "XMLScene.h"

XMLScene::XMLScene(char *filename, sceneGraph * graph)
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
	camerasElement = anfElement->FirstChildElement( "cameras" );
	lightsElement = anfElement->FirstChildElement( "lights" );
	appearancesElement = anfElement->FirstChildElement( "appearances" );
	textsElement = anfElement->FirstChildElement( "textures" );
	graphElement =  anfElement->FirstChildElement( "graph" );


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
			{
				vector<float> bg;
				bg.push_back(r);
				bg.push_back(g);
				bg.push_back(b);
				bg.push_back(a);
				graph->setDrawingMode(mode);
				graph->setShading(shading);
				graph->setBackground(bg);
				printf("  drawing attributes: %s %s\n , background %f %f %f %f \n", mode, shading, r ,g ,b ,a);
			}
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
				graph->setCullingFace(face);
				graph->setCullOrder(order);
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
				vector<float> amb;
				amb.push_back(r);
				amb.push_back(g);
				amb.push_back(b);
				amb.push_back(a);

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

				graph->setDSided(doublesided);
				graph->setlLocal(local);
				graph->setlEnabled(enabled);
				graph->setLAmbient(amb);

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

		char * rootId = (char*) graphElement->Attribute("rootid");
		string rID(rootId);
		graph->setRootID(rID);
		char *prefix="  -";
		TiXmlElement *node=graphElement->FirstChildElement();

		while (node)
		{
			Node node1 = Node(node->Attribute("id"));

			printf("Node id '%s' - Descendants:\n",node->Attribute("id"));
			TiXmlElement * transforms = node->FirstChildElement();
			if (transforms == NULL)
				printf("Transforms block not found!\n");
			else //TRANSFORMACOES MATRICIAIS
			{
				TiXmlElement * tranformation = transforms->FirstChildElement();

				char * valString = NULL, * t = NULL;
				float m[4][4];

				while(tranformation)
				{
					t = (char *) tranformation->Attribute("type");
					string type(t);

					if(t == "translate")
					{
						float x,y,z;
						valString = (char*) tranformation->Attribute("to");
						if(sscanf(valString,"%f %f %f",&x,&y,&z) == 3)
						{

						}
					}
					else if(t == "rotate")
					{

					}
					else if(t == "scale")
					{

					}

					tranformation = tranformation->NextSiblingElement();
				}

			}

			TiXmlElement * appearance = transforms->NextSiblingElement();
			if (appearance == NULL)
				printf("Appearance block not found!\n");
			else //Definir aparencia do nó
			{
			}

			TiXmlElement *primitives = appearance->NextSiblingElement();
			if (primitives == NULL)
				printf("Primitives block not found!\n");
			else //Definir primitivas
			{
				TiXmlElement *primitivesDef = primitives->FirstChildElement("rectangle");	

				while(primitivesDef)
				{
					char * valString1=NULL, * valString2 = NULL;
					printf("  - Type id: '%s'\n", primitivesDef->Attribute("type"));

					valString1 = (char *) primitivesDef->Attribute("xy1");
					valString2 = (char *) primitivesDef->Attribute("xy2");
					float x1,x2,y1,y2;
					if(sscanf(valString1,"%f %f",&x1,&y1) ==2 && sscanf(valString2,"%f %f",&x2,&y2) ==2)
						node1.addRectangle(x1,y1,x2,y2);



					primitivesDef = primitivesDef->NextSiblingElement("rectangle");
				}

				primitivesDef = primitives->FirstChildElement("triangle");

				while(primitivesDef)
				{
					char * valString1=NULL, * valString2 = NULL;
					printf("  - Type id: '%s'\n", primitivesDef->Attribute("type"));


					char * valString3=NULL;
					float x1,x2,x3,y1,y2,y3,z1,z2,z3;
					valString1 = (char *) primitivesDef->Attribute("xyz1");
					valString2 = (char *) primitivesDef->Attribute("xyz2");
					valString3 = (char *) primitivesDef->Attribute("xyz3");
					if(sscanf(valString1,"%f %f %f",&x1,&y1,&z1) ==3 && sscanf(valString2,"%f %f %f",&x2,&y2,&z2) ==3 && sscanf(valString3,"%f %f %f",&x3,&y3,&z3) ==3)
						node1.addTriangle(x1,y1,z1,x2,y2,z2,x3,y3,z3);


					primitivesDef = primitivesDef->NextSiblingElement("triangle");
				}


				primitivesDef = primitives->FirstChildElement("cylinder");

				while(primitivesDef)
				{
					char * valString1=NULL, * valString2 = NULL;

					char * sHeigh = NULL,* sSlices = NULL,* sStacks = NULL;
					valString1 = (char *) primitivesDef->Attribute("base");
					valString2 = (char *) primitivesDef->Attribute("top");
					sHeigh = (char *) primitivesDef->Attribute("height");
					sSlices = (char *) primitivesDef->Attribute("slices");
					sStacks = (char *) primitivesDef->Attribute("stacks");
					float base,top,height;
					int slices,stacks;

					if(sscanf(valString1,"%f",&base) ==1 && sscanf(valString2,"%f",&top)==1 
						&& sscanf(sHeigh,"%f",&height) == 1 && sscanf(sSlices,"%d",&slices) == 1 && sscanf(sStacks,"%d",&stacks) == 1 )
						node1.addCylinder(base,top,height,slices,stacks);

					primitivesDef = primitivesDef->NextSiblingElement("cylinder");
				}


				primitivesDef = primitives->FirstChildElement("sphere");

				while(primitivesDef)
				{
					char * valString1=NULL, * valString2 = NULL;
					printf("  - Type id: '%s'\n", primitivesDef->Attribute("type"));

					char * sSlices = NULL,* sStacks = NULL;
					valString1 = (char *) primitivesDef->Attribute("radius");
					sSlices = (char *) primitivesDef->Attribute("slices");
					sStacks = (char *) primitivesDef->Attribute("stacks");
					float radius;
					int slices,stacks;
					if(sscanf(valString1,"%f",&radius) ==1 && sscanf(sSlices,"%d",&slices) == 1 && sscanf(sStacks,"%d",&stacks) == 1 )
						node1.addSphere(radius,slices,stacks);

					primitivesDef = primitivesDef->NextSiblingElement("sphere");
				}


			}


			TiXmlElement *descendants=primitives->NextSiblingElement();

			if(descendants == NULL)
				printf("Descendants block not found!\n");
			else
			{
				TiXmlElement *child =descendants->FirstChildElement();

				if(child != NULL)
					while (child)
					{
						char * nodeC = NULL;
						nodeC = (char *) child->Attribute("noderef");

						string childID(nodeC);

						node1.addDescendant(childID);

						child = child->NextSiblingElement();
					}


			}
			node=node->NextSiblingElement();
			graph->addNode(node1);
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


