/*
* Traveling Salesman Problem Solver By Tomasz Grochowski.
*/


#include "TabuSearch.h"

TabuSearch::TabuSearch(int nodeAmount, int** matrix, Callback neighbourhoodType) : AlgorithmTSP(nodeAmount, matrix)
{
	this->neighbourhoodType = neighbourhoodType;
}

void TabuSearch::run(int& finalCost, std::vector<unsigned>& finalPath)
{
    finalPath = algorithmGreedy();
    finalPath.push_back(0); //City 0 at the end
    finalCost = newCalculation(finalPath);

    std::vector<unsigned> optimalPath = finalPath;
    int optimalCost = finalCost;

    int** tabu = new int* [this->nodeAmount - 2];
    for (int i = 0; i < this->nodeAmount - 2; i++)
    {
        tabu[i] = new int[this->nodeAmount - 2];
    }
    for (int i = 0; i < this->nodeAmount - 2; i++)
    {
        for (int j = 0; j < this->nodeAmount - 2; j++)
        {
            tabu[i][j] = 0;
        }
    }

    int criticalRepetition = 100;

    for (int x = 0; x < 3000; x++)
    {
        for (int i = 0; i < this->nodeAmount - 2; i++)
        {
            for (int j = 0 + i; j < this->nodeAmount - 2; j++)
            {
                if (tabu[i][j] > 0)
                    tabu[i][j]--;
            }
        }

        int newCost = INT32_MAX;
        int bestI = 0;
        int bestJ = 0;
        for (int i = 1; i < this->nodeAmount - 1; i++)
        {
            for (int j = 1 + i; j < this->nodeAmount; j++)
            {
                std::vector<unsigned> neighbourRoute = this->neighbourhoodType(optimalPath, i, j);

                int currentCost = newCalculation(neighbourRoute);

                if (tabu[i - 1][j - 2] > 0 && currentCost >= finalCost)
                    continue;

                if (currentCost < newCost)
                {
                    newCost = currentCost;
                    bestI = i;
                    bestJ = j;
                }
            }
        }

        if (bestI == 0 || bestJ == 0)
        {
            continue;
        }

        //Diversification
        if (newCost == optimalCost)
        {
            criticalRepetition--;
            if (criticalRepetition == 0)
            {
                optimalPath = algorithmHybrid();
                continue;
            }
        }
        else
        {
            criticalRepetition = 100;
        }

        optimalPath = this->neighbourhoodType(optimalPath, bestI, bestJ);
        optimalCost = newCost;

        if (optimalCost < finalCost)
        {
            finalPath = optimalPath;
            finalCost = optimalCost;
        }

        tabu[bestI - 1][bestJ - 2] = 3;
    }
}

int TabuSearch::newCalculation(std::vector<unsigned> path) //Currently includes cost of going back to city 0
{
    int calculatedCost = 0;
    for (int i = 0; i < this->nodeAmount; i++)
    {
        calculatedCost += this->matrix[path.at(i)][path.at(i + 1)];
    }
    return calculatedCost;
}

std::vector<unsigned> TabuSearch::algorithmHybrid()
{
    std::vector<unsigned> initialPath;
    initialPath.push_back(0);

    int randomizeAmount = rand() % (this->nodeAmount - 1) + 1;

    while (initialPath.size() - 1 < randomizeAmount)
    {
        unsigned randomNode = rand() % randomizeAmount + 1;
        bool used = false;

        for (int j = 1; j < initialPath.size(); j++)
        {
            if (std::find(initialPath.begin() + 1, initialPath.end(), randomNode) != initialPath.end())
            {
                used = true;
            }
        }
        if (!used)
            initialPath.push_back(randomNode);
    }

    int next;
    int cost;
    for (int i = 1; i < this->nodeAmount - randomizeAmount; i++)
    {
        next = 0;
        cost = INT_MAX;
        for (int j = 0; j < this->nodeAmount; j++)
        {
            if (std::find(initialPath.begin(), initialPath.end(), j) == initialPath.end())
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
    initialPath.push_back(0);

    return initialPath;
}

std::vector<unsigned> TabuSearch::algorithmGreedy()
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
            if (std::find(initialPath.begin(), initialPath.end(), j) == initialPath.end())
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
