/*
* Traveling Salesman Problem Solver By Tomasz Grochowski.
*/


#pragma once
#include <vector>

/// <summary>
/// A container of functions creating a heighbourhood path for Traveling Salesman Problem
/// </summary>
class NeighbourHoodFinder
{
public:
	static std::vector<unsigned> neighbourhoodByInsert(std::vector<unsigned> path, int i, int j);
	static std::vector<unsigned> neighbourhoodByReverse(std::vector<unsigned> path, int i, int j);
	static std::vector<unsigned> neighbourhoodBySwap(std::vector<unsigned> path, int i, int j);
};

