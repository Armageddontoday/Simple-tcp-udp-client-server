#pragma once
#include <vector>
#include <algorithm>

class UIntVectorsHandler {
public:
	static void SortVector(std::vector<uint32_t> &vector) {
		std::sort(vector.begin(), vector.end());
	}
	
	static uint64_t GetVectorElementsSum(const std::vector<uint32_t> &vector) {
		if (vector.size() == 0) {
			return 0;
		}
		uint64_t sum_of_elems = 0;
		std::for_each(
			vector.begin(), vector.end(), [&](uint32_t currElem) {
				sum_of_elems += currElem;
			}
		);
		return sum_of_elems;
	}
};