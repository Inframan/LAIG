#include "GameBoard.h"


GameBoard::GameBoard(void)
{
	tab = new tabuleiro();
	bool cor = 0;//come�a com uma pe�a preta
	for(int i = 0; i < 7;i++)
	{
		for(int j = 0; j < 5;j++)
		{
			pilha * p = new pilha();
			if(!(i == 0  || i == 6 || j == 0 || j == 4))//n�o � uma das bordas
			{
				if(i == 3)//� na coluna do meio
				{
					if(j == 1)//azul
					{
						cor = 0;
					}
					else if(j == 3)//rosa
					{
						cor = 1;
					}
					else//n�o desenha
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
			pecas.push_back(p);
		}
	}
}




GameBoard::~GameBoard(void)
{
}
