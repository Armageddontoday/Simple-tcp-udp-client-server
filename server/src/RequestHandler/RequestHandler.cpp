#pragma once
#include "RequestHandler.hpp"
#include <sstream>

std::string RequestHandler::GenerateReply(std::string request) {
	std::vector<uint32_t> numbersFromString = _GetUnsignedNumbersFromString(request);
	uint64_t numbersSumm = vectorHandler.GetVectorElementsSum(numbersFromString);

	vectorHandler.SortVector(numbersFromString);
	
	std::stringstream reply;
	reply
		<< _GetStringOfNumbers(numbersFromString)
		<< '\n'
		<< numbersSumm
	;
	return reply.str();
}

std::vector<uint32_t> RequestHandler::_GetUnsignedNumbersFromString(const std::string &sourceString) {
	//result vector
	std::vector<uint32_t> numbersFromString;
	
	//temp string for numbers, e.g. string "num 10" -> string "10"
	std::string txtNumberRecord = "";

	//temp uint variable for final number conversion "10" -> 10
	uint32_t foundNumber;

	for (unsigned int i = 0; i < sourceString.length(); i++) {
		if (_IsDecimalChar(sourceString.at(i))) {
			txtNumberRecord += sourceString.at(i);
			//for case when number is last in string e.g. "test string 1"
			if (i + 1 != sourceString.length()) {
				continue;
			}
		}

		if (
			!txtNumberRecord.empty() &&
			std::stringstream(txtNumberRecord) >> foundNumber
		) {
			numbersFromString.push_back(foundNumber);
			txtNumberRecord.clear();
		}
	}
	return numbersFromString;
}

bool RequestHandler::_IsDecimalChar(char c) {
	static std::string numbers = "0123456789";
	return numbers.find(c) != std::string::npos;
}

std::string RequestHandler::_GetStringOfNumbers(const std::vector<uint32_t> &sourceVector, char divider) {
	if (sourceVector.size() == 0) {
		return "";
	}

	std::stringstream resultAccumulator;
	std::for_each(
		sourceVector.begin(), sourceVector.end(), [&](int currElem) {
			resultAccumulator << currElem << divider;
		}
	);

	std::string result = resultAccumulator.str();
	//erase unnescessary last divider, e. g. "1 2 3 " -> "1 2 3"
	result.erase(result.length() - 1);
	return result;
}