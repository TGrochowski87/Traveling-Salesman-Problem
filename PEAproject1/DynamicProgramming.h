/*
* Traveling Salesman Problem Solver By Tomasz Grochowski.
*/


#pragma once
#include "AlgorithmTSP.h"

/// <summary>
/// Class containing functionality to solve TSP with Dynammic Programming method
/// </summary>
class DynamicProgramming : private AlgorithmTSP
{
public:
	DynamicProgramming(int, int**);
	void run(int&, std::vector<unsigned>&);

private:
	int executeAlgorithm(int**, int, int, int);
};

