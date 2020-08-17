
#include "stdafx.h"
#include "GamePieces.h"

// constructor 
gamePiece::gamePiece(pieceColor c, std::string n, std::string pd)
: color(c), name(n), printDisplay(pd)
{}

// other constructor
gamePiece::gamePiece()
: color(noColor), name(""), printDisplay(" ")
{}

// definition of pieceColorToString method 
std::string pieceColorToString(pieceColor color){
	if (color == red){
		return "red";
	}
	else if (color == white){
		return "white";
	}
	else if (color == black){
		return "black";
	}
	else if (color == noColor){
		return "noColor";
	}
	else{
		return "invalidColor";
	}
}

// definition of stringToPieceColor method
pieceColor stringToPieceColor(std::string color){
	if (color == "red"){
		return red;
	}
	else if (color == "white"){
		return white;
	}
	else if (color == "black"){
		return black;
	}
	else if (color == "noColor" || color == ""){
		return noColor;
	}
	else{
		return invalidColor;
	}
}
