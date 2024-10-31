#pragma once
#include <string>
#include <vector>

class Object {
public:
    // Constructor
    Object(const std::string& name = "", int val = 0, double wgt = 0.0);

    // Public member variables
    std::string Name;
    int value;
    double weight;
};

std::vector<Object> InitializeKnapsack(int& maxGene);

void DefineFitness(std::vector<Individual>& population, std::vector<Object> currObjects);