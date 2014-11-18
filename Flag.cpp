
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "Flag.h"

FlagShader::FlagShader(Appearence *app)
{

	t = app->getTexture();

	init("FlagShader.vert","FlagShader.frag");

	CGFshader::bind();

	// Store Id for the uniform "normScale", new value will be stored on bind()
	scaleLoc = glGetUniformLocation(id(), "normScale");


	// get the uniform location for the sampler
	baseImageLoc = glGetUniformLocation(id(), "baseImage");

	// set the texture id for that sampler to match the GL_TEXTUREn that you 
	// will use later e.g. if using GL_TEXTURE0, set the uniform to 0
	
}



Flag::Flag(Appearence *app): plane(30)
{
	
	fshader = new FlagShader(app);

}


void FlagShader::bind()
{
	CGFshader::bind();



	// make sure the correct texture unit is active
	glActiveTexture(GL_TEXTURE0);

	// apply/activate the texture you want, so that it is bound to GL_TEXTURE0
	((CGFtexture*) t)->apply();

}

void FlagShader::unbind()
{
	CGFshader::unbind();
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