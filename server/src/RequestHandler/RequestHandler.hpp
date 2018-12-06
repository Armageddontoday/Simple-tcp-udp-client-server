#pragma once
#include <vector>
#include <string>
#include "UIntVectorHandler.hpp"

class RequestHandler {
public:
	//this function takes all ints from string, sort them & creates an answer containing only numbers & their sum
	std::string GenerateReply(std::string request);
private:
	//extracts numbers from string to vector, ignores sign, e.g. "a2 bc10_, df 11, -20" -> { 2, 10, 11, 20 } 
	static std::vector<uint32_t> _GetUnsignedNumbersFromString(const std::string &sourceString);
	
	//check if current char is part of number
	static bool _IsDecimalChar(char c);
	
	//create strings of numbers from vector, numbers separated by specified character
	static std::string _GetStringOfNumbers(const std::vector<uint32_t> &sourceVector, char divider = ' ');

	UIntVectorsHandler vectorHandler;
};
