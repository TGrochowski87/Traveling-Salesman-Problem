/*
* Traveling Salesman Problem Solver By Tomasz Grochowski.
*/



#include "SimulatedAnnealing.h"

SimulatedAnnealing::SimulatedAnnealing(int nodeAmount, int** matrix, Callback neighbourhoodType) : AlgorithmTSP(nodeAmount, matrix)
{
    this->neighbourhoodType = neighbourhoodType;
}

void SimulatedAnnealing::run(int& finalCost, std::vector<unsigned>& finalPath)
{
    finalPath = algorithmGreedy();
    finalPath.push_back(0); //City 0 at the end
    double temperatureMax = 1;
    double temperature = temperatureMax;

    long maxit;
    if (this->nodeAmount < 10)
    {
        maxit = this->nodeAmount;
        for (int i = this->nodeAmount - 1; i > 0; i--)
        {
            maxit = maxit * i;
        }
    }
    else
    {
        maxit = 9;
        for (int i = 8; i > 1; i--)
        {
            maxit *= i;
        }
        maxit += (this->nodeAmount / 10) * pow(this->nodeAmount, 2) * log2(this->nodeAmount);
    }
    for (long i = 0; i < maxit; i++)
    {
        finalCost = newCalculation(finalPath);

        int first = rand() % (this->nodeAmount - 1) + 1;
        int second = rand() % (this->nodeAmount - 1) + 1;

        std::vector<unsigned> neighbourRoute = this->neighbourhoodType(finalPath, first, second);

        int neighbourCost = newCalculation(neighbourRoute);

        int energy = finalCost - neighbourCost;
        if (energy > 0)
        {
            finalPath = neighbourRoute;
        }
        else if (exp(energy / temperature) > (float)rand() / (float)RAND_MAX)
        {
            finalPath = neighbourRoute;
        }

        temperature *= 0.9999;
    }
}

std::vector<unsigned> SimulatedAnnealing::algorithmGreedy()
{
    std::vector<unsigned> initialPath;
    initialPath.push_back(0);

    int next;
    int cost;
    for (int i = 1; i < this->nodeAmount; i++)
    {
        next = 0;
        cost = INT_MAX;
        for (int j = 0; j < this->nodeAmount; j++)
        {
            if (find(initialPath.begin(), initialPath.end(), j) == initialPath.end())
            {
                if (this->matrix[initialPath.back()][j] < cost)
                {
                    next = j;
                    cost = this->matrix[initialPath.back()][j];
                }
            }
        }
        initialPath.push_back(next);
    }
    return initialPath;
}

int SimulatedAnnealing::newCalculation(std::vector<unsigned> path)
{
    int calculatedCost = 0;
    for (int i = 0; i < this->nodeAmount; i++)
    {
        calculatedCost += this->matrix[path.at(i)][path.at(i + 1)];
    }
    return calculatedCost;
}
