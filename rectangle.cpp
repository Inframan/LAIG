#include "rectangle.h"


rectangle::rectangle(float x1,float y1,float x2,float y2)
{
	this->x1 = x1;
	this->x2 = x2;
	this->y1 = y1;
	this->y2 = y2;

}

vector<float> rectangle:: getCoords() const
{
	vector<float> temp;
	temp.push_back(x1);
	temp.push_back(y1);
	temp.push_back(x2);
	temp.push_back(y2);
	return temp;
}

void rectangle::draw(Texture * t)
{
	float width = t->getTexLengthS(), height = t->getTexLengthT(), lengthT = x2-x1,heightT = y2-y1;
	float tX,tY;

	tX = lengthT/width;
	tY = heightT/height;


	glBegin(GL_QUADS);
	glNormal3f(0,0,1);
	glTexCoord2f(0,0); 
	glVertex2f(x1,y1);
	
	glTexCoord2f(0,tY);
	glVertex2f(x2,y1);

	glTexCoord2f(tX,tY);
	glVertex2f(x2,y2);

	
	glTexCoord2f(tX,0);
	glVertex2f(x1,y2);
	glEnd();
}


void rectangle::draw()
{
	glBegin(GL_QUADS);
	glNormal3f(0,0,1);	
	glTexCoord2f(0,0); 
	glVertex2f(x1,y1);
	glTexCoord2f(1,0); 
	glVertex2f(x2,y1);
	glTexCoord2f(1,1); 
	glVertex2f(x2,y2);
	glTexCoord2f(0,1); 
	glVertex2f(x1,y2);
	glEnd();
}

rectangle::~rectangle(void)
{
}
