#include "SelectionAlgos.h"
#include <vector>
#include "Individual.h"
using namespace std;

//Tournement size define o maximo de comparações que ocorrem dentro de cada seleção
//Sem replacement
Individual TournementSelection(std::vector<Individual> population, int tournamentSize) 
{
    int populationSize = population.size();

    // Cria um individuo novo com valor de fitness baixo para comparação
    Individual bestIndividual;
    bestIndividual.Fitness = -1;

    for (int i = 0; i < tournamentSize; i++) 
    {
        //Escolhe um Individuo da população aleatoriamente
        int randomIndex = rand() % populationSize;
        Individual selectedIndividual = population[randomIndex];

        // Compara a fitness com o melhor
        if (selectedIndividual.Fitness > bestIndividual.Fitness) 
        {
            bestIndividual = selectedIndividual;
        }
    }

    return bestIndividual;
}