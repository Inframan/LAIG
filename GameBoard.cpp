#include "GameBoard.h"


GameBoard::GameBoard(void)
{
	tab = new tabuleiro();
	pecas.resize(5);
	for(int i = 0; i < pecas.size();i++)
		pecas[i].resize(7);
	bool cor = 1;//começa com uma peça preta

	for(int i = 0; i < 7;i++)
	{

		for(int j = 0; j < 5;j++)	
		{	


			pilha * p = new pilha();
			if(!(i == 0  || i == 6 || j == 0 || j == 4 || (i == 3 && j == 2)))//não é uma das bordas
			{
				if(i == 3)//é na coluna do meio
				{
					if(j == 1)//azul
					{
						cor = 0;
					}
					else if(j == 3)//rosa
					{
						cor = 1;
					}
				}


				for(int k = 0; k < 3;k++)
				{
					Peca t(cor);
					t.setCoords(j,i);
					p->setCoords(j,i,1);
					p->setCor(cor);
					p->addPiece(t);
				}
				if(i != 3)
					cor = !cor;
			}
			else
				p->setCoords(j,i,0);
			pecas[j][i] = p;
		}
	}
}


string GameBoard::transformMatrixToPrologList(){
	string res = "boardgame([";

	for (unsigned int i = 0 ; i < pecas.size() ; i++)
	{
		res+="[";
		for(unsigned int j = 0; j < pecas[i].size() ; j++)
		{
			res+=pecas[i][j]->toString();
			if (j+1 != pecas[i].size())
				res+=",";
		}

		res+="]";
		if (i+1 != pecas.size())
			res+=",";
	}
	res += "]).\n";

	return res;
}

void GameBoard::sendBoard()
{ 
	socketConnect();

	char *boardToSend = new char[transformMatrixToPrologList().length() + 1];
	strcpy(boardToSend, transformMatrixToPrologList().c_str());
	envia(boardToSend, strlen(boardToSend));
	/*
	* TO DO
	* Enviar uma jogada aqui
	*/

	char ans[128];
	recebe(ans);
}
void GameBoard::draw(){
	tab->draw();

	

	glPushMatrix();
	glPushName(-1);
	
	for (int i = 0 ; i < pecas.size(); i++){
		

		for(int j = 0 ; j < pecas[i].size(); j++){
			pecas[i][j]->draw();
		}
	}

	glPopMatrix();


}


vector<vector <pilha *>> GameBoard::getPecas(){
	return pecas;
}

tabuleiro* GameBoard::getTab(){

	return tab;
}

GameBoard::~GameBoard(void)
{
}