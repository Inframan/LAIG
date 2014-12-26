#pragma once
#include "Peca.h"
class pilha :
	public primitive
{
	int x,y,z;
	vector<Peca> pecas;
public:
	pilha(void);
	void draw();
	Peca removePiece();
	void addPiece(Peca peca);
	void emptyStack();
	~pilha(void);
};

