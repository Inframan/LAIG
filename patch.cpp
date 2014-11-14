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

}

void patch::draw()
{
	
	

	
	glColor3f(1.0,1.0,1.0);
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 2,  0.0, 1.0, 6, 2,  &controlPoints[0][0]);
	//glMap2f(GL_MAP2_NORMAL,   0.0, 1.0, 3, 2,  0.0, 1.0, 6, 2,  &nrmcomponents[0][0]);
	//glMap2f(GL_MAP2_TEXTURE_COORD_2,  0.0, 1.0, 2, 2,  0.0, 1.0, 4, 2,  &texpoints[0][0]);

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
		glEvalMesh2(GL_FILL, 0,partsU, 0,partsV);	
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


	glColor3f(1.0, 1.0, 0.0);
	for (int i = 0; i < 4; i++)
	{
		glRasterPos3f(controlPoints[i][0],controlPoints[i][1],controlPoints[i][2]+0.5);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '0'+i);
	}

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_COLOR_MATERIAL);
	


}


patch::~patch(void)
{
}
