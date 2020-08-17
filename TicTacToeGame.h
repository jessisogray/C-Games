#ifndef TicTacToeGame_H
#define TicTacToeGame_H
#include "GameBase.h"

// TicTacToeGame class declaration
class TicTacToeGame : public GameBase{
	friend std::ostream &operator<<(std::ostream & out, const TicTacToeGame& game);
public:
	TicTacToeGame();
	virtual void print();
	virtual bool done();
	virtual bool draw();
	virtual int turn();
	int auto_player();
	std::vector<int> possibleMoves();
	int canWinNextTurn(std::string letter);

private:
	wonValue winner;

};

// declaration of the << operator
std::ostream &operator<<(std::ostream & out, const TicTacToeGame& game);

#endif/* TicTacToeGame_H*/