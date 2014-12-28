#pragma once
#include "Peca.h"
#include <string>
class pilha :
	public primitive
{
	int x,y,z;
	vector<Peca> pecas;
	int size;
	unsigned int cor; //0-branca 1-preta else-vazio
public:
	pilha(void);
	void draw();
	Peca removePiece();
	void addPiece(Peca peca);

	string toString();
	void emptyStack();
	~pilha(void);
};

