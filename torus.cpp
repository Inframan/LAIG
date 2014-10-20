#include "torus.h"


torus::torus(float inner, float outer, int slices, int loops)
{
	this->inner = inner;
	this->outer = outer;
	this->slices= slices;
	this->loops = loops;

	pi = acos(-1.0);
	majorStep = 2.0f*pi / slices;   
	minorStep = 2.0f*pi / loops; 

	for (int i=0; i<slices; i++)    
	{   
		double a0 = i * majorStep;   
		x.push_back(cos(a0));
		y.push_back(sin(a0));   
		for (int j=0; j<=loops; ++j)    
		{   
			double b = j * minorStep;   
			c.push_back(cos(b));
			r.push_back(inner * c[j] + outer);   
			z.push_back(inner *sin(b));	
		}   
		glEnd();   
	}   


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

	for (int i=0; i<slices; ++i)    
	{   

		glBegin(GL_TRIANGLE_STRIP);   
		for (int j=0; j<=loops; ++j)    
		{   

			// First point   
			glTexCoord2f((float)(i)/(float)(loops), (float)(j)/(float)(slices));   
			vNormal[0] = x[i]*c[j];   
			vNormal[1] = y[i]*c[j];   
			vNormal[2] = z[j]/inner;   
			//gltNormalizeVector(vNormal);   
			glNormal3fv(vNormal);   
			glVertex3f(x[i]*r[j], y[i]*r[j], z[j]);   

			glTexCoord2f((float)(i+1)/(float)(loops), (float)(j)/(float)(slices));   
			if(i+1 < slices)
			{
			vNormal[0] = x[i+1]*c[j];   
			vNormal[1] = y[i+1]*c[j];
			vNormal[2] = z[j]/inner;   
			glNormal3f(vNormal[0],vNormal[1],vNormal[2]);   
			glVertex3f(x[i+1]*r[j], y[i+1]*r[j], z[j]);   
			}
			else
			{
			vNormal[0] = x[0]*c[j];   
			vNormal[1] = y[0]*c[j];
			vNormal[2] = z[j]/inner;   
			glNormal3f(vNormal[0],vNormal[1],vNormal[2]);   
			glVertex3f(x[0]*r[j], y[0]*r[j], z[j]);   
			}
		}   
		glEnd();   
	}   


}

torus::~torus(void)
{
}
