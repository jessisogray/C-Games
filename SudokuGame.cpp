
#include "stdafx.h"
#include "SudokuGame.h"

// Constructor
SudokuGame::SudokuGame()
: winner(noWinner), GameBase(9, 9, false), lengthToWin(9)
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

// definition for << operator
std::ostream &operator<<(std::ostream & out, const SudokuGame& game){

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

// definition of done() method
bool SudokuGame::done(){
	
	//uses helper functions to iterate through to board and look for a win
	bool gameIsDone = allPiecesFilled() && checkColumns() && checkRows() && checkBoxes();


	return gameIsDone;
}

bool SudokuGame::draw(){

	return false;
}

// definition of allPiecesFilled() method
bool SudokuGame::allPiecesFilled(){
	bool allPiecesFilled = true;
	for (unsigned int i = 0; i < board.size(); i++){
		if (board[i].printDisplay == " "){
			allPiecesFilled = false;
			return allPiecesFilled;
		}
	}
	return allPiecesFilled;
}


// unique prompt method for Sudoku (unlike TicTacToe/Gomoku, user must enter a coord and a number 1 to 9)
int SudokuGame::prompt(unsigned int & x, unsigned int & y, unsigned int & num){
	//prompts the player for a move
	std::string usageMessage = "Type a valid coordinate and number in the form X,X,# to make your move or type quit to quit";
	std::cout << usageMessage << std::endl;
	bool validInput = false;
	std::string input;
	while (!validInput && std::cin >> input){
		if (input == "quit"){
			std::ofstream writeToFile;
			writeToFile.open(gameNameString);
			if (promptSave()){
				writeToFile << gameNameString << std::endl;
				if (player1Turn){
					writeToFile << 1 << std::endl;
				}
				else{
					writeToFile << 2 << std::endl;
				}
				for (unsigned int i = 0; i < board.size(); ++i){
					writeToFile << pieceColorToString(board[i].color) << std::endl << board[i].printDisplay << std::endl;

				}
				std::cout << "The game has been saved" << std::endl;
				return gameQuitWithSaving;
			}
			else{
				writeToFile << "NODATA" << std::endl;
				std::cout << "The game was not saved" << std::endl;
				return userQuitProgram;
			}
		}
		//checks for commas to make sure right numbers were given
		int numCommas = 0;
		for (unsigned int i = 0; i < input.size(); ++i){
			if (input[i] == ','){
				numCommas++;
				input[i] = ' ';
			}
		}
		if (numCommas == 2){
			//when there are 2 numbers we read in and check if the move is valid depending on wether or not we're using a buffer
			if (std::istringstream(input) >> x >> y >> num){
				int index = width * y + x;
				bool moveIsValid;
				if (hasBuffer){
					moveIsValid = x > 0 && y > 0 && x < (width - 1) && y < (height - 1);

				}
				else{
					moveIsValid = x >= 0 && y >= 0 && x < width && y < height;
				}
				if (moveIsValid && num >= sudokuMinNumber && num <= sudokuMaxNumber){
					validInput = true;
				}
			}
		}
		if (!validInput){
			usageMessage = "This input was not valid, please input a valid input or enter quit";
			std::cout << usageMessage << std::endl;
		}
	}
	return success;

}


// definition of the turn() method
int SudokuGame::turn(){
	unsigned int x;
	unsigned int y;
	unsigned int num;
	int promptReturnValue;
	//prompts the player for a move  and places a piece on the board
	promptReturnValue = prompt(x, y, num);
	if (promptReturnValue == success){
		int index = width * y + x;
		std::string pieceNumber = std::to_string(num) ;
		board[index] = gamePiece(black, pieceNumber, pieceNumber);
		
		if (board[index].printDisplay.length() > longestStringLength){
			longestStringLength = board[index].printDisplay.length();
		}
	}
	else{
		return promptReturnValue;
	}

	if (allPiecesFilled() && !done()){
		std::cout << "The board is full, but you haven't won yet!" << std::endl;
	}
	return success;
}



void SudokuGame::print(){
	std::cout << *this << std::endl;
}

// helper method to check to make sure the columns have unique numbers 1 to 9
bool SudokuGame::checkColumns(){
	bool nothingInColumnsRepeats = true;
	//iterates through each column to see if there is a win in a column
	for (unsigned int col = 0; col < width; ++col){
		for (unsigned int rowOfFirst = 0; rowOfFirst < height; ++rowOfFirst) {
			unsigned int indexOne = rowOfFirst * width + col;
			for (unsigned int rowOfSecond = rowOfFirst+1; rowOfSecond < height; ++rowOfSecond){
				unsigned int indexTwo = rowOfSecond * width + col;
				if (board[indexOne].printDisplay == board[indexTwo].printDisplay){
					nothingInColumnsRepeats = false;
					return nothingInColumnsRepeats;
				}
			}
			

		}
	}
	return nothingInColumnsRepeats;
}

// helper method to check to make sure the rows have unique numbers 1 to 9
bool SudokuGame::checkRows(){
	bool nothingInRowsRepeats = true;
	//iterates through each column to see if there is a win in a column
	for (unsigned int row = 0; row < height; ++row){
		for (unsigned int colOfFirst = 0; colOfFirst < width; ++colOfFirst) {
			unsigned int indexOne = row * width + colOfFirst;
			for (unsigned int colOfSecond = colOfFirst+1; colOfSecond < width; ++colOfSecond){
				unsigned int indexTwo = row * width + colOfSecond;
				if (board[indexOne].printDisplay == board[indexTwo].printDisplay){
					nothingInRowsRepeats = false;
					return nothingInRowsRepeats;
				}
			}


		}
	}
	return nothingInRowsRepeats;
}

// helper method to check to make sure the columns have unique numbers 1 to 9
bool SudokuGame::checkBoxes(){
	bool nothingInBoxRepeats = true;
	unsigned int i = 0;
	unsigned int counter = 0;
	while( counter < 9){
		std::vector<std::string> box(9);
		box[0] = board[i].printDisplay;
		box[1] = board[i+1].printDisplay;
		box[2] = board[i+2].printDisplay;
		box[3] = board[i + width].printDisplay;
		box[4] = board[i + width +1].printDisplay;
		box[5] = board[i + width +2].printDisplay;
		box[6] = board[i + 2*width].printDisplay;
		box[7] = board[i + 2*width+1].printDisplay;
		box[8] = board[i + 2*width+2].printDisplay;
		for (unsigned int j = 0; j < box.size(); ++j){
			for (unsigned int k = box.size() - 1; k > j; --k){
				if (box[j] == box[k]){
					nothingInBoxRepeats = false;
					return nothingInBoxRepeats;
				}
			}
		}
		if (counter % 3 == 2){
			i = i + 21;
		}
		else{
			i = i + 3;
		}
		++counter;
	}
	return nothingInBoxRepeats;

}
