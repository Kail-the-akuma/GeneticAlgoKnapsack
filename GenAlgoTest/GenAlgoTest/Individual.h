#pragma once
#include <vector>

class Individual
{
public:
	std::vector<int> Genes;
	int Fitness = 0;
	int generation;
	int id;
};

