
#ifndef CommonItems_H
#define CommonItems_H
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>

// declarations for parseFile, customMessage, and makeLowerCase functions
int parseFile(std::vector<std::string> & vect, char * fileName);
int customMessage(char * programName, std::string usageMessage);
std::string makeLowerCase(std::string & s);

enum returnValues{
	invalidGameName = -5,
	sharedPointerException = -4,
	invalidDimension = -3,
	userQuitProgram = -2,
	unknownError = -1,
	success = 0,
	invalidArgs = 1,
	fileNotFound = 2,
	couldNotExtractDims = 3,
	noValidGamePieces = 4,
	incorrectVectorSize = 5,
	errorMakingGameBoard = 6,
	gameWasADraw = 7,
	gameQuitWithSaving = 8

};

enum argValues{
	programName = 0,
	gameName = 1,
	correctNumOfArgs = 2,
	dimensions = 2,
	lengthToWinGomoku = 3,
	maxNumOfArgs = 4

};

enum asciiValues{
	upperLowerDif = 32,
	upperBegin = 65,
	upperEnd = 90
};



#endif/* CommonItems_H*/