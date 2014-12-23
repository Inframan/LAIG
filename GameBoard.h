#pragma once
#include "tabuleiro.h"
#include "Peca.h"
#include <vector>
class GameBoard
{
	tabuleiro *tab;
	vector <Peca *> brancas;
	vector <Peca *> pretas;

public:
	GameBoard(void);
	~GameBoard(void);
};

