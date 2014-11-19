#pragma once
#include "animation.h"
class circularAnimation :
	public animation
{
	float cx,cy,cz,rotAng,radius;
	float x,z;
	float speed,angle;
	bool firstTime;
	unsigned long previousTime;
public:
	circularAnimation(void);
	circularAnimation(std::string id,float span,float cx,float cy,float cz,float rotAng,float startAng,float radius);
	circularAnimation(std::string id,float span,float cx,float cy,float cz,float rotAng,float startAng,float radius,bool loop);
	void update(unsigned long millis);
	void transform();
	~circularAnimation(void);
};

