
#ifndef GomokuGame_H
#define GomokuGame_H
#include "GameBase.h"

// declaration of the GomokuGame class
class GomokuGame : public GameBase{
	friend std::ostream &operator<<(std::ostream & out, const GomokuGame& game);
public:
	GomokuGame();
	virtual void print();
	virtual bool done();
	virtual bool draw();
	virtual int turn();
	int auto_player();
	bool checkColumns(bool includeEmptySpaces);
	bool checkRows(bool includeEmptySpaces);
	bool checkUpDiagonals(bool includeEmptySpaces);
	bool checkDownDiagonals(bool includeEmptySpaces);
	std::vector<int> possibleMoves();
	int canWinNextTurn(std::string letter);

private:
	wonValue winner;
	unsigned int lengthToWin;
};

// declaration of the << operator
std::ostream &operator<<(std::ostream & out, const GomokuGame& game);

#endif/* GomokuGame_H*/