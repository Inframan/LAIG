#pragma once
#include "tabuleiro.h"
#include "pilha.h"
#include "connectProlog.h"
#include <vector>
#include <string>
#include "Appearence.h"

class GameBoard
{
	tabuleiro *tab;
	vector <vector <pilha *>> pecas;
	Appearence *app;
	flagSelection* flag;
public:
	GameBoard(void);
	GameBoard(flagSelection* flag);
	string transformMatrixToPrologList();
	void sendBoard();
	vector<vector <pilha *>> getPecas();
	tabuleiro* getTab();
	~GameBoard(void);
	void draw();
	void draw(int x, int y);

};

