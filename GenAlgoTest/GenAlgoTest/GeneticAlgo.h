#pragma once
#include <vector>
#include "Individual.h"
std::vector<Individual> InitializeGeneticAlgo(int maxPopulation, int maxGenes);

std::vector<Individual> DoGeneticAlgo(std::vector<Individual> currPopulation, int generation, int maxPopulation);