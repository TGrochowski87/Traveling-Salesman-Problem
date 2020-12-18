/*
* Traveling Salesman Problem Solver By Tomasz Grochowski.
*/



#pragma once
#include "AlgorithmTSP.h"
#include <iostream>


/// <summary>
/// Class containing functionality to solve TSP with Simulated Annealing method
/// </summary>
class SimulatedAnnealing : private AlgorithmTSP
{
public:
	using Callback = std::vector<unsigned>(*)(std::vector<unsigned>, int, int);

	/// <summary>
	/// A constructor extended by a neighbourhood generating method
	/// </summary>
	/// <param name=""></param>
	/// <param name=""></param>
	/// <param name="vector"></param>
	SimulatedAnnealing(int, int**, Callback);
	void run(int&, std::vector<unsigned>&);

private:
	std::vector<unsigned> algorithmGreedy();
	int newCalculation(std::vector<unsigned>);
	Callback neighbourhoodType;
};

