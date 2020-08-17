
#include "stdafx.h"
#include "GomokuGame.h"

// constructor 
GomokuGame::GomokuGame()
: winner(noWinner), GameBase(19, 19, false), lengthToWin(5)
{
	//checks length of largest string so we can keep the board evenly space
	unsigned int charsToDisplayWidth = width / 10 + 1;
	if (charsToDisplayWidth > longestStringLength){
		longestStringLength = charsToDisplayWidth;
	}
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
std::ostream &operator<<(std::ostream & out, const GomokuGame& game){

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
bool GomokuGame::done(){
	bool includeEmpty = false;
	//uses helper functions to iterate through to board and look for a win
	bool gameIsDone = checkColumns(includeEmpty) || checkRows(includeEmpty) || checkUpDiagonals(includeEmpty) || checkDownDiagonals(includeEmpty);
	return gameIsDone;
}

// definition of the draw() method
bool GomokuGame::draw(){
	bool includeEmpty = true;
	//uses helper functions to iterate through to board and look for a possible victory left
	bool gameIsWinnable = checkColumns(includeEmpty) || checkRows(includeEmpty) || checkUpDiagonals(includeEmpty) || checkDownDiagonals(includeEmpty);
	return !gameIsWinnable;
}


// definition of the turn() method
int GomokuGame::turn(){
	unsigned int x;
	unsigned int y;
	int promptReturnValue;
	//prompts the player for a move  and places a piece on the board
	promptReturnValue = prompt(x, y);
	if (promptReturnValue == success){
		int index = width * y + x;

		if (player1Turn){
			board[index] = gamePiece(black, "B", "B");
		}
		else{
			board[index] = gamePiece(white, "W", "W");
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



void GomokuGame::print(){
	std::cout << *this << std::endl;
}

// helper function to check for a win in a column
bool GomokuGame::checkColumns(bool includeEmptySpaces){
	//iterates through each column to see if there is a win in a column
	for (unsigned int col = 0; col < width; ++col){
		for (unsigned int row = 0; row < height - lengthToWin + 1; ++row) {
			unsigned int index = row * width + col;
			unsigned int i = 1;
			if (includeEmptySpaces){
				pieceColor firstColor = board[index].color;
				//checks if the next space is the same color or blank (useful for the draw function)
				while ((index + i * width) < board.size() && (firstColor == board[index + i*width].color || board[index + i*width].color == noColor || firstColor == noColor)){
					if (firstColor == noColor){
						firstColor = board[index + i*width].color;
					}
					++i;
					//Don't need to check inside the loop if i > length to win because if there was, we would've ended the game last turn
				}

				if (i == lengthToWin)
				{
					return true;
				}
			}
			else{
				//if this square is empty check to see if it possible to win including that square as one of the five
				if (board[index].color != noColor){

					while ((index + i * width) < board.size() && board[index].color == board[index + i*width].color){
						++i;
					}
				}
				if (i == lengthToWin)
				{
					return true;
				}
			}

		}
	}
	return false;
}

// helper function to check for a win in the rows
bool GomokuGame::checkRows(bool includeEmptySpaces){
	// iterate horizontally looking for win
	for (unsigned int row = 0; row < height; ++row) {
		for (unsigned int col = 0; col < width - lengthToWin + 1; ++col){
			unsigned int index = row * width + col;
			unsigned int i = 1;
			if (includeEmptySpaces){
				//same as cols except moves horizontally, checks if the index is in bounds, then compares colors
				pieceColor firstColor = board[index].color;
				while ((index + i) < board.size() && (firstColor == board[index + i].color || board[index + i].color == noColor || firstColor == noColor)){
					if (firstColor == noColor){
						firstColor = board[index + i].color;
					}
					++i;
				}

				if (i == lengthToWin)
				{
					return true;
				}
			}
			else{
				if (board[index].color != noColor){

					while ((index + i) < board.size() && board[index].color == board[index + i].color){
						++i;
					}
				}
				if (i == lengthToWin)
				{
					return true;
				}
			}

		}
	}
	return false;
}

// helper function looking for a win in an up diagonal
bool GomokuGame::checkUpDiagonals(bool includeEmptySpaces){
	// iterate diagonally looking for wins
	for (unsigned int col = 0; col < width - lengthToWin + 1; ++col){
		for (unsigned int row = 0; row < height - lengthToWin + 1; ++row) {
			unsigned int index = row * width + col;
			unsigned int i = 1;
			if (includeEmptySpaces){
				pieceColor firstColor = board[index].color;
				//same as before except index is changed to find the diagonal sq. 
				while ((index + i * width + i) < board.size() && (firstColor == board[index + i*width + i].color || board[index + i*width + i].color == noColor || firstColor == noColor)){
					if (firstColor == noColor){
						firstColor = board[index + i*width + i].color;
					}
					++i;
				}

				if (i == lengthToWin)
				{
					return true;
				}

			}
			else{
				if (board[index].color != noColor){


					while ((index + i * width + i) < board.size() && board[index].color == board[index + i*width + i].color){
						++i;
					}
				}
				if (i == lengthToWin)
				{
					return true;
				}
			}

		}
	}
	return false;

}

// helper function looking for a win in a down diagonal
bool GomokuGame::checkDownDiagonals(bool includeEmptySpaces){
	//iterate from top left of the board diagonally to bottom right
	for (unsigned int col = 0; col < width - lengthToWin + 1; ++col){
		for (unsigned int row = height - 1; row >= lengthToWin - 1; --row) {
			unsigned int index = row * width + col;
			unsigned int i = 1;
			if (includeEmptySpaces){
				pieceColor firstColor = board[index].color;
				//same as before with out of bound adjs. and change in how we move through the vector
				while ((index - i * width + i) >= 0 && (firstColor == board[index - i*width + i].color || board[index - i*width + i].color == noColor || firstColor == noColor)){
					if (firstColor == noColor){
						firstColor = board[index - i*width + i].color;
					}
					++i;
				}

				if (i == lengthToWin)
				{
					return true;
				}
			}
			else{
				if (board[index].color != noColor){


					while ((index - i * width + i) >= 0 && board[index].color == board[index - i*width + i].color){
						++i;
					}
				}
				if (i == lengthToWin)
				{
					return true;
				}
			}

		}
	}
	return false;
}