/*
* Traveling Salesman Problem Solver By Tomasz Grochowski.
*/

#pragma once
#include "NeighbourHoodFinder.h"

/// <summary>
/// A base abstract class for all algorithms
/// </summary>
class AlgorithmTSP
{
public:
	/// <summary>
	/// Constructor providing algorithms with TSP data
	/// </summary>
	/// <param name=""></param>
	/// <param name=""></param>
	AlgorithmTSP(int, int**);

	/// <summary>
	/// A pure virtual method that starts the algorithm
	/// </summary>
	/// <param name=""></param>
	/// <param name=""></param>
	virtual void run(int&, std::vector<unsigned>&) = 0;

protected:
	/// <summary>
	/// Amount of cities in TSP
	/// </summary>
	int nodeAmount;

	/// <summary>
	/// A matrix of distances between cities in TSP
	/// </summary>
	int** matrix;
};

