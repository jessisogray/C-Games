#include "stdafx.h"
#include "TicTacToeGame.h"


// main function for lab4
int main(int argc, char * argv[])
{
	// usage message for lab4
	std::string properInput = " <'TicTacToe', 'Sudoku' or 'Gomoku'>";

	try{
		GameBase::checkArguments(argc, argv);
		std::shared_ptr<GameBase> game = GameBase::instance();
		if (game == 0){
			return customMessage(argv[programName], properInput);
		}
		else{
			return game->play();

		}
	}
	catch (int exception){
		customMessage(argv[programName], properInput);
		return exception;
	}
	catch (...){
		customMessage(argv[programName], properInput);
		return unknownError;
	}

}

