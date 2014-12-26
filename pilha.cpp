#include "pilha.h"


pilha::pilha(void)
{

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

pilha::~pilha(void)
{
}
