#pragma once
#include <string>
#include <vector>

class animation
{
	std::string id;
	float span;
	unsigned long startTime;
	bool finished;
public:
	animation(void);
	animation(std::string id,float span);
	std::string getId()const;
	virtual void update(unsigned long t) =0;
	void setStartTime(unsigned long t);
	unsigned long getStartTime()const;
	float getSpan()const;
	void setFinish(bool f);
	bool isFinished()const;
	~animation(void);
};

