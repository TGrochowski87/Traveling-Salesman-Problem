/*
* Traveling Salesman Problem Solver By Tomasz Grochowski.
*/


#include "Test.h"

int Test::amount[7]{ 4, 6, 8, 10, 12, 14, 16 };

using namespace std;

void Test::tspFromFile()
{
	while (1)
	{
		cout << endl;
		cout << "Which algorithm you want to test?\n"
			<< "1 - Brute Force\n"
			<< "2 - Dynamic Programming\n"
			<< "3 - Branch and Bound\n"
			<< "4 - Simulated annealing\n"
			<< "5 - Tabu search\n"
			<< "6 - Genetic\n"
			<< "0 - Go back\n" << endl;

		int choice;
		cin >> choice;

		vector<unsigned> finalPath;
		int finalCost = INT32_MAX;

		Graph graph;

		switch (choice)
		{
		case 1:
		{
			graph.readFromFile();

			BruteForce bruteForce(graph.getNodeAmount(), graph.getMatrix());
			bruteForce.run(finalCost, finalPath);
			break;
		}
		case 2:
		{
			graph.readFromFile();

			DynamicProgramming dynamicProgramming(graph.getNodeAmount(), graph.getMatrix());
			dynamicProgramming.run(finalCost, finalPath);
			break;
		}
		case 3:
		{
			graph.readFromFile();

			BranchAndBound branchAndBound(graph.getNodeAmount(), graph.getMatrix());
			branchAndBound.run(finalCost, finalPath);
			break;
		}
		case 4:
		{
			graph.readFromFile();

			bool choosing = true;
			while (choosing)
			{
				cout << endl;
				cout << "Choose a neighbourhood generating method.\n"
					<< "1 - Swap\n"
					<< "2 - Reverse\n"
					<< "3 - Insert\n" << endl;

				int neighbourhoodChoice;
				cin >> neighbourhoodChoice;

				switch (neighbourhoodChoice)
				{
				case 1:
				{
					SimulatedAnnealing simulatedAnnealing(graph.getNodeAmount(), graph.getMatrix(), &NeighbourHoodFinder::neighbourhoodBySwap);
					choosing = false;

					simulatedAnnealing.run(finalCost, finalPath);
					break;
				}
				case 2:
				{
					SimulatedAnnealing simulatedAnnealing(graph.getNodeAmount(), graph.getMatrix(), &NeighbourHoodFinder::neighbourhoodByReverse);
					choosing = false;

					simulatedAnnealing.run(finalCost, finalPath);
					break;
				}
				case 3:
				{
					SimulatedAnnealing simulatedAnnealing(graph.getNodeAmount(), graph.getMatrix(), &NeighbourHoodFinder::neighbourhoodByInsert);
					choosing = false;

					simulatedAnnealing.run(finalCost, finalPath);
					break;
				}
				default:
				{
					cout << "Choose one of available options!" << endl;
					break;
				}
				}
			}
			break;
		}
		case 5:
		{
			graph.readFromFile();

			bool choosing = true;
			while (choosing)
			{
				cout << endl;
				cout << "Choose a neighbourhood generating method.\n"
					<< "1 - Swap\n"
					<< "2 - Reverse\n"
					<< "3 - Insert\n" << endl;

				int neighbourhoodChoice;
				cin >> neighbourhoodChoice;

				switch (neighbourhoodChoice)
				{
				case 1:
				{
					TabuSearch tabuSearch(graph.getNodeAmount(), graph.getMatrix(), &NeighbourHoodFinder::neighbourhoodBySwap);
					choosing = false;

					tabuSearch.run(finalCost, finalPath);
					break;
				}
				case 2:
				{
					TabuSearch tabuSearch(graph.getNodeAmount(), graph.getMatrix(), &NeighbourHoodFinder::neighbourhoodByReverse);
					choosing = false;

					tabuSearch.run(finalCost, finalPath);
					break;
				}
				case 3:
				{
					TabuSearch tabuSearch(graph.getNodeAmount(), graph.getMatrix(), &NeighbourHoodFinder::neighbourhoodByInsert);
					choosing = false;

					tabuSearch.run(finalCost, finalPath);
					break;
				}
				default:
				{
					cout << "Choose one of available options!" << endl;
					break;
				}
				}
			}
			break;
		}
		case 6:
		{
			graph.readFromFile();

			while (1)
			{
				cout << endl;
				cout << "Choose a crossover method:\n"
					<< "1 - PMX\n"
					<< "2 - OX\n"
					<< "Mutation method:\n"
					<< "1 - Invert\n"
					<< "2 - Scramble\n"
					<< "And type in desired population size.\n"
					<< "Seperated by space.\n"
					<< endl;

				int availableChoices[2]{1, 2};

				int crossoverChoice, mutationChoice, populationSize;
				cin >> crossoverChoice >> mutationChoice >> populationSize;

				if ((crossoverChoice != 1 && crossoverChoice != 2) || (mutationChoice != 1 && mutationChoice != 2))
				{
					cout << "Choose one of available options!" << endl;
					continue;
				}

				GeneticAlgorithm geneticAlgorithm(graph.getNodeAmount(), graph.getMatrix(), populationSize, crossoverChoice, mutationChoice);
				geneticAlgorithm.run(finalCost, finalPath);
				break;
			}
			break;
		}
		case 0:
			return;
		default:
			cout << "Choose one of available options!" << endl;
			break;
		}

		cout << "Cost = " << finalCost << endl;
		cout << "Path: " << finalPath.at(0) << flush;
		for (int i = 1; i < finalPath.size(); i++)
		{
			cout << " - " << finalPath.at(i) << flush;
		}
		cout << endl;
	}
	return;
}

