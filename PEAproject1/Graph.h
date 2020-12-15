#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <time.h>
#include <map>

using namespace std;

struct priorityCompare
{
	bool operator()(const vector<unsigned>& first, const vector<unsigned>& second) const
	{
		return first.at(0) > second.at(0);
	}
};

class Graph
{
public:
	~Graph();

	void generate(int);
	void readFromFile();
	void bruteForce(int&, vector<unsigned>&);
	void BBAlgorithm(int& , vector<unsigned>&);
	void BBAlgorithm2(int&, vector<unsigned>&);
	void DPalgorithm(int&, vector<unsigned>&);
	void SimulatedAnnealing(int&, vector<unsigned>&, int);
	void tabuSearch(int&, vector<unsigned>&);
	vector<unsigned> hybridAlgorithm();
	vector<unsigned> greedyAlgorithm();

private:
	vector<unsigned> insert(vector<unsigned> path, int i, int j);
	int newCalculation(vector<unsigned>);
	void findMin(const int, int*, bool = false);
	void reduceMatrix(const int, int*, int&, bool = false);
	int DPalgorithm(int** maskMatrix, int allVisitedMask, int mask, int currentCity);
	void BBAlgorithm(int* indexesX, int* indexesY, int cityArrayLength, int currentCost, int& finalCost, int* path, vector<unsigned>&);
	void bruteForce(int visitedCities[], int visitedArrayLength, int currentCity, int currentCost, int&, vector<unsigned>&);
	bool findInArray(int* array, int value);

	int nodeAmount;
	int** matrix;
};

