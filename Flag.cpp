
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "Flag.h"

FlagShader::FlagShader(Texture * text)
{

	this->text = text;

	init("data/FlagShader.vert","data/FlagShader.frag");

	CGFshader::bind();

	

	// initialize in memory
	this->startTime = 0.0;
	this->delta = 0.0;
	this->wind = 0;

	textLoc = glGetUniformLocation(id(), "text");
	glUniform1i(textLoc, 0);

	windLoc = glGetUniformLocation(id(), "wind");
	glUniform1f(windLoc, wind);

	
	deltaLoc = glGetUniformLocation(id(), "delta");
	glUniform1f(deltaLoc,delta);

	// set the texture id for that sampler to match the GL_TEXTUREn that you 
	// will use later e.g. if using GL_TEXTURE0, set the uniform to 0
	CGFshader::unbind();
}



Flag::Flag(Texture * text): plane(30)
{
	
	this->fshader = new FlagShader(text);

}


void FlagShader::bind()
{
	CGFshader::bind();

	
	glUniform1f(windLoc, wind);
	glUniform1f(deltaLoc, delta);

	// make sure the correct texture unit is active
	glActiveTexture(GL_TEXTURE0);

	// apply/activate the texture you want, so that it is bound to GL_TEXTURE0
	//((CGFtexture*) text)->apply();
	text->apply();
}

void FlagShader::unbind()
{
	CGFshader::unbind();
}

void FlagShader::setTime(float t)
{

	
	if(this->startTime == 0)
	{
		this->startTime = t;
	}
	else
	{
		this->delta = t - startTime;
	}
}


void Flag::update(unsigned long t)
{
	float time_s = t * 0.001; // <-- seconds

	this->fshader->setTime(time_s);
}


void Flag::setWind(int wind){

	this->fshader->wind = wind;

}




Flag::~Flag(void)
{
}


void Flag::draw()
{
	fshader->bind();
		
	plane::draw();

	fshader->unbind();


}