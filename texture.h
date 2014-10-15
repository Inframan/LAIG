#pragma once
#include <string>
using namespace std;
class Texture
{
	string id;
	string file;
	float texlength_S;
	float texlength_T;



public:
	Texture(void);
	Texture(string id, string file, float texlength_S, float texlength_T);
	string getID();
	string getFile();
	float getTexLengthS();
	float getTexLengthT();
	void setID(string id);
	void setFile(string file);
	void setTexLengthS(float texlength_S);
	void setTexLengthT(float texlength_T);
	~Texture(void);
};

