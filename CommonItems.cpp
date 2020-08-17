
#include "stdafx.h"
#include "CommonItems.h"

// definition of customMessage function
int customMessage(char * progName, std::string usageMessage){
	std::cout << "Sorry, the input you used is not valid. Please make your input in this form:" << std::endl;
	std::string message = progName + usageMessage;
	std::cout << message << std::endl;
	return invalidArgs;
}

// definition of parseFile function
int parseFile(std::vector<std::string> & vect, char * fileName){
	std::ifstream ifs;
	ifs.open(fileName);
	if (ifs.is_open()){
		std::string stringFromFile;
		while (ifs >> stringFromFile){
			vect.push_back(stringFromFile);
		}
		return success;
	}
	else{
		std::string fileNotFoundMessage = "Sorry, could not find the requested file.";
		std::cout << fileNotFoundMessage << std::endl;
		return fileNotFound;
	}
}

// definition of makeLowerCase function
std::string makeLowerCase(std::string & s){
	for (size_t i = 0; i < s.length(); ++i){
		if (s[i] <= upperEnd && s[i] >= upperBegin){
			s[i] += upperLowerDif;
		}
	}
	return s;
}