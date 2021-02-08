/*
* Traveling Salesman Problem Solver By Tomasz Grochowski.
*/

#include "GeneticAlgorithm.h"

bool ValueCompare(const Individual& a, const Individual& b)
{
    return a.fitnessValue < b.fitnessValue;
}

GeneticAlgorithm::GeneticAlgorithm(int nodeAmount, int** matrix, int populationSize, int crossover, int mutation) : AlgorithmTSP(nodeAmount, matrix)
{
    this->populationSize = populationSize;
    this->crossover = crossover;
    this->mutation = mutation;
}

void GeneticAlgorithm::run(int& finalCost, std::vector<unsigned>& finalPath)
{
    std::vector<Individual> population = generatePopulation();

    int populationDrop = 0;

    for (int x = 0; x < 500; x++)
    {
        for (int i = 0; i < this->populationSize - populationDrop; i++)
        {
            if ((float)rand() / RAND_MAX < 0.70)
            {
                int parentIndex1;
                int parentIndex2;

                do
                {
                    parentIndex1 = rand() % (this->populationSize - populationDrop);
                    parentIndex2 = rand() % (this->populationSize - populationDrop);
                } while (parentIndex1 == parentIndex2);

                std::vector<unsigned> newChromosome;
                switch (this->crossover)
                {
                case 1:
                {
                    newChromosome = crossoverPMX(population.at(parentIndex1).chromosome, population.at(parentIndex2).chromosome);
                    population.push_back(Individual(newChromosome, newCalculation(newChromosome)));
                    newChromosome = crossoverPMX(population.at(parentIndex2).chromosome, population.at(parentIndex1).chromosome);
                    population.push_back(Individual(newChromosome, newCalculation(newChromosome)));
                    break;
                }
                case 2:
                {
                    newChromosome = crossoverOX(population.at(parentIndex1).chromosome, population.at(parentIndex2).chromosome);
                    population.push_back(Individual(newChromosome, newCalculation(newChromosome)));
                    newChromosome = crossoverOX(population.at(parentIndex2).chromosome, population.at(parentIndex1).chromosome);
                    population.push_back(Individual(newChromosome, newCalculation(newChromosome)));
                    break;
                }
                }
            }
        }

        for (int i = 0; i < this->populationSize - populationDrop; i++)
        {
            if ((float)rand() / RAND_MAX < 0.01)
            {
                switch (this->mutation)
                {
                case 1:
                {
                    int mutatedIndividualIndex = rand() % (this->populationSize - populationDrop);
                    population.at(mutatedIndividualIndex).chromosome = mutationInvert(population.at(mutatedIndividualIndex).chromosome);
                    population.at(mutatedIndividualIndex).fitnessValue = newCalculation(population.at(mutatedIndividualIndex).chromosome);
                    break;
                }
                case 2:
                {
                    int mutatedIndividualIndex = rand() % (this->populationSize - populationDrop);
                    population.at(mutatedIndividualIndex).chromosome = mutationScramble(population.at(mutatedIndividualIndex).chromosome);
                    population.at(mutatedIndividualIndex).fitnessValue = newCalculation(population.at(mutatedIndividualIndex).chromosome);
                    break;
                }
                }
            }
        }

        std::sort(population.begin(), population.end(), ValueCompare);

        if (populationDrop > this->populationSize - 30)
        {
            populationDrop += 2;
        }

        while (population.size() > this->populationSize - populationDrop)
        {
            population.pop_back();
        }

        finalPath = population.front().chromosome;
        finalCost = population.front().fitnessValue;
    }
}

std::vector<Individual> GeneticAlgorithm::generatePopulation()
{
    std::vector<Individual> population;

    for (int i = 0; i < this->populationSize; i++)
    {
        std::vector<unsigned> chromosome = randomizeChromosome();
        population.push_back(Individual(chromosome, newCalculation(chromosome)));
    }

    return population;
}

std::vector<unsigned> GeneticAlgorithm::randomizeChromosome()
{
    std::vector<unsigned> initialChromosome;
    initialChromosome.push_back(0);

    while (initialChromosome.size() < this->nodeAmount)
    {
        unsigned randomNode = rand() % (this->nodeAmount - 1) + 1;
        bool used = false;

        for (int j = 1; j < initialChromosome.size(); j++)
        {
            if (std::find(initialChromosome.begin() + 1, initialChromosome.end(), randomNode) != initialChromosome.end())
            {
                used = true;
            }
        }
        if (!used)
            initialChromosome.push_back(randomNode);
    }
    initialChromosome.push_back(0);

    return initialChromosome;
}

int GeneticAlgorithm::newCalculation(std::vector<unsigned> path)
{
    int calculatedCost = 0;
    for (int i = 0; i < this->nodeAmount; i++)
    {
        calculatedCost += this->matrix[path.at(i)][path.at(i + 1)];
    }
    return calculatedCost;
}

