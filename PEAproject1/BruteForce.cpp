/*
* Traveling Salesman Problem Solver By Tomasz Grochowski.
*/


#include "BruteForce.h"

BruteForce::BruteForce(int nodeAmount, int** matrix) : AlgorithmTSP(nodeAmount, matrix) {}

void BruteForce::executeAlgorithm(int visitedCities[], int visitedArrayLength, int currentCity, int currentCost, int& finalCost, std::vector<unsigned>& finalPath)
{
    if (currentCost > finalCost)
        return;

    if (visitedArrayLength == this->nodeAmount)
    {
        currentCost += this->matrix[currentCity][0];
        if (currentCost < finalCost)
        {
            finalPath.clear();
            finalCost = currentCost;
            for (int i = 0; i < this->nodeAmount; i++)
            {
                finalPath.push_back(visitedCities[i]);
            }
        }
    }

    for (int i = 0; i < this->nodeAmount; i++)
    {
        if (!findInArray(visitedCities, i))
        {
            int savedNum = visitedCities[visitedArrayLength];

            visitedCities[visitedArrayLength] = i;
            executeAlgorithm(visitedCities, visitedArrayLength + 1, i, (currentCost + this->matrix[currentCity][i]), finalCost, finalPath);
            visitedCities[visitedArrayLength] = savedNum;
        }
    }
    return;
}

void BruteForce::run(int& finalCost, std::vector<unsigned>& finalPath)
{
    int* visitedCities = new int[this->nodeAmount];
    for (int i = 0; i < this->nodeAmount; i++)
        visitedCities[i] = -1;

    visitedCities[0] = 0;

    executeAlgorithm(visitedCities, 1, 0, 0, finalCost, finalPath);

    delete[] visitedCities;
    return;
}

bool BruteForce::findInArray(int* array, int value)
{
    for (int i = 0; i < this->nodeAmount; i++)
    {
        if (array[i] == value)
            return true;
    }
    return false;
}
