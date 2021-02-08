/*
* Traveling Salesman Problem Solver By Tomasz Grochowski.
*/

#pragma once
#include "AlgorithmTSP.h"
#include <iostream>
#include <algorithm>

struct Individual
{
	Individual(std::vector<unsigned> chromosome, int fitnessValue)
	{
		this->chromosome = chromosome;
		this->fitnessValue = fitnessValue;
	}

	std::vector<unsigned> chromosome;
	int fitnessValue{ 0 };
};

/// <summary>
/// Class containing functionality to solve TSP with Genetic Algorithm
/// </summary>
class GeneticAlgorithm : private AlgorithmTSP
{
public:
	/// <summary>
	/// A constructor extended by population size and choices of mutation and crossover
	/// </summary>
	/// <param name=""></param>
	/// <param name=""></param>
	GeneticAlgorithm(int, int**, int, int, int);
	void run(int&, std::vector<unsigned>&);

private:
	std::vector<Individual> generatePopulation();
	std::vector<unsigned> randomizeChromosome();
	int newCalculation(std::vector<unsigned>);
	std::vector<unsigned> mutationInvert(std::vector<unsigned> chromosome);
	std::vector<unsigned> mutationScramble(std::vector<unsigned> chromosome);
	std::vector<unsigned> crossoverPMX(std::vector<unsigned> parent1, std::vector<unsigned> parent2);
	std::vector<unsigned> crossoverOX(std::vector<unsigned> parent1, std::vector<unsigned> parent2);

	int populationSize;
	int crossover;
	int mutation;
};

