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
public:
	linearAnimation(void);
	linearAnimation(std::string id,float span );
	void addPoint(float x,float y,float z);
	void update(unsigned long t);
	void calculateTotalDistance();
	~linearAnimation(void);
};

