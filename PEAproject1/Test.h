/*
* Traveling Salesman Problem Solver By Tomasz Grochowski.
*/


#pragma once
#include "Graph.h"
#include "BruteForce.h"
#include "BranchAndBound.h"
#include "DynamicProgramming.h"
#include "SimulatedAnnealing.h"
#include "TabuSearch.h"
#include "GeneticAlgorithm.h"
#include "Timer.h"

/// <summary>
/// A class for testing algorithms
/// </summary>
class Test
{
public:
	/// <summary>
	/// Test for data read from .txt file
	/// </summary>
	static void tspFromFile();

	/// <summary>
	/// Test for random generated data
	/// </summary>
	static void tspGenerated();

	/// <summary>
	/// Extention of tspGenerated method
	/// </summary>
	/// <param name=""></param>
	static void generateAndTest(int);

private:
	static int amount[7];
};

