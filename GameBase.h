

#ifndef GameBase_H
#define GameBase_H
#include "GamePieces.h"
#include <memory>

enum wonValue{
	noWinner = 0, //also used when game is in progress
	player1Won = 1,
	player2Won = -1

};



// declaration for the GameBase class
class GameBase{
public:
	virtual void print() = 0;
	virtual bool done() = 0;
	virtual bool draw() = 0;
	virtual int prompt(unsigned int & x, unsigned int & y);
	virtual bool promptSave();
	virtual int turn() = 0;
	int play();
	static void checkArguments(int argc, char *argv[]);
	static std::shared_ptr<GameBase> instance();
protected:
	GameBase(unsigned int w, unsigned int h, bool buffer);
	const unsigned int width;
	const unsigned int height;
	std::vector<gamePiece> board;
	unsigned int longestStringLength;
	//This boolean is true when X is up, false when O is up, and ignored when game over.
	bool player1Turn;
	bool hasBuffer;
	static std::shared_ptr<GameBase> sharedPointer;
	static std::string gameNameString;
};


#endif/* GameBase_H*/