#include "SelectionAlgos.h"
#include <vector>
#include "Individual.h"
using namespace std;

//Tournement size define o maximo de compara��es que ocorrem dentro de cada sele��o
//Sem replacement
Individual TournementSelection(std::vector<Individual> population, int tournamentSize) 
{
    int populationSize = population.size();

    // Cria um individuo novo com valor de fitness baixo para compara��o
    Individual bestIndividual;
    bestIndividual.Fitness = -1;

    for (int i = 0; i < tournamentSize; i++) 
    {
        //Escolhe um Individuo da popula��o aleatoriamente
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