void Test::tspGenerated()
{
	while (1)
	{
		cout << endl;
		cout << "Which algorithm you want to test?\n"
			<< "1 - Brute Force\n"
			<< "2 - Dynamic Programming\n"
			<< "3 - Branch and Bound\n"
			<< "0 - Go back\n" << endl;

		int choice;
		cin >> choice;

		switch (choice)
		{
		case 1:
			generateAndTest(choice);
			break;
		case 2:
			generateAndTest(choice);
			break;
		case 3:
			generateAndTest(choice);
			break;
		case 0:
			return;
		default:
			cout << "Choose one of available options!" << endl;
			break;
		}
	}
	return;
}

void Test::generateAndTest(int chosenMethod)
{
	Timer timer;
	string fileName;
	cout << "What file you want to save output in?" << endl;
	cin >> fileName;

	ofstream saveFile(fileName);
	if (saveFile.is_open())
	{
		if (chosenMethod == 1)
		{
			for (int i = 0; i < 7; i++)
			{

				saveFile << "NUMBER OF CITIES: " << amount[i] << endl;
				for (int j = 0; j < 100; j++)
				{
					Graph graph;
					graph.generate(Test::amount[i]);

					vector<unsigned> path;
					int cost = INT32_MAX;

					BruteForce bruteForce(graph.getNodeAmount(), graph.getMatrix());

					timer.timerStart();
					bruteForce.run(cost, path);
					timer.timerStop();

					saveFile << timer.elapsedTime() << endl;
				}
				saveFile << endl;
			}
		}
		if (chosenMethod == 2)
		{
			for (int i = 0; i < 7; i++)
			{
				saveFile << "NUMBER OF CITIES: " << amount[i] << endl;
				for (int j = 0; j < 100; j++)
				{
					Graph graph;
					graph.generate(Test::amount[i]);

					vector<unsigned> path;
					int cost = INT32_MAX;

					DynamicProgramming dynamicProgramming(graph.getNodeAmount(), graph.getMatrix());

					timer.timerStart();
					dynamicProgramming.run(cost, path);
					timer.timerStop();

					saveFile << timer.elapsedTime() << endl;
				}
				saveFile << endl;
			}
		}
		if (chosenMethod == 3)
		{
			for (int i = 0; i < 7; i++)
			{
				saveFile << "NUMBER OF CITIES: " << amount[i] << endl;
				for (int j = 0; j < 100; j++)
				{
					Graph graph;
					graph.generate(Test::amount[i]);

					vector<unsigned> path;
					int cost = INT32_MAX;

					BranchAndBound branchAndBound(graph.getNodeAmount(), graph.getMatrix());

					timer.timerStart();
					branchAndBound.run(cost, path);
					timer.timerStop();

					saveFile << timer.elapsedTime() << endl;
				}
				saveFile << endl;
			}
		}
	}
	else
	{
		cout << "ERROR - File did not open!" << endl;
		return;
	}
	saveFile.close();
	return;
}