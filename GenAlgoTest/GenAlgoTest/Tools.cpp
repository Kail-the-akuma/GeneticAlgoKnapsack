#include "Tools.h"
#include <iostream>
#include <vector>
#include <string>
#include <random>  //Para random

using namespace std;

void PrintVector(const vector<int>& vector)
{
	for (int i = 0; i < vector.size(); i++)
	{
		cout << vector[i] << " ";
	}
	cout << endl;
}

int GenerateRandom(int min, int max)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distrib(min, max);
	return  distrib(gen);
}

char PromptForInput(string chars)
{
	char out;

	cout << chars << endl;
	cin >> out;

	return out;
}