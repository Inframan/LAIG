#include "torus.h"


torus::torus(float inner, float outer, int slices, int loops)
{
	this->inner = inner;
	this->outer = outer;
	this->slices= slices;
	this->loops = loops;
}

float torus::getInner()const
{
	return inner;
}
float torus::getOuter()const
{
	return outer;
}
int torus::getSlices()const
{
	return slices;
}
int torus::getLoops()const
{
	return loops;
}

void torus::draw()
{
	double pi = acos(-1.0);
	float vNormal[3];   
    double majorStep = 2.0f*pi / slices;   
    double minorStep = 2.0f*pi / loops;   
    int i, j;   
   
    for (i=0; i<slices; ++i)    
            {   
            double a0 = i * majorStep;   
            double a1 = a0 + majorStep;   
            GLfloat x0 = (GLfloat) cos(a0);   
            GLfloat y0 = (GLfloat) sin(a0);   
            GLfloat x1 = (GLfloat) cos(a1);   
            GLfloat y1 = (GLfloat) sin(a1);   
   
            glBegin(GL_TRIANGLE_STRIP);   
            for (j=0; j<=loops; ++j)    
                    {   
                    double b = j * minorStep;   
                    GLfloat c = (GLfloat) cos(b);   
                    GLfloat r = inner * c + outer;   
                    GLfloat z = inner * (GLfloat) sin(b);   
   
                    // First point   
                    glTexCoord2f((float)(i)/(float)(loops), (float)(j)/(float)(slices));   
                    vNormal[0] = x0*c;   
                    vNormal[1] = y0*c;   
                    vNormal[2] = z/inner;   
                    //gltNormalizeVector(vNormal);   
                    glNormal3fv(vNormal);   
                    glVertex3f(x0*r, y0*r, z);   
   
                    glTexCoord2f((float)(i+1)/(float)(loops), (float)(j)/(float)(slices));   
                    vNormal[0] = x1*c;   
                    vNormal[1] = y1*c;   
                    vNormal[2] = z/inner;   
					glNormal3f(vNormal[0],vNormal[1],vNormal[2]);   
                    glVertex3f(x1*r, y1*r, z);   
                    }   
            glEnd();   
            }   


}

torus::~torus(void)
{
}
