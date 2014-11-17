#include "patch.h"


patch::patch(void)
{
}

patch::patch(int order,int partsU,int partsV,string compute,float ** controlPoints):controlPoints(controlPoints)
{
	this->order = order;
	this->partsU = partsU;
	this->partsV = partsV;


	if(compute == "fill")
		this->compute = 1;
	else if(compute == "line")
		this->compute = 2;
	else
		this->compute = 3;

	int nPoints =  (order+1)*(order+1);

	textPoints = (float **) malloc( (order+1)*(order+1)*sizeof(float));

	float incS = 1.0/(order);
	float incT = 1.0/(order);
	float xS = 0;
	float yT = 0;
	for(int i = 0; i < nPoints;i++)
	{		
		if(xS > 1)
		{
			xS = 0;
			yT += incT;
		}
		textPoints[i] = (float*)malloc(2*sizeof(float));
		textPoints[i][0] = xS;
		textPoints[i][1] = yT;

		xS += incS;
	}

}

void patch::draw()
{
	/*
	GLfloat nrmcomponents[4][3] ={	{  0.0, 1.0, 0.0},
	{  0.0, 1.0, 0.0}, 
	{  0.0, 1.0, 0.0},
	{  0.0, 1.0, 0.0} };

	// As cores a atribuir a cada ponto de controlo:
	//   Nota: para uma boa percepcao do efeito de iluminacao, é
	//         aconselhável usar, em alternativa, uma cor cinzenta

	GLfloat texpoints[4][2] = {	{ 0.0, 0.0},
	{ 0.0, 1.0}, 
	{ 1.0, 0.0},
	{ 1.0, 1.0} };




	glColor3f(1.0,1.0,1.0);
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 2,  0.0, 1.0, 6, 2,  &controlPoints[0][0]);

	glMap2f(GL_MAP2_NORMAL,   0.0, 1.0, 3, 2,  0.0, 1.0, 6, 2,  &nrmcomponents[0][0]);
	glMap2f(GL_MAP2_TEXTURE_COORD_2,  0.0, 1.0, 2, 2,  0.0, 1.0, 4, 2,  &texpoints[0][0]);

	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_MAP2_NORMAL);
	glEnable(GL_MAP2_COLOR_4);
	glEnable(GL_MAP2_TEXTURE_COORD_2);

	glMapGrid2f(partsU, 0.0,1.0, partsV, 0.0,1.0); 


	// SEGUE-SE EXEMPLO DE UTILIZACAO DE "EVALUATORS"

	//if(gouraud)
	switch (compute)
	{
	case 1:		
	glShadeModel(GL_SMOOTH);
	break;
	case 2:
	glShadeModel(GL_LINE);
	break;
	case 3:
	glShadeModel(GL_POINT);
	break;
	}
	//else
	//glShadeModel(GL_FLAT);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);
	//myTexture->apply();



	/*switch(scene->wire)
	{
	case 0:*/	
	//glEvalMesh2(GL_FILL, 0,partsU, 0,partsV);	
	/*break;
	case 1:
	glEvalMesh2(GL_LINE, 0,10, 0,15);	
	break;
	case 2:		
	glEvalMesh2(GL_POINT, 0,10, 0,15);
	break;
	}*/

	// GL_POINT, GL_LINE, GL_FILL
	//glEvalMesh2(GL_FILL, 10,30, 20,40);	// poligono incompleto...
	//glEvalMesh2(GL_FILL, -10,50, -20,70);	// ...ou "transbordante"
	// NOTA: os 4 ultimos parametros da funcao glEvalMesh2() nao sao 
	//		 coordenadas mas sim indices de passos (do passo -10
	//		 ao passo 50; do passo -20 ao passo 70...

	// so' para referencia visual... onde estao os quatro pontos
	// de controlo:
	/*
	int nCP = (order+1)*(order+1);
	glColor3f(1.0, 1.0, 0.0);
	for (int i = 0; i < nCP; i++)
	{
	glRasterPos3f(controlPoints[i][0],controlPoints[i][1],controlPoints[i][2]+0.5);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '0'+i);
	}

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_COLOR_MATERIAL);
	*/

	/*
	GLfloat nrmlcompon[4][3] ={	{  0.0, 1.0, 0.0},
	{  0.0, 1.0, 0.0}, 
	{  0.0, 1.0, 0.0},
	{  0.0, 1.0, 0.0} };
	*/


	/*

	GLfloat textpoints[4][2] = {	{ 0.0, 0.0},
	{ 0.0, 1.0}, 
	{ 1.0, 0.0},
	{ 1.0, 1.0} };


	GLfloat nrmlcompon[4][3] ={	{  0.0, 1.0, 0.0},
	{  0.0, 1.0, 0.0}, 
	{  0.0, 1.0, 0.0},
	{  0.0, 1.0, 0.0} };



	glColor3f(1.0,1.0,1.0);
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 2,  0.0, 1.0, 6, 2,  &ctrlpoint[0][0]);
	glMap2f(GL_MAP2_NORMAL,   0.0, 1.0, 3, 2,  0.0, 1.0, 6, 2,  &nrmlcompon[0][0]);
	glMap2f(GL_MAP2_COLOR_4,  0.0, 1.0, 4, 2,  0.0, 1.0, 8, 2,  &colorpoints[0][0]);
	glMap2f(GL_MAP2_TEXTURE_COORD_2,  0.0, 1.0, 2, 2,  0.0, 1.0, 4, 2,  &textpoints[0][0]);

	// os interpoladores activam-se:
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_MAP2_NORMAL);
	glEnable(GL_MAP2_COLOR_4);
	glEnable(GL_MAP2_TEXTURE_COORD_2);

	// para este conjunto de interpoladores:
	//    na direccao U, serao efectuadas divisoes em 40 passos
	//        quando a variável U varia de 0 a 1
	//    na direccao V, serao efectuadas divisoes em 60 passos
	//        quando a variável U varia de 0 a 1
	glMapGrid2f(partsU, 0.0,1.0, partsV, 0.0,1.0); 


	// SEGUE-SE EXEMPLO DE UTILIZACAO DE "EVALUATORS"
	//glShadeModel(GL_FLAT);					// GL_FLAT, GL_SMOOTH
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);
	//myTexture->apply();


	glEvalMesh2(GL_FILL, 0,partsU, 0,partsV);		
	// GL_POINT, GL_LINE, GL_FILL
	//glEvalMesh2(GL_FILL, 10,30, 20,40);	// poligono incompleto...
	//glEvalMesh2(GL_FILL, -10,50, -20,70);	// ...ou "transbordante"
	// NOTA: os 4 ultimos parametros da funcao glEvalMesh2() nao sao 
	//		 coordenadas mas sim indices de passos (do passo -10
	//		 ao passo 50; do passo -20 ao passo 70...

	// so' para referencia visual... onde estao os quatro pontos
	// de controlo:


	glColor3f(1.0, 1.0, 0.0);
	for (int i = 0; i < 4; i++)
	{
	glRasterPos3f(controlPoints[i][0],controlPoints[i][1],controlPoints[i][2]+0.5);
	//glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '0'+i);
	}

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_COLOR_MATERIAL);



	*/





	

	/*
	switch (order)
	{
	case 1: 


	break;
	case 2:

	GLfloat ctrlpoint[9][3];
	GLfloat textpoints[9][2];
	break;
	case 3:

	GLfloat ctrlpoint[16][3];
	GLfloat textpoints[16][2];
	break;
	default:
	break;
	}*/

	if(order == 1)
	{GLfloat colorpoints[4][4] = {	{ 0.7, 0.7, 0.7, 0},	{ 0.7, 0.7, 0.7, 0}, 
	{ 0.7, 0.7, 0.7, 0},	{ 0.7, 0.7, 0.7, 0} };
		GLfloat ctrlpoint[4][3];
		GLfloat textpoints[4][2];
		for(int i = 0; i < (order+1)*(order+1);i++)
		{
			for(int j = 0; j < 3;j++)
			{
				ctrlpoint[i][j] = controlPoints[i][j];

			}

			for(int j = 0; j < 2;j++)
			{
				textpoints[i][j] = textPoints[i][j];
			}

		}
		glColor3f(1.0,1.0,1.0);
		glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, (order+1),  0.0, 1.0, 3*(order+1), (order+1),  &ctrlpoint[0][0]);
		//glMap2f(GL_MAP2_NORMAL,   0.0, 1.0, 3, 2                     ,  0.0, 1.0, 6, 2,  &nrmlcompon[0][0]);
		glMap2f(GL_MAP2_COLOR_4,  0.0, 1.0, 4, order+1,  0.0, 1.0,4*(order+1),order+1,  &colorpoints[0][0]);
		glMap2f(GL_MAP2_TEXTURE_COORD_2,  0.0, 1.0, 2, (order+1),  0.0, 1.0, 2 * (order+1), (order+1), &textpoints[0][0]);

	}
	else if(order == 2)
	{GLfloat colorpoints[9][4] = {	{ 0.7, 0.7, 0.7, 0},	{ 0.7, 0.7, 0.7, 0}, 	{ 0.7, 0.7, 0.7, 0},
	{ 0.7, 0.7, 0.7, 0},	{ 0.7, 0.7, 0.7, 0},	{ 0.7, 0.7, 0.7, 0},
	{ 0.7, 0.7, 0.7, 0},	{ 0.7, 0.7, 0.7, 0},	{ 0.7, 0.7, 0.7, 0} };
		GLfloat ctrlpoint[9][3];
		GLfloat textpoints[9][2];
		for(int i = 0; i < (order+1)*(order+1);i++)
		{
			for(int j = 0; j < 3;j++)
			{
				ctrlpoint[i][j] = controlPoints[i][j];

			}

			for(int j = 0; j < 2;j++)
			{
				textpoints[i][j] = textPoints[i][j];
			}

		}
		glColor3f(1.0,1.0,1.0);
		glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, (order+1),  0.0, 1.0, 3*(order+1), (order+1),  &ctrlpoint[0][0]);
		//glMap2f(GL_MAP2_NORMAL,   0.0, 1.0, 3, 2                     ,  0.0, 1.0, 6, 2,  &nrmlcompon[0][0]);
		glMap2f(GL_MAP2_COLOR_4,  0.0, 1.0, 4, order+1,  0.0, 1.0,4*(order+1),order+1,  &colorpoints[0][0]);
		glMap2f(GL_MAP2_TEXTURE_COORD_2,  0.0, 1.0, 2, (order+1),  0.0, 1.0, 2 * (order+1), (order+1), &textpoints[0][0]);

	
	}
	else if(order == 3)
	{
		GLfloat colorpoints[16][4] = {	{ 0.7, 0.7, 0.7, 0},	{ 0.7, 0.7, 0.7, 0}, 	{ 0.7, 0.7, 0.7, 0},	{ 0.7, 0.7, 0.7, 0},	{ 0.7, 0.7, 0.7, 0},	{ 0.7, 0.7, 0.7, 0},	{ 0.7, 0.7, 0.7, 0},
	{ 0.7, 0.7, 0.7, 0},	{ 0.7, 0.7, 0.7, 0},	{ 0.7, 0.7, 0.7, 0},	{ 0.7, 0.7, 0.7, 0},	{ 0.7, 0.7, 0.7, 0},	{ 0.7, 0.7, 0.7, 0},
	{ 0.7, 0.7, 0.7, 0},	{ 0.7, 0.7, 0.7, 0},	{ 0.7, 0.7, 0.7, 0} };
		GLfloat ctrlpoint[16][3];
		GLfloat textpoints[16][2];
		for(int i = 0; i < (order+1)*(order+1);i++)
		{
			for(int j = 0; j < 3;j++)
			{
				ctrlpoint[i][j] = controlPoints[i][j];
			}
			for(int j = 0; j < 2;j++)
			{
				textpoints[i][j] = textPoints[i][j];
			}
		}

		glColor3f(1.0,1.0,1.0);
		glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, (order+1),  0.0, 1.0, 3*(order+1), (order+1),  &ctrlpoint[0][0]);
		//glMap2f(GL_MAP2_NORMAL,   0.0, 1.0, 3, 2                     ,  0.0, 1.0, 6, 2,  &nrmlcompon[0][0]);
		glMap2f(GL_MAP2_COLOR_4,  0.0, 1.0, 4, order+1,  0.0, 1.0,4*(order+1),order+1,  &colorpoints[0][0]);
		glMap2f(GL_MAP2_TEXTURE_COORD_2,  0.0, 1.0, 2, (order+1),  0.0, 1.0, 2 * (order+1), (order+1), &textpoints[0][0]);
	
	}
	
		glFrontFace(GL_CW);
		glEnable(GL_MAP2_VERTEX_3);
		glEnable(GL_AUTO_NORMAL);
		//glEnable(GL_MAP2_NORMAL);
		glEnable(GL_MAP2_COLOR_4);
		glEnable(GL_MAP2_TEXTURE_COORD_2);

		glMapGrid2f(partsU, 0.0, 1.0, partsV, 0.0, 1.0); 

		// SEGUE-SE EXEMPLO DE UTILIZACAO DE "EVALUATORS"
		glEnable(GL_LIGHTING);
		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_TEXTURE_2D);


		switch (compute)
		{
		case 1:		
			glEvalMesh2(GL_FILL, 0, partsU, 0,partsV);
			break;
		case 2:
			glEvalMesh2(GL_LINE, 0, partsU, 0,partsV);
			break;
		case 3:
			glEvalMesh2(GL_POINT, 0, partsU, 0,partsV);
			break;
		}

		glColor3f(1.0, 1.0, 0.0);

		glDisable(GL_MAP2_VERTEX_3);
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_AUTO_NORMAL);

		glFrontFace(GL_CCW);
		//glDisable(GL_MAP2_NORMAL);
		glDisable(GL_COLOR_MATERIAL);
}


patch::~patch(void)
{
}
