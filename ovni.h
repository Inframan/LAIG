#pragma once
#include "patch.h"
#include "cylinder.h"
#include "Flag.h"


class ovni :
	public primitive
{
	patch *cockpit;
	cylinder * upperDisk,*lowerDisk,*pole;
	Flag *flag;

public:
	ovni(void);
	void draw();	
	void update(unsigned long millis);
	void setWind(int wind);
	~ovni(void);
};

