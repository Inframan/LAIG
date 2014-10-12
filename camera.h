#pragma once
#include <string>
#include <vector>

using namespace std;
class camera 
{
	string id;
	float near,far;
	string type;
public:
	camera();
	camera(string id,float near, float far);
	string getID()const;
	float getNear()const;
	float getFar()const;
	void setType(string t);
	string getType()const;
	~camera(void);
};

