#include "pilha.h"


pilha::pilha(void)
{
	size = 0;
	cor = -1;

}

Peca pilha:: removePiece()
{
	Peca ret = pecas[pecas.size()-1];
	pecas.pop_back();

	return ret;
}

void pilha::draw()
{
	glPushMatrix;
	for(vector<Peca>::iterator it = pecas.begin();it != pecas.end();it++)
	{
		it->draw();
		glTranslated(0,1,0);
	}
	glPopMatrix;
}


void pilha:: addPiece(Peca peca)
{
	pecas.push_back(peca);
}

void pilha::emptyStack()
{
	pecas.clear();
}


string pilha::toString(){

	string res = "[" + size;
	if(cor== 0)
		res += ",b]";
	else if(cor ==1)
		res += ",p]";
	else
		res += ",v]";


	return res;
}
pilha::~pilha(void)
{
}
