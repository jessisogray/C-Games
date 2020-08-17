#include "stdafx.h"
#include "TicTacToeGame.h"

// Constructor
TicTacToeGame::TicTacToeGame()
: winner(noWinner), GameBase(5, 5, true)
{
	std::ifstream inputFile(gameNameString);
	std::string gameNameRead;
	getline(inputFile, gameNameRead);
	if (gameNameRead == gameNameString){
		std::cout << "A Game is being loaded" << std::endl;
		std::string playerTurn;
		getline(inputFile, playerTurn);
		if (playerTurn == "1"){
			player1Turn = true;
		}
		else{
			player1Turn = false;
		}
		unsigned int i = 0;
		while (i < board.size()){

			std::string colorInFile;
			std::string displayInFile;
			getline(inputFile, colorInFile);
			getline(inputFile, displayInFile);
			if (colorInFile != "noColor"){
				board[i] = gamePiece(stringToPieceColor(colorInFile), displayInFile, displayInFile);
			}
			if (board[i].printDisplay.length() > longestStringLength){
				longestStringLength = board[i].printDisplay.length();
			}
			++i;
		}
		print();
	}
	else{
		std::cout << "A new game is being created" << std::endl;
	}
	
}


// definition of the << operator
std::ostream &operator<<(std::ostream & out, const TicTacToeGame& game){
	int printWidth = game.longestStringLength + 1;
	for (unsigned int y = game.height; y != -1; --y){
		if (y == 0){
			for (unsigned int x = 0; x < game.width; ++x){
				out << std::setw(printWidth) << x;
			}
		}
		else{
			out << std::setw(game.longestStringLength) << (y - 1);

			for (unsigned int x = 0; x < game.width; ++x){
				int index = game.width * (y - 1) + x;
				out << game.board[index].printDisplay << std::setw(printWidth);
			}
		}
		out << std::endl;
	}
	return out;
}

// definition of the done() method
bool TicTacToeGame::done(){
	int firstSpotOnBoard = 1;
	for (unsigned int x = firstSpotOnBoard; x < width - 1; ++x){
		int index = width * 1 + x;

		//These nextInChain ints are the indexes for spots that can be combined for a line with the main 
		//index spot. Initially, they are set to be the spots above the index. 
		int nextInChain1 = width * 2 + x;
		int nextInChain2 = width * 3 + x;
		if (board[index].name == "X" || board[index].name == "O"){
			if (board[index].name == board[nextInChain1].name && board[index].name == board[nextInChain2].name){
				if (board[index].name == "X"){
					winner = player1Won;
				}
				else{
					winner = player2Won;
				}
				return true;
			}
			else if (x == firstSpotOnBoard){
				//Check for diagonal pair starting from bottom left
				//The nextInChain+1 and +2 are used so that we look for diagonal pairs instead of just vertical
				if (board[index].name == board[nextInChain1 + 1].name && board[index].name == board[nextInChain2 + 2].name){
					if (board[index].name == "X"){
						winner = player1Won;
					}
					else{
						winner = player2Won;
					}
					return true;
				}

				//Check for horizontal line at each level
				while (index <= nextInChain2 && (board[index].name == "X" || board[index].name == "O")){
					//We use index+1, and index+2, because these are the spots on the same horizontal line
					if (board[index].name == board[index + 1].name && board[index].name == board[index + 2].name){
						if (board[index].name == "X"){
							winner = player1Won;
						}
						else{
							winner = player2Won;
						}
						return true;
					}
					//Increase the index by the width, which will let us check for horizontal pairs 
					// one line above
					index = index + width;
				}
			}
			else if (x == width - 2){
				//The nextInChain-1 and -2 are used so that we look for diagonal pairs instead of just vertical
				if (board[index].name == board[nextInChain1 - 1].name && board[index].name == board[nextInChain2 - 2].name){
					if (board[index].name == "X"){
						winner = player1Won;
					}
					else{
						winner = player2Won;
					}
					return true;
				}
			}
		}
	}
	winner = noWinner;
	return false;

}

// definition of the draw() method
bool TicTacToeGame::draw(){
	int firstSpotOnBoard = 1;
	for (unsigned int x = firstSpotOnBoard; x < width - 1; ++x){
		for (unsigned int y = firstSpotOnBoard; y < width - 1; ++y){
			int index = width * y + x;
			if (board[index].name != "X" && board[index].name != "O"){
				return false;
			}
		}
	}
	return true;
}








int TicTacToeGame::turn(){
	unsigned int x;
	unsigned int y;
	int promptReturnValue;
	promptReturnValue = prompt(x, y);
	if (promptReturnValue == success){
		int index = width * y + x;

		if (player1Turn){
			board[index] = gamePiece(black, "X", "X");
		}
		else{
			board[index] = gamePiece(white, "O", "O");
		}
		if (board[index].printDisplay.length() > longestStringLength){
			longestStringLength = board[index].printDisplay.length();
		}
	}
	else{
		return promptReturnValue;
	}

	return success;
}



void TicTacToeGame::print(){
	std::cout << *this << std::endl;
}