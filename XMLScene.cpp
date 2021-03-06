#include "XMLScene.h"
#include "GL/glu.h"

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


	animeElement = anfElement->FirstChildElement( "animations" );
	globElement = anfElement->FirstChildElement( "globals" );
	camerasElement = anfElement->FirstChildElement( "cameras" );
	lightsElement = anfElement->FirstChildElement( "lights" );
	appearancesElement = anfElement->FirstChildElement( "appearances" );
	textsElement = anfElement->FirstChildElement( "textures" );
	graphElement =  anfElement->FirstChildElement( "graph" );


	// Init
	// An example of well-known, required nodes



	if(animeElement)
	{
		TiXmlElement* anime = animeElement->FirstChildElement();

		while(anime)
		{
			char* type = (char*) anime->Attribute("type");
			char * id = NULL;
			char * stringVal = NULL;
			char * loopVal = NULL;
			float span;
			bool loop = false;

			loopVal = (char*) anime->Attribute("loop");

			if(loopVal)
			{
				if(strcmp(loopVal,"true")==0)
					loop = true;
				else
					loop = false;				
			}

			id = (char *) anime->Attribute("id");
			stringVal =  (char *) anime->Attribute("span");
			if(sscanf(stringVal,"%f",&span) == 1)
			{
				if(strcmp(type,"linear") == 0)
				{
					
					linearAnimation * lAnime= new linearAnimation(id,span,loop);

					TiXmlElement* outOfControl = anime->FirstChildElement();
					while(outOfControl)
					{
						float x,y,z;
						char* cX = NULL,*cY = NULL,*cZ = NULL;
						cX = (char*) outOfControl->Attribute("xx");
						cY = (char*) outOfControl->Attribute("yy");
						cZ = (char*) outOfControl->Attribute("zz");

						if(sscanf(cX,"%f",&x) == 1 && sscanf(cY,"%f",&y) == 1 && sscanf(cZ,"%f",&z) == 1)	
							lAnime->addPoint(x,y,z);
						else
						{
							printf("ERROR WITH ANIMATION\N");
							exit(1);
						}

						outOfControl = outOfControl->NextSiblingElement();
					}
					lAnime->changeControlPoint();
					lAnime->calculateTotalDistance();

					graph->addAnimation(lAnime);

				}
				//<animation id=�ss� span=�ff� type=�circular� center="ff ff ff" radius="ff" startang="ff" rotang="ff" />
				else if(strcmp(type,"circular") == 0)
				{
					char * valCentre = NULL;
					char * valRadius = NULL;
					char * valRotAng = NULL;
					char * valStAng = NULL;
					float cx,cy,cz,rotAng,startAng,radius;
					valCentre = (char *) anime->Attribute("center");
					valRadius = (char *)anime->Attribute("radius");
					valRotAng =(char *) anime->Attribute("rotang");
					valStAng = (char *)anime->Attribute("startang");
					if(sscanf(valCentre,"%f %f %f",&cx,&cy,&cz) == 3 && sscanf(valRadius,"%f",&radius) == 1 && sscanf(valRotAng,"%f",&rotAng) == 1  && sscanf(valStAng,"%f",&startAng) == 1)	
					{

					circularAnimation * cAnime = new circularAnimation(id,span,cx,cy,cz,rotAng,startAng,radius,loop);
						
					graph->addAnimation(cAnime);
					}
				}
			}
			anime = anime->NextSiblingElement();
		}


	}

	/////////GLOBAL VARIABLES
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

	////////CAMERAS   /////////////
	if (camerasElement == NULL)
		printf("Cameras block not found!\n");
	else
	{
		char * rootCamera = NULL;
		rootCamera = (char*) camerasElement->Attribute("initial");
		string rc(rootCamera);
		graph->setCameraID(rc);

		TiXmlElement *cam=camerasElement->FirstChildElement("ortho");

		while(cam)
		{
			camera * camr;
			char * camID = NULL;
			camID = (char*)cam->Attribute("id");     
			char * direction = (char *) cam->Attribute("direction");
			char * stNear = (char *) cam->Attribute("near");
			char * stFar = (char *) cam->Attribute("far");
			char * stLeft = (char *) cam->Attribute("left");
			char * stRight = (char *) cam->Attribute("right");
			char * stTop = (char *) cam->Attribute("top");
			char * stBot = (char *) cam->Attribute("bottom");
			float near,far,left,right,top,bot;

			if(sscanf(stNear,"%f",&near) == 1 && sscanf(stFar,"%f",&far) == 1 && sscanf(stLeft,"%f",&left) == 1
				&& sscanf(stRight,"%f",&right) == 1 && sscanf(stTop,"%f",&top) == 1 && sscanf(stBot,"%f",&bot) == 1)
				camr = new orthogonal(camID,direction[0],near,far,left,right,top,bot);

			graph->addCamera(camr);
			cam = cam->NextSiblingElement("ortho");
		}

		cam=camerasElement->FirstChildElement("perspective");
		while(cam)
		{
			camera * camr;
			char * camID = NULL;
			camID = (char*)cam->Attribute("id");     
			string ID(camID);
			char * stNear = (char *) cam->Attribute("near");
			char * stFar = (char *) cam->Attribute("far");
			char * stAngle = (char *) cam->Attribute("angle");
			char * stPos= (char *) cam->Attribute("pos");
			char * stTarget = (char *) cam->Attribute("target");
			float near,far,angle,posX,posY,posZ,targetX,targetY,targetZ;

			if( sscanf(stNear,"%f",&near) == 1 && sscanf(stFar,"%f",&far) == 1  && sscanf(stAngle,"%f",&angle) == 1 && sscanf(stPos,"%f %f %f",&posX,&posY,&posZ) == 3
				&& sscanf(stTarget,"%f %f %f",&targetX,&targetY,&targetZ) == 3)
				camr = new perspective(ID,near,far,angle,posX,posY,posZ,targetX,targetY,targetZ);


			graph->addCamera(camr);
			cam = cam->NextSiblingElement("perspective");
		}

	}

	//////////////LIGHTS 

	if (lightsElement == NULL)
		printf("Lights block not found!\n");
	else
	{


		TiXmlElement *light=lightsElement->FirstChildElement("light");

		while(light)
		{
			int enabled,marker;
			float posX,posY,posZ;
			vector<float> posV;
			char * id = NULL, *type = NULL, *sEnabled = NULL, * sMarker = NULL, *pos = NULL;


			id = (char*) light->Attribute("id");
			type = (char*) light->Attribute("type");
			string t(type);
			sEnabled = (char*) light->Attribute("enabled");			
			sMarker = (char*) light->Attribute("marker");		
			string sE(sEnabled),	sM(sMarker);
			pos = (char*) light->Attribute("pos");

			if(sscanf(pos,"%f %f %f",&posX,&posY,&posZ) == 3)
			{
				if(sE == "true")
					enabled = true;
				else 
					enabled = false;
				if(sM == "true")
					marker = true;
				else
					marker = false;

				posV.push_back(posX);
				posV.push_back(posY);
				posV.push_back(posZ);

			}

			myLight lightToSave = myLight(id,type,enabled,marker,posV);

			if(t == "spot")
			{
				float angle, exponent, targetX,targetY,targetZ;
				char *valAngle =NULL,*valExp =NULL,*valTarget =NULL;
				valAngle = (char*) light->Attribute("angle");
				valExp = (char*) light->Attribute("exponent");
				valTarget = (char*) light->Attribute("target");
				if(sscanf(valAngle,"%f",&angle) ==1 && sscanf(valExp,"%f",&exponent)  == 1 && sscanf(valTarget,"%f %f %f",&targetX,&targetY,&targetZ) == 3)
				{
					vector<float> targetV;
					targetV.push_back(targetX);
					targetV.push_back(targetY);
					targetV.push_back(targetZ);
					lightToSave.setAngle(angle);
					lightToSave.setExponent(exponent);
					lightToSave.setTarget(targetV);
				}
			}

			TiXmlElement *lightComponent = light->FirstChildElement();//

			vector<float> zeros;// serve para p�r as luzes a 0
			zeros.push_back(0.0);
			zeros.push_back(0.0);
			zeros.push_back(0.0);
			zeros.push_back(0.0);
			lightToSave.setAmbient(zeros);
			lightToSave.setDiffuse(zeros);
			lightToSave.setSpecular(zeros);

			while(lightComponent)
			{
				float r,g,b,a;
				char * type = (char*) lightComponent->Attribute("type");
				string t(type);
				char * valString = (char*) lightComponent->Attribute("value");

				if(sscanf(valString,"%f %f %f %f",&r,&g,&b,&a) == 4)
				{
					vector<float> values;
					values.push_back(r);
					values.push_back(g);
					values.push_back(b);
					values.push_back(a);
					if(t == "ambient")
					{
						lightToSave.setAmbient(values);
					}
					else if(t == "diffuse")
					{
						lightToSave.setDiffuse(values);
					}
					else if(t == "specular")
					{
						lightToSave.setSpecular(values);
					}

				}


				lightComponent = lightComponent->NextSiblingElement();
			}

			graph->addLight(lightToSave);
			light = light->NextSiblingElement();
		}


	}




	//TEXTURE BLOCK

	if (textsElement == NULL)
		printf("Text block not found!\n");
	else
	{
		TiXmlElement *textures=textsElement->FirstChildElement();

		while(textures){

			char *Id=NULL , *file=NULL, *texlength_s=NULL, *texlength_t=NULL;
			float texlength_S=0, texlength_T=0;
			Id = (char*) textures->Attribute("id");
			file =(char*) textures->Attribute("file");
			texlength_s= (char *)textures->Attribute("texlength_s");
			texlength_t= (char *)textures->Attribute("texlength_t");

			if(sscanf(texlength_s,"%f",&texlength_S) == 1 && sscanf(texlength_t,"%f",&texlength_T) == 1){
				Texture t = Texture(Id , file,texlength_S,texlength_T);
				graph->addTexture(t);	
			}

			textures= textures->NextSiblingElement();
		}

	}

	//appearence block

	if (appearancesElement == NULL)
		printf("Appearence block not found!\n");
	else
	{



		TiXmlElement *appearances=appearancesElement->FirstChildElement("appearance");

		while(appearances)
		{
			float shininess = 0;
			char * id = NULL, *shininessStr = NULL, *textureref = NULL;

			id = (char*) appearances->Attribute("id");
			shininessStr = (char*) appearances->Attribute("shininess");
			textureref = (char*) appearances->Attribute("textureref");			


			sscanf(shininessStr,"%f",&shininess);
			Appearence appearenceToSave;
			if(textureref)
				appearenceToSave = Appearence(id,shininess,textureref);
			else
				appearenceToSave = Appearence(id,shininess);


			TiXmlElement * appearenceComponent = appearances->FirstChildElement();

			while(appearenceComponent)
			{
				float r,g,b,a;
				char * type = (char*) appearenceComponent->Attribute("type");
				string t(type);
				char * valString = (char*) appearenceComponent->Attribute("value");
				float ambientArray[4];
				float diffuseArray[4];
				float specularArray[4];
				if(sscanf(valString,"%f %f %f %f",&r,&g,&b,&a) == 4)
				{
					vector<float> values;
					values.push_back(r);
					values.push_back(g);
					values.push_back(b);
					values.push_back(a);
					if(t == "ambient")
					{
						appearenceToSave.setAmbient(values);
						for (int i = 0 ; i < values.size();i++)
							ambientArray[i]=values[i];
					}
					else if(t == "diffuse")
					{
						appearenceToSave.setDiffuse(values);
						for (int i = 0 ; i < values.size();i++)
							diffuseArray[i]=values[i];
					}
					else if(t == "specular")
					{
						appearenceToSave.setSpecular(values);
						for (int i = 0 ; i < values.size();i++)
							specularArray[i]=values[i];
					}

				}




				CGFappearance * app = new CGFappearance(ambientArray,diffuseArray,specularArray,shininess);
				appearenceToSave.setAppearance(app);
				for(int j= 0 ; j < graph->getTextures().size();j++){
					if(textureref)
						if (textureref == graph->getTextures()[j].getID())
						{
							Texture * text = new Texture();
							(*text) = graph->getTextures()[j];
							appearenceToSave.setTexture(text);
						}
				}
				appearenceComponent = appearenceComponent->NextSiblingElement();

			}

			graph->addAppearence(appearenceToSave);
			appearances = appearances->NextSiblingElement();
		}


	}


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
			Node node1;
			char * displayList = NULL;
			bool dL;
			displayList = (char*) node->Attribute("displaylist");

			TiXmlElement* animationRef = node->FirstChildElement("animationref");

			if(displayList)
			{
				if(strcmp(displayList,"true")==0)
					dL = true;
				else
					dL = false;
				node1 = Node(node->Attribute("id"),dL);
			}
			else
				node1 = Node(node->Attribute("id"));

			while(animationRef)
			{
				char * aniRef = NULL;
				aniRef = (char*) animationRef->Attribute("id");
				node1.addAnimation(graph->animations.find(aniRef)->second);

				animationRef = animationRef->NextSiblingElement("animationref");
			}




			printf("Node id '%s' - Descendants:\n",node->Attribute("id"));
			TiXmlElement * transforms = node->FirstChildElement("transforms");
			if (transforms == NULL)
				printf("Transforms block not found!\n");
			else //TRANSFORMACOES MATRICIAIS
			{
				TiXmlElement * tranformation = transforms->FirstChildElement();

				char * valString = NULL, * t = NULL;
				float m[4][4];

				glLoadIdentity();
				while(tranformation)
				{
					t = (char *) tranformation->Attribute("type");
					string type(t);

					if(type == "translate")
					{
						float x,y,z;
						valString = (char*) tranformation->Attribute("to");
						if(sscanf(valString,"%f %f %f",&x,&y,&z) == 3)
						{
							glTranslated(x,y,z);
						}
					}
					else if(type == "rotate")
					{
						float angle;
						char * eixo = NULL;
						eixo = (char *) tranformation->Attribute("axis");
						valString = (char*) tranformation->Attribute("angle");
						if(sscanf(valString,"%f",&angle) == 1)
						{
							if(eixo[0] == 'x')
								glRotated(angle,1,0,0);
							else	if(eixo[0] == 'y')
								glRotated(angle,0,1,0);
							else 	if(eixo[0] == 'z')
								glRotated(angle,0,0,1);
							else
								printf("erro na rota��o \n");
						}
					}
					else if(type == "scale")
					{
						float x,y,z;
						valString = (char*) tranformation->Attribute("factor");
						if(sscanf(valString,"%f %f %f",&x,&y,&z) == 3)
						{
							glScaled(x,y,z);
						}
					}

					tranformation = tranformation->NextSiblingElement();
				}

				glGetFloatv(GL_MODELVIEW_MATRIX, &m[0][0]);

				node1.setMatrix(m);
			}

			TiXmlElement * appearanceref = transforms->NextSiblingElement("appearanceref");
			if (appearanceref == NULL)
				printf("Appearance block not found!\n");
			else //Definir aparencia do n�
			{

				char* id = NULL;

				id = (char*) appearanceref->Attribute("id");
				if(!id)
				{
					id = "";
				}
				string ID(id);
				node1.setAppearenceRef(ID);
				if(ID != "inherit" && ID!="")
				{
					Appearence *app = new Appearence();
					(*app) = graph->getAppearence().find(ID)->second;

					node1.setAppearence(app);
				}
			}

			TiXmlElement *primitives = transforms->NextSiblingElement("primitives");
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

				primitivesDef = primitives->FirstChildElement("torus");

				while(primitivesDef)
				{
					char * valString1=NULL, * valString2 = NULL;
					printf("  - Type id: '%s'\n", primitivesDef->Attribute("type"));

					char * sSlices = NULL,* sLoops = NULL;
					valString1 = (char *) primitivesDef->Attribute("inner");
					valString2 = (char *) primitivesDef->Attribute("outer");
					sSlices = (char *) primitivesDef->Attribute("slices");
					sLoops = (char *) primitivesDef->Attribute("loops");
					float inner,outer;
					int slices,loops;
					if(sscanf(valString1,"%f",&inner) ==1 &&sscanf(valString2,"%f",&outer) ==1 && sscanf(sSlices,"%d",&slices) == 1 && sscanf(sLoops,"%d",&loops) == 1 )
						node1.addTorus(inner,outer,slices,loops);

					primitivesDef = primitivesDef->NextSiblingElement("torus");
				}



				primitivesDef = primitives->FirstChildElement("plane");

				while(primitivesDef)
				{
					int parts;
					char * partsS =NULL;
					partsS = (char*)primitivesDef->Attribute("parts");
					printf("  - Type id: '%s'\n", partsS);

					if(sscanf(partsS,"%d",&parts) ==1)
						node1.addPlane(parts);

					primitivesDef = primitivesDef->NextSiblingElement("plane");
				}
				//	<patch order=�ii� partsU=�ii� partsV=�ii� compute=�ss�>
				//<controlpoint x=�ff� y=�ff� z=�ff� />


				primitivesDef = primitives->FirstChildElement("patch");

				while(primitivesDef)
				{
					int pU,pV,od;
					char * partsU =NULL;					
					char * partsV =NULL;										
					char * order =NULL;
					char * compute =NULL;

					order = (char*)primitivesDef->Attribute("order");
					partsU = (char*)primitivesDef->Attribute("partsU");
					partsV = (char*)primitivesDef->Attribute("partsV");
					compute = (char*)primitivesDef->Attribute("compute");

					TiXmlElement * controlPoint = primitivesDef->FirstChildElement();
					if(sscanf(partsU,"%d",&pU) ==1 && sscanf(partsV,"%d",&pV) ==1 && sscanf(order,"%d",&od) ==1)
					{
						float cx,cy,cz;
						char * sY = NULL,*sX = NULL,*sZ = NULL;
						int ctrlPtsN = (od+1)*(od+1);
					//	GLfloat ** controlPoints = (GLfloat**) malloc(ctrlPtsN *sizeof(float));
						vector<float> controlPoints;
						for(int i = 0; i < ctrlPtsN;i++)
						{
							if(controlPoint)
							{
								sZ = (char *) controlPoint->Attribute("z");							
								sY = (char *) controlPoint->Attribute("y");
								sX = (char *) controlPoint->Attribute("x");
								if(sscanf(sX,"%f",&cx) ==1 && sscanf(sY,"%f",&cy) ==1 && sscanf(sZ,"%f",&cz) ==1)
								{
									controlPoints.push_back(cx);
									controlPoints.push_back(cy);
									controlPoints.push_back(cz);
								}
								controlPoint = controlPoint->NextSiblingElement();
							}
							else
							{
								exit(1);
							}
						}

						node1.addPatch(od,pU,pV,compute,controlPoints);
					}

					primitivesDef = primitivesDef->NextSiblingElement("patch");
				}

				primitivesDef = primitives->FirstChildElement("flag");

				while(primitivesDef)
				{
					char * text=NULL;
					char * id=NULL;
					printf("  - filepath: '%s'\n", primitivesDef->Attribute("texture"));

					text = (char *) primitivesDef->Attribute("texture");
					string texture(text);
					node1.addFlag(new CGFtexture(texture));

					primitivesDef = primitivesDef->NextSiblingElement("flag");
				}

				
				primitivesDef = primitives->FirstChildElement("vehicle");

				while(primitivesDef)
				{
					node1.addOvni();

					primitivesDef = primitivesDef->NextSiblingElement("flag");
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
						nodeC = (char *) child->Attribute("id");

						string childID(nodeC);

						node1.addDescendant(childID);

						child = child->NextSiblingElement();
					}


			}
			node=node->NextSiblingElement();
			graph->addNode(node1);
		}
	}

	graph->setDescendantNode();
	graph->setRootNode();
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


