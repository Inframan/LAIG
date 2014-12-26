#pragma once
#include "tabuleiro.h"
#include "pilha.h"
#include <vector>
class GameBoard
{
	tabuleiro *tab;
	vector <pilha *> pecas;
public:
	GameBoard(void);
	~GameBoard(void);
};

