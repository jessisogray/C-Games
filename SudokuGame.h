
#ifndef SudokuGame_H
#define SudokuGame_H
#include "GameBase.h"

// useful enumerations
enum{
	sudokuMaxNumber = 9,
	sudokuMinNumber = 1
};

// class declaration for SudokuGame
class SudokuGame : public GameBase{
	friend std::ostream &operator<<(std::ostream & out, const SudokuGame& game);
public:
	SudokuGame();
	virtual void print();
	virtual bool done();
	virtual bool draw();
	virtual int turn();
	int prompt(unsigned int & x, unsigned int & y, unsigned int & num);
	int auto_player();
	bool checkColumns();
	bool checkRows();
	bool checkBoxes();
	bool allPiecesFilled();
	std::vector<int> possibleMoves();
	int canWinNextTurn(std::string letter);

private:
	wonValue winner;
	unsigned int lengthToWin;
};

// declaration for << operator
std::ostream &operator<<(std::ostream & out, const SudokuGame& game);

#endif/* SudokuGame_H*/