#pragma once

#include "Flag.h"
#include "cylinder.h"
class flagSelection
{
	Flag *flag;
	cylinder *pole;
public:
	flagSelection(CGFtexture *t);
	void setWind(int wind);
	void draw();
	void draw(int x, int y);
	void update(unsigned long millis);
	~flagSelection(void);
};

