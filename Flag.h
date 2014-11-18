#ifndef Flag_H
#define Flag_H




#include "CGFapplication.h"
#include "CGFshader.h"

#include "Plane.h"
#include "Appearence.h"
#include "texture.h"


class FlagShader : public CGFshader{

	friend class Flag;

	Texture *t;
	GLint baseImageLoc;
	GLint scaleLoc;

public:
	FlagShader(Appearence* app);

	virtual void bind();
	virtual void unbind();
	void setScale(float s);
	float normScale;



};


class Flag: public plane
{
	FlagShader *fshader;

public:

	Flag(Appearence* app);
	void draw();
	//void update(unsigned long refresh);
	// implementar o vento
	
	~Flag(void);


};



#endif