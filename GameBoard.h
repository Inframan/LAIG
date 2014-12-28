#pragma once
#include "tabuleiro.h"
#include "pilha.h"
//#include "connectProlog.h"
#include <vector>
#include <string>

class GameBoard
{
	tabuleiro *tab;
	vector <vector <pilha *>> pecas;
public:
	GameBoard(void);
	string transformMatrixToPrologList();
	void sendBoard();
	~GameBoard(void);

};

