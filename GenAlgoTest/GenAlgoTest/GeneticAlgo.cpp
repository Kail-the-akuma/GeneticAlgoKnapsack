#include <iostream>
#include <vector>
#include <string>
#include "GeneticAlgo.h"
#include "Tools.h"
#include "Individual.h"
# include "SelectionAlgos.h"

using namespace std;


int CreateGene()
{
	return GenerateRandom(0,1);
}

void CreateIndividual (Individual& currIndividual, int maxGenes)
{
	for (int i = 0; i < maxGenes; i++)
	{
		currIndividual.Genes.push_back(GenerateRandom(0, 1));
	}
}

void CreatePopulation(vector<Individual>& population, int populationSize, int maxGenes, int generation)
{
	for (int i = 0; i < populationSize; i++)
	{
		Individual currIndividual;
		currIndividual.generation = generation;
		currIndividual.id = i;

		CreateIndividual(currIndividual, maxGenes);

		population.push_back(currIndividual);
	}
}

vector<Individual> MergeIndividuals(Individual A, Individual B, int generation, int lastId)
{
	
	vector<Individual> newChilds;
	
	Individual childA;
	Individual childB;
	childA.generation = generation;
	childB.generation = generation;
	childA.id = lastId + 1;
	childB.id = lastId + 2;

	int middlePoint = (int)A.Genes.size() / 2;

	for (int i = 0; i < A.Genes.size(); i++)
	{
		if (i < middlePoint)
		{
			childA.Genes.push_back(A.Genes[i]);
			childB.Genes.push_back(B.Genes[i]);
		}
		else
		{
			childA.Genes.push_back(B.Genes[i]);
			childB.Genes.push_back(A.Genes[i]);
		}
	}



	newChilds.push_back(childA);
	newChilds.push_back(childB);

	return newChilds;
}

//BitFlip
void DoMutation(Individual& individual, double mutationProbability)
{
	int length = (int)individual.Genes.size();

	for (int i = 0; i < length; i++) 
	{

		double randomProb = (double)rand() / RAND_MAX;

		if (randomProb < mutationProbability) 
		{
			individual.Genes[i] = 1 - individual.Genes[i]; 
			cout << "Individual: " << individual.generation << individual.id << " has mutated a gene" << endl;
		}
	}
}


vector<Individual> InitializeGeneticAlgo(int maxPopulation, int maxGenes)
{
	vector<Individual> population;
	CreatePopulation(population, maxPopulation, maxGenes, 0);
	
	char input = PromptForInput("Ver populacao atual? Y/N");

	if (input == 'Y' || input == 'y')
	{
		int i = 0;
		for (const auto& individual : population)
		{
			i++;
			cout << "individiual " << individual.generation << individual.id << " genes : ";
			PrintVector(individual.Genes);
		}
	}
	return population;
}

vector<Individual> DoGeneticAlgo(vector<Individual> currPopulation, int generation, int maxPopulation)
{
	vector<Individual> newPopulation;

	//Duas primeiras escolhas passam automaticamente para a proxima geração
	newPopulation.push_back(currPopulation[0]);
	newPopulation.push_back(currPopulation[1]);
	newPopulation[0].generation = generation;
	newPopulation[1].generation = generation;

	int lastId = 0;

	while (newPopulation.size() < maxPopulation) 
	{

		Individual parentA = TournementSelection(currPopulation, 3);
		Individual parentB = TournementSelection(currPopulation, 3);

		vector<Individual> childs = MergeIndividuals(parentA, parentB, generation, lastId);

		for (int i = 0; i <= 1 && newPopulation.size() < maxPopulation; i++)
		{
			DoMutation(childs[i], 0.05);
			newPopulation.push_back(childs[i]);
		}
		lastId += 2;
	}

	return newPopulation;
}

