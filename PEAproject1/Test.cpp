#include "Test.h"

int Test::amount[7]{ 4, 6, 8, 10, 12, 14, 16 }; //7 different amounts of cities to test algorithms for

void Test::tspFromFile() //Interface for testing correctness of algorithms
{
	while (1)
	{
		cout << endl;
		cout << "Which algorithm you want to test?\n"
			<< "1 - Brute Force\n"
			<< "2 - Dynamic Programming\n"
			<< "3 - Branch and Bound method 1\n"
			<< "4 - Branch and Bound method 2\n"
			<< "5 - Simulated annealing\n"
			<< "6 - Tabu search\n"
			<< "0 - Go back\n" << endl;

		int choice;
		cin >> choice;

		vector<unsigned> finalPath;
		int finalCost = INT32_MAX;

		Graph graph;

		switch (choice)
		{
		case 1:
			graph.readFromFile();
			graph.bruteForce(finalCost, finalPath);
			break;
		case 2:
			graph.readFromFile();
			graph.DPalgorithm(finalCost, finalPath);
			break;
		case 3:
			graph.readFromFile();
			graph.BBAlgorithm(finalCost, finalPath);
			break;
		case 4:
			graph.readFromFile();
			graph.BBAlgorithm2(finalCost, finalPath);
			break;
		case 5:
			graph.readFromFile();
			graph.BBAlgorithm2(finalCost, finalPath);
			break;
		case 6:
			graph.readFromFile();
			graph.BBAlgorithm2(finalCost, finalPath);
			break;
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

void Test::tspGenerated() //Interface for automatic tests
{
	while (1)
	{
		cout << endl;
		cout << "Which algorithm you want to test?\n"
			<< "1 - Brute Force\n"
			<< "2 - Dynamic Programming\n"
			<< "3 - Branch and Bound method 1\n"
			<< "4 - Branch and Bound method 2\n"
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
		case 4:
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

void Test::generateAndTest(int chosenMethod) //Function responsible for automatic tests
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
			for (int i = 0; i < 7; i++) //Tests are made automaticly 100 times for every of 7 different amounts and results are saved in file
			{
				saveFile << "NUMBER OF CITIES: " << amount[i] << endl;
				for (int j = 0; j < 100; j++)
				{
					Graph graph;
					graph.generate(Test::amount[i]);

					vector<unsigned> path;
					int cost = INT32_MAX;

					timer.timerStart();
					graph.bruteForce(cost, path);
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

					timer.timerStart();
					graph.DPalgorithm(cost, path);
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

					timer.timerStart();
					graph.BBAlgorithm(cost, path);
					timer.timerStop();

					saveFile << timer.elapsedTime() << endl;
				}
				saveFile << endl;
			}
		}
		if (chosenMethod == 4)
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

					timer.timerStart();
					graph.BBAlgorithm2(cost, path);
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
