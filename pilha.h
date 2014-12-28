#pragma once
#include "Peca.h"
#include <sstream>
#include <string>
class pilha :
	public primitive
{
	int x,y,z;
	vector<Peca> pecas;
	int size;
	int cor; //0-branca 1-preta vazio- -1
public:
	pilha(void);
	void draw();
	Peca removePiece();
	void addPiece(Peca peca);
	void setCor(int x);
	int getCor()const;
	void setCoords(int x, int y,int z);
	vector<int> getCoords()const;
	string toString();
	void emptyStack();
	~pilha(void);
};

