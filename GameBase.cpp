
#include "stdafx.h"
#include "TicTacToeGame.h"
#include "GomokuGame.h"
#include "SudokuGame.h"

// initialize the sharedPointer
std::shared_ptr<GameBase> GameBase::sharedPointer = nullptr;
std::string GameBase::gameNameString = "";

// constructor for GameBase
GameBase::GameBase(unsigned int w, unsigned int h, bool buffer)
: width(w), height(h), board(w*h), player1Turn(true), hasBuffer(buffer)
{
}

// definition of the prompt method to ask the player for a move
int GameBase::prompt(unsigned int & x, unsigned int & y){

	std::string usageMessage = "Type a valid coordinate in the form X,X to make your move or type quit to quit";
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
		
		if (numCommas == 1){
			//when there are 2 numbers we read in and check if the move is valid depending on wether or not we're using a buffer
			if (std::istringstream(input) >> x >> y){
				int index = width * y + x;
				bool moveIsValid;
				if (hasBuffer){
					moveIsValid = x > 0 && y > 0 && x < (width - 1) && y < (height - 1) && board[index].name == "";

				}
				else{
					moveIsValid = x >= 0 && y >= 0 && x < width && y < height && board[index].name == "";

				}
				if (moveIsValid){
					validInput = true;
				}
			}
		}
		if (!validInput){
			usageMessage = "This input was not valid, please input a valid coordinate or enter quit";
			std::cout << usageMessage << std::endl;
		}
	}
	return success;
}

// definition for the promptSave method, which is called when the user enters 'quit'
bool GameBase::promptSave(){
	std::string usageMessage = "Do you want to save? Type <save> to save, or anything else to quit without saving";
	std::cout << usageMessage << std::endl;
	std::string input;
	if (std::cin >> input){
		if (input == "save"){
			return true;
		}
	}
	return false;

}


// definition of the play method
int GameBase::play(){
	//checks the game should still be played 
	while (!done() && !draw()){
		int turnReturnValue = turn();
		if (turnReturnValue == success){
			print();
			player1Turn = !player1Turn;
		}
		else{
			std::string message = "The game ended without finishing";
			std::cout << message << std::endl;
			return turnReturnValue;
		}

	}
	
	// if the sudoku game is done, print the appropriate message:
	// for Sudoku
	if (gameNameString == "Sudoku"){
		std::cout << "You solved the sudoku puzzle!" << std::endl;
	}
	// for a draw
	else if (draw()){
		std::cout << "It's a draw!" << std::endl;
		return gameWasADraw;
	}
	//if its Player 1's turn, then Player2 went last. So player2 won.
	else if (player1Turn){
		std::cout << "Player 2 Won!" << std::endl;
	}
	else{
		std::cout << "Player 1 Won!" << std::endl;
	}
	
	std::ofstream writeToFile;
	writeToFile.open(gameNameString);

	writeToFile << "NODATA" << std::endl;

	return success;

}

// definition of the checkArguments method to figure out which game to play and make sure the arguments are valid
void GameBase::checkArguments(int argc, char * argv[]){
	if (sharedPointer != nullptr){
		throw sharedPointerException;
	}
	else{
		GameBase * singularPointer = 0;
		if (argc >= correctNumOfArgs){
			//checks if we are playing TicTacToe, Gomoku, or Sudoku
			if (argc == correctNumOfArgs && strcmp(argv[gameName], "TicTacToe") == success){
				gameNameString = "TicTacToe";
				sharedPointer = (std::shared_ptr<GameBase>) new TicTacToeGame;
			}
			else if (argc == correctNumOfArgs && strcmp(argv[gameName], "Gomoku") == success){
				gameNameString = "Gomoku";
				sharedPointer = (std::shared_ptr<GameBase>) new GomokuGame();
			}
			else if (argc == correctNumOfArgs && strcmp(argv[gameName], "Sudoku") == success){
				gameNameString = "Sudoku";
				sharedPointer = (std::shared_ptr<GameBase>) new SudokuGame();
			}
			else{
				throw invalidGameName;
			}

		}
	}
}

// definition of the instance method, which returns a shared smart pointer to the game base class 
std::shared_ptr<GameBase> GameBase::instance(){
	if (sharedPointer != nullptr){
		return sharedPointer;
	}
	else{
		throw sharedPointerException;
	}
}
