#include "GameBoard.h"


GameBoard::GameBoard(void)
{
	tab = new tabuleiro();
	bool cor = 0;//começa com uma peça preta
	for(int i = 0; i < 7;i++)
	{

		vector <pilha*> temp;

		for(int j = 0; j < 5;j++)
		{	


			pilha * p = new pilha();
			if(!(i == 0  || i == 6 || j == 0 || j == 4))//não é uma das bordas
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
					else//não desenha
						continue;
				}


				for(int k = 0; k < 3;i++)
				{
					Peca t(cor);
					t.setCoords(i,j);
					p->addPiece(t);
				}

				if(i != 3)
					cor = !cor;
			}

			temp.push_back(p);
		}
		pecas.push_back(temp);
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

	}
	res += "])";

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

GameBoard::~GameBoard(void)
{
}
