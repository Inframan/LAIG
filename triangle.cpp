#include "triangle.h"

using namespace std;

triangle::triangle(float x1,float y1,float z1,float x2,float y2,float z2,float x3,float y3,float z3)
{
	this->x1 = x1;
	this->y1 = y1;
	this->z1 = z1;
	
	this->x2 = x2;
	this->y2 = y2;
	this->z2 = z2;
	
	this->x3 = x3;
	this->y3 = y3;
	this->z3 = z3;

	
	lengthT = sqrt( (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2));//comprimento da base
	float alfa = acos(  (x3-x1)*(y2-y1)*(z3-z1)+(x2-x1)*(y3-y1)*(z2-z1));//ângulo do triangulo (através do produto interno)
	heightT = sin( alfa)*sqrt( (x1-x3)*(x1-x3)+(y1-y3)*(y1-y3)+(z1-z3)*(z1-z3));//seno do ângulo * comprimento entre p1 e p2 (deverá dar a altura)


}

vector<float> triangle::getCoords()const
{
	vector<float> temp;
	temp.push_back(x1);
	temp.push_back(y1);
	temp.push_back(z1);
	temp.push_back(x2);
	temp.push_back(y2);
	temp.push_back(z2);
	temp.push_back(x3);
	temp.push_back(y3);
	temp.push_back(z3);
	return temp;
}

void triangle::draw()
{
	glBegin(GL_TRIANGLES);
	glVertex3f(x1,y1,z1);
	glVertex3f(x2,y2,z2);
	glVertex3f(x3,y3,z3);
	glEnd();
}

void triangle::draw(Texture * t)
{
	float width = t->getTexLengthS(), height = t->getTexLengthT();
	float tX,tY;

	tX = lengthT/width;
	tY = heightT/height;

	glBegin(GL_TRIANGLES);

	glNormal3f(x1, y1,1);
	glTexCoord2f(0,0);
	glVertex3f(x1,y1,z1);

	glNormal3f(x2, y2,1);
	glTexCoord2f(tX,0);
	glVertex3f(x2,y2,z2);

	glNormal3f(z3,y3,1);
	glTexCoord2f(tX,tY);
	glVertex3f(x3,y3,z3);
	glEnd();

}

triangle::~triangle(void)
{
}
