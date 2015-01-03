#include "pilha.h"


pilha::pilha(void)
{
	size = 0;
	cor = -1;
	y = z = x = 0;
}


Peca pilha:: removePiece()
{
	Peca ret = pecas[pecas.size()-1];
	pecas.pop_back();
	size--;
	if(size == 0)
		cor = -1;
	return ret;
}

int pilha::getCor()const
{
	return cor;
}

void pilha::setCor(int cor)
{
	this->cor = cor;
}
void pilha::draw()
{
	glPushMatrix();
	glTranslated(x+0.5,z,y+0.5);
	glLoadName(x);
	glPushMatrix();
	for(vector<Peca>::iterator it = pecas.begin();it != pecas.end();it++)
	{
		
		glPushName(y);
		it->draw();
		glPopName();
		glTranslated(0,0.1,0);
	}
	glPopMatrix();
	glPopMatrix();
}


void pilha:: addPiece(Peca peca)
{
	pecas.push_back(peca);
	size++;
}

void pilha::emptyStack()
{
	pecas.clear();
	size =0;
}

bool pilha::isEmpty() const
{
	return size == 0;
}

string pilha::toString(){

	stringstream ss;
	ss << size;
	string res = "[" + ss.str();
	if(cor== 0)
		res += ",b]";
	else if(cor ==1)
		res += ",p]";
	else
		res += ",v]";


	return res;
}



void pilha::setCoords(int x, int y,int z){
	this->x = x;
	this->y = y;
	this->z = z;
}

vector<int> pilha::getCoords() const
{
	vector<int> ret;
	ret.push_back(x);
	ret.push_back(y);	
	ret.push_back(z);
	return ret;
}


pilha::~pilha(void)
{
}
