/*
* Traveling Salesman Problem Solver By Tomasz Grochowski.
*/


#include "Graph.h"

Graph::~Graph()
{
	for (int i = 0; i < this->nodeAmount; i++)
	{
		delete[] this->matrix[i];
	}

	delete[] this->matrix;
}

void Graph::generate(int amount)
{
    this->nodeAmount = amount;

    this->matrix = new int* [this->nodeAmount];
    for (int i = 0; i < this->nodeAmount; i++)
    {
        this->matrix[i] = new int[this->nodeAmount];
    }

    for (int j = 0; j < this->nodeAmount; j++)
    {
        for (int i = 0; i < this->nodeAmount; i++)
        {
            if(i == j)
                this->matrix[j][i] = 0;
            else
                this->matrix[j][i] = rand() & 99 + 1;
        }
    }
}

void Graph::readFromFile()
{
	int justReadValue;

	std::cout << "Name of file to read from: " << std::flush;
	std::string fileName;
	std::cin >> fileName;

	std::ifstream file(fileName);
	if(file.is_open())
	{
		file >> this->nodeAmount;
		if (file.fail())
		{
			std::cout << "ERROR - Could not read cities' quantity!" << std::endl;
			return;
		}
		else
		{
			this->matrix = new int* [this->nodeAmount];

			for (int i = 0; i < this->nodeAmount; i++)
			{
				this->matrix[i] = new int[this->nodeAmount];
			}

			for (int j = 0; j < this->nodeAmount; j++)
			{
				for (int i = 0; i < this->nodeAmount; i++)
				{
					file >> justReadValue;
					if (file.fail())
					{
						std::cout << "ERROR - Could not read matrix values!" << std::endl;
						return;
					}
					else
					{
						this->matrix[j][i] = justReadValue;
					}
				}
			}
			file.close();
		}
	}
	else
	{
		std::cout << "ERROR - Could not open file of given name!" << std::endl;
		return;
	}
}

int Graph::getNodeAmount()
{
    return this->nodeAmount;
}

int** Graph::getMatrix()
{
    return this->matrix;
}