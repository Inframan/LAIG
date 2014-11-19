#pragma once
#include "animation.h"
class linearAnimation :
	public animation
{
	std::vector<std::vector<float>> controlPoints;
	int current_point;
	bool firstTime;
	unsigned long previousTime;
	float totalDistance;
	float speed;
	float dx,dy,dz;//increments
	float x,y,z;//current position
	float angle;
public:
	linearAnimation(void);
	linearAnimation(std::string id,float span );
	void addPoint(float x,float y,float z);
	void update(unsigned long t);
	void calculateTotalDistance();
	void changeControlPoint();
	bool checkControlPoint();
	void transform();
	~linearAnimation(void);
};

