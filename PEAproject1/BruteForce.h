/*
* Traveling Salesman Problem Solver By Tomasz Grochowski.
*/

#pragma once
#include "AlgorithmTSP.h"

/// <summary>
/// Class containing functionality to solve TSP with Brute Force method
/// </summary>
class BruteForce : private AlgorithmTSP
{
public:
	BruteForce(int, int**);
	void run(int&, std::vector<unsigned>&);

private:
	void executeAlgorithm(int[], int, int, int, int&, std::vector<unsigned>&);
	bool findInArray(int*, int);
};

