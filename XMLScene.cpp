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
		char *prefix="  -";
		TiXmlElement *node=graphElement->FirstChildElement();

		while (node)
		{
			printf("Node id '%s' - Descendants:\n",node->Attribute("id"));
			TiXmlElement *child=node->FirstChildElement();
		
			Node node1 = Node(node->Attribute("id"));

			while (child)
			{
				if (strcmp(child->Value(),"Node")==0)
				{
					// access node data by searching for its id in the nodes section

					TiXmlElement *noderef=findChildByAttribute(nodesElement,"id",child->Attribute("id"));

					if (noderef)
					{
						char* d = NULL;
						d = (char*) child->Attribute("id");
						string desc(d);
						node1.addDescendant(d);
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
						char * valString=NULL;
						valString = (char*) leaf->Attribute("pars");
						char * t = (char*) leaf->Attribute("type");
						string type(t);
						// it is a leaf and it is present in the leaves section
						printf("  - Leaf id: '%s' ; type: '%s'\n", child->Attribute("id"), leaf->Attribute("type"));

						if(type == "rectangle")
						{
							float x1,x2,y1,y2;
							if(sscanf(valString,"%f %f %f %f",&x1,&y1,&x2,&y2) ==4)
								node1.addRectangle(x1,y1,x2,y2);

						}
						else if(type == "triangle")
						{
							float x1,x2,x3,y1,y2,y3,z1,z2,z3;
							if(sscanf(valString,"%f %f %f %f %f %f %f %f %f",&x1,&y1,&z1,&x2,&y2,&z2,&x3,&y3,&z3) ==9)
								node1.addTriangle(x1,y1,z1,x2,y2,z2,x3,y3,z3);
						}
						else if(type == "cylinder")
						{
							float base,top,height;
							int slices,stacks;
							if(sscanf(valString,"%f %f %f %d %d",&base,&top,&height,&slices,&stacks) ==5)
								node1.addCylinder(base,top,height,slices,stacks);
						}
						else if(type == "sphere")
						{
							float radius;
							int slices,stacks;
							if(sscanf(valString,"%f %d %d",&radius,&slices,&stacks) ==3)
								node1.addSphere(radius,slices,stacks);
						}

						// repeat for other leaf details
					}
					else
						printf("  - Leaf id: '%s' - NOT FOUND IN THE LEAVES SECTION\n",child->Attribute("id"));
				}

				child=child->NextSiblingElement();
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


