/*
* Traveling Salesman Problem Solver By Tomasz Grochowski.
*/


#pragma once
#include "AlgorithmTSP.h"

/// <summary>
/// Class containing functionality to solve TSP with Branch and Bound method
/// </summary>
class BranchAndBound : private AlgorithmTSP
{
public:
	BranchAndBound(int, int**);
	void run(int&, std::vector<unsigned>&);

private:
	void executeAlgorithm(int*, int*, int, int, int&, int*, std::vector<unsigned>&);
	void findMin(const int, int*, bool = false);
	void reduceMatrix(const int, int*, int&, bool = false);
};

