
#ifndef GamePieces_H
#define GamePieces_H
#include "CommonItems.h"


enum pieceColor{
	invalidColor, noColor, red, white, black
};

struct gamePiece{
	gamePiece();
	gamePiece(pieceColor color, std::string name, std::string printDisplay);
	pieceColor color;
	std::string name;
	std::string printDisplay;
};

std::string pieceColorToString(pieceColor color);
pieceColor stringToPieceColor(std::string color);

#endif/* GamePieces_H*/