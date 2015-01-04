#include "GameBoard.h"


GameBoard::GameBoard(void)
{
	
	player1pieces = 21;
	player2pieces = 21;
	ani = NULL;
	tab = new tabuleiro();
	createPieces();
	reposition=false;
	initialState=pecas;
}

GameBoard::GameBoard(flagSelection * flag)
{
	player1pieces = 21;
	player2pieces = 21;
	ani = NULL;
	this->flag = flag;
	tab = new tabuleiro();
	createPieces();
	
	initialState=pecas;
	reposition=false;
}


void GameBoard::createPieces()
{
	ani = NULL;
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
					p->setCoords(j,i,1);
					p->setCor(cor);
					p->addPiece(t);
				}
				if(i != 3)
					cor = !cor;
			}
			else if(j ==2 && i==3)
				p->setCoords(j,i,1);
			else
				p->setCoords(j,i,0);
			pecas[j][i] = p;
		}
	}

}

GameBoard::GameBoard(string prologList)
{
	player1pieces = 21;
	player2pieces = 21;
	reposition=false;
	ani=NULL;
	this->flag=flag;
	tab = new tabuleiro();
	pecas.resize(5);
	for(int i = 0; i < pecas.size();i++)
		pecas[i].resize(7);

	initialState=pecas;
}

void GameBoard::addPlay(int playType,int prevX,int prevY,int newX, int newY,int size,int cor)
{
	vector<int> play;
	vector<int> reversePlay;

	if(playType == 2)
	{
		int tempx, tempy;
		tempx = newX; tempy = newY;
		newX = prevX; newY = prevY;
		prevX = tempx;prevY = tempy;
	}


	play.push_back(playType);
	play.push_back(prevX);
	play.push_back(prevY);
	play.push_back(newX);
	play.push_back(newY);
	play.push_back(size);

	reversePlay.push_back(playType);	
	reversePlay.push_back(newX);
	reversePlay.push_back(newY);
	reversePlay.push_back(prevX);
	reversePlay.push_back(prevY);
	reversePlay.push_back(size);
	reversePlay.push_back(cor);
	plays.push_back(play);
	reversePlays.push_back(reversePlay);
}

void GameBoard::undo()
{
	plays.pop_back();
	vector<int> reverse = reversePlays[reversePlays.size()-1];
	reversePlays.pop_back();
	int type = reverse[0];
	switch (type)
	{
	case 0:
		move(reverse[1],reverse[2],reverse[3],reverse[4]);
		break;
	case 1:
		exit(reverse[1],reverse[2],reverse[3],reverse[4]);
		if(reverse[6])
			player1pieces++;
		else
			player2pieces++;
		break;
	case 2:
		for(int i = 0; i < reverse[5];i++)
			exit(reverse[1],reverse[2],reverse[3],reverse[4]);
		break;
	default:
		break;
	}
}


string GameBoard::transformMatrixToPrologList(){
	string res = "[";

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
	res += "]";

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

void GameBoard::draw(int x, int y){

	bool selected=true;

	
	glPushMatrix();
	if(ani)
		ani->transform();

	
	flag->draw(x,y);
	glPushMatrix();
	glPushName(-1);
	
	tab->draw();

	for (int i = 0 ; i < pecas.size(); i++){
		
		for(int j = 0 ; j < pecas[i].size(); j++){
					pecas[i][j]->draw();
		}
	}

	
	glPopMatrix();
	
	glPopMatrix();

}

void GameBoard::draw(){
	

	glPushMatrix();
	if(ani)
		ani->transform();

	glPushMatrix();
	glPushName(-1);
	
	tab->draw();

	for (int i = 0 ; i < pecas.size(); i++){
		for(int j = 0 ; j < pecas[i].size(); j++){
			pecas[i][j]->draw();
		}
	}
	glPopMatrix();

	glPopMatrix();

}


vector<vector <pilha *>> GameBoard::getPecas(){
	return pecas;
}

tabuleiro* GameBoard::getTab(){

	return tab;
}

void GameBoard::move(int prevX,int prevY,int newX,int newY)
{
	int cor = (*pecas[prevX][prevY]).getCor();
	while(!pecas[prevX][prevY]->isEmpty())
	{
		Peca p = pecas[prevX][prevY]->removePiece();
		int x = prevX - newX;
		int y = prevY - newY;
		p.setMoveAnimation(x,0,y);
		pecas[newX][newY]->addPiece(p);
	}
	pecas[newX][newY]->setCor(cor);
	pecas[prevX][prevY]->setCor(-1);
}

void GameBoard::merge(int prevX,int prevY,int newX,int newY)
{
	Peca p;
	while(!pecas[newX][newY]->isEmpty())
	{
		p = pecas[newX][newY]->removePiece();
		int x = newX - prevX;
		int y = newY - prevY;
		p.setMergeAnimation(x,0,y);
		pecas[prevX][prevY]->addPiece(p);
	}
}

void GameBoard::exit(int prevX,int prevY,int newX,int newY)
{
	bool cor = pecas[prevX][prevY]->getCor();
	Peca p = pecas[prevX][prevY]->removePiece();	
	int x = prevX - newX;
	int y = prevY - newY;
	p.setExitAnimation(x,1,y);
	pecas[newX][newY]->addPiece(p);
	pecas[newX][newY]->setCor(cor);
}


void GameBoard::update(unsigned long millis)
{
	if(ani)
		ani->update(millis);
	for(int i = 0; i < pecas.size(); i++)
		for(int j = 0; j < pecas[i].size();j++)
			pecas[i][j]->update(millis);
}

void GameBoard::setAnimation()
{
	if(reposition){
	ani = new circularAnimation("this ani",2,2.5,0,3.5,180,180,0);
	reposition=false;
	}
	else{
	ani = new circularAnimation("this ani",2,2.5,0,3.5,180,0,0);
	reposition=true;
	}
}

GameBoard::~GameBoard(void)
{
}