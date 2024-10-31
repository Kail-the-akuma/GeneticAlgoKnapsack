#include <iostream>
#include <vector>  
#include "GeneticAlgo.h"
#include "Tools.h"
#include "KnapsackProblem.h"
#include "Individual.h"

int OptionsMenu()
{

    int option;
    
    std::cout << "What problem to use as example?\n"
        << "1 : Knapsack " << "\n"
        << "0 : exit" << std::endl;

    std::cin >> option;
    return option;
}

int main()
{

    //Para os random
    srand(time(0));

    switch (OptionsMenu())
    {
        case 0:
            return 0;
        case 1:
            int maxPop = 10;
            int maxGene;
            
            std::vector<Object> itemsList = InitializeKnapsack(maxGene);
            std::vector<Individual> population = InitializeGeneticAlgo(maxPop, maxGene);

            DefineFitness(population, itemsList);

            std::cout << "How many generations?";
            int generations;
            std::cin >> generations;
            
            for (int i = 0; i < generations; i++)
            {
                population = DoGeneticAlgo(population, i+1, maxPop);
                DefineFitness(population, itemsList);
            }

            break;
    }

    return 0;


}

