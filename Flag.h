#ifndef Flag_H
#define Flag_H




#include "CGFapplication.h"
#include "CGFshader.h"

#include "Plane.h"
#include "Appearence.h"
#include "texture.h"


class FlagShader : public CGFshader{

	friend class Flag;

	Texture * text;
	int textLoc;

	int wind;
	int windLoc;

	float delta;
	int deltaLoc;

	float startTime;

public:
	FlagShader(Appearence* app);

	virtual void bind();
	virtual void unbind();
	void setScale(float s);
	void setTime(float t);
	float normScale;



};


class Flag: public plane
{
	FlagShader *fshader;

public:

	Flag(Appearence* app);
	void draw();
	void update(unsigned long t);
	void setWind(int wind);
	
	~Flag(void);


};



#endif