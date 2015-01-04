#pragma once
#include "tabuleiro.h"
#include "pilha.h"
#include "connectProlog.h"
#include <vector>
#include <string>
#include "Appearence.h"
#include "circularAnimation.h"

class GameBoard
{
	tabuleiro *tab;
	Appearence *app;
	flagSelection* flag;
	vector <vector <pilha *>> pecas;
	circularAnimation * ani;
	bool reposition;
	void createPieces();
public:
	GameBoard(void);
	GameBoard(string prologList);
	GameBoard(flagSelection * flag);

	//vector <vector <pilha *>> transformPrologListToMatrix(string prologList);
	string transformMatrixToPrologList();
	void sendBoard();
	vector<vector <pilha *>> getPecas();
	tabuleiro* getTab();
	~GameBoard(void);
	void draw();
	void draw(int x, int y);
	void move(int prevX,int prevY,int newX,int newY);
	void merge(int prevX,int prevY,int newX,int newY);
	void exit(int prevX,int prevY,int newX,int newY);
	void update(unsigned long millis);
	void setAnimation();
};

