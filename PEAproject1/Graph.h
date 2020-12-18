/*
* Traveling Salesman Problem Solver By Tomasz Grochowski.
*/


#pragma once
#include <iostream>
#include <fstream>
#include <vector>

/// <summary>
/// A data container for TSP
/// </summary>
class Graph
{
public:
	~Graph();

	/// <summary>
	/// A random TSP data generator
	/// </summary>
	/// <param name="">Amount of cities</param>
	void generate(int);

	/// <summary>
	/// A method for reading data from .txt file
	/// </summary>
	void readFromFile();

	int getNodeAmount();
	int** getMatrix();

private:
	int nodeAmount;
	int** matrix;
};