std::vector<unsigned> GeneticAlgorithm::mutationInvert(std::vector<unsigned> chromosome)
{
    int i = rand() % (this->nodeAmount - 1) + 1;
    int j = rand() % (this->nodeAmount - 1) + 1;

    std::vector<unsigned> mutatedChromosome = chromosome;
    if (i < j)
        std::reverse(mutatedChromosome.begin() + i, mutatedChromosome.begin() + j);
    else if (i > j)
        std::reverse(mutatedChromosome.begin() + j, mutatedChromosome.begin() + i);

    return mutatedChromosome;
}

std::vector<unsigned> GeneticAlgorithm::mutationScramble(std::vector<unsigned> chromosome)
{
    int amount = rand() % (this->nodeAmount - 1) + 1;

    std::vector<unsigned> mutatedChromosome = chromosome;
    std::vector<unsigned> randomizedGens;
    for (int i = 0; i < amount;)
    {
        int randomizedGen = rand() % (this->nodeAmount - 1) + 1;

        if (find(randomizedGens.begin(), randomizedGens.end(), randomizedGen) == randomizedGens.end())
        {
            randomizedGens.push_back(randomizedGen);
            i++;
        }
    }

    for (int i = 0; i < amount; i++)
    {
        int first = rand() % amount;
        int second = rand() % amount;
        std::swap(mutatedChromosome.at(randomizedGens.at(first)), mutatedChromosome.at(randomizedGens.at(second)));
    }

    return mutatedChromosome;
}

std::vector<unsigned> GeneticAlgorithm::crossoverPMX(std::vector<unsigned> parent1, std::vector<unsigned> parent2)
{
    int from = rand() % (this->nodeAmount - 3) + 1;
    int to = rand() % (this->nodeAmount - (from + 1)) + (from + 1);

    std::vector<unsigned> descendant(this->nodeAmount, 0);

    for (int i = from; i <= to; i++)
    {
        descendant.at(i) = parent1.at(i);
    }

    std::vector<std::pair<int, int>> pairs;
    for (int i = from; i <= to; i++)
    {
        if (find(descendant.begin(), descendant.end(), parent2.at(i)) == descendant.end())
        {
            pairs.push_back(std::pair<int, int>(parent2.at(i), parent1.at(i)));
        }
    }

    for (int i = 0; i < pairs.size(); i++)
    {
        for (int j = 0; j < parent2.size()-1; j++)
        {
            if (parent2.at(j) == pairs.at(i).second)
            {
                if (descendant.at(j) == 0)
                {
                    descendant.at(j) = pairs.at(i).first;
                    break;
                }
                else
                {
                    bool placed = false;
                    int toFind = descendant.at(j);
                    do
                    {
                        for (int k = 0; k < parent2.size() - 1; k++)
                        {
                            if (parent2.at(k) == toFind)
                            {
                                if (descendant.at(k) == 0)
                                {
                                    descendant.at(k) = pairs.at(i).first;
                                    placed = true;
                                    break;
                                }
                                else
                                {
                                    toFind = descendant.at(k);
                                }
                            }
                        }
                    } while (!placed);
                }
            }
        }
    }

    for (int i = 0; i < this->nodeAmount; i++)
    {
        if (descendant.at(i) == 0)
        {
            descendant.at(i) = parent2.at(i);
        }
    }
    descendant.push_back(0);

    return descendant;
}

std::vector<unsigned> GeneticAlgorithm::crossoverOX(std::vector<unsigned> parent1, std::vector<unsigned> parent2)
{
    int from = rand() % (this->nodeAmount - 3) + 1;
    int to = rand() % (this->nodeAmount - (from + 1)) + (from + 1);

    std::vector<unsigned> descendant(this->nodeAmount + 1, 0);

    for (int i = from; i <= to; i++)
    {
        descendant.at(i) = parent1.at(i);
    }

    std::vector<unsigned> toAdd(parent2.begin() + (to+1), parent2.end()-1);
    toAdd.insert(toAdd.end(), parent2.begin() + 1, parent2.begin() + (to+1));

    for (int i = to + 1; i < descendant.size() - 1;)
    {
        if (find(descendant.begin(), descendant.end(), toAdd.front()) == descendant.end())
        {
            descendant.at(i) = toAdd.front();
            toAdd.erase(toAdd.begin());
            i++;
        }
        else
        {
            toAdd.erase(toAdd.begin());
        }
    }
    for (int i = 1; i < from;)
    {
        if (find(descendant.begin(), descendant.end(), toAdd.front()) == descendant.end())
        {
            descendant.at(i) = toAdd.front();
            toAdd.erase(toAdd.begin());
            i++;
        }
        else
        {
            toAdd.erase(toAdd.begin());
        }
    }

    return descendant;
}