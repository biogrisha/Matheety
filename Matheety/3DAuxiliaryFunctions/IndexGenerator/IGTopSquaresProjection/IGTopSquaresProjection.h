#pragma once
#include <vector>


class IGTopSquaresProjection
{
public:
	static void GenerateIndices(std::vector<int>& indices,int xCount, int yCount);
};