#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <random>
#include "GeneticAlgo.h"
#include "Tools.h"
#include "Individual.h"

class Object
{
public: 
	std::string Name;
	int value;
	double weight;


	Object(const std::string& name = "", int val = 0, double wgt = 0)
		: Name(name), value(val), weight(wgt) {}
};


std::vector<Object> DefineObjects()
{
    std::vector<Object> objects;

    //40 items
    objects.push_back(Object("Portatil", 1500, 4));
    objects.push_back(Object("Smartphone", 800, 2));
    objects.push_back(Object("Camera", 600, 3));
    objects.push_back(Object("Headphones", 200, 1));
    objects.push_back(Object("Livro", 50, 1));
    objects.push_back(Object("Garrafa de Agua", 20, 0.5));
    objects.push_back(Object("Carteira", 100, 0.5));
    objects.push_back(Object("Tablet", 300, 1.5));
    objects.push_back(Object("Relogio", 150, 0.3));
    objects.push_back(Object("Mochila", 400, 1));
    objects.push_back(Object("Oculos", 80, 0.2));
    objects.push_back(Object("Pen Drive", 40, 0.1));
    objects.push_back(Object("Carregador", 30, 0.2));
    objects.push_back(Object("Caderno", 60, 0.8));
    objects.push_back(Object("Power Bank", 120, 0.5));
    objects.push_back(Object("Oculos de Sol", 90, 0.2));
    objects.push_back(Object("Lanterna", 70, 0.4));
    objects.push_back(Object("Kit de Primeiros Socorros", 110, 1.2));
    objects.push_back(Object("Coluna Portatil", 250, 1.3));
    objects.push_back(Object("Caneca Termica", 30, 0.4));
    objects.push_back(Object("Lente de Camera", 500, 1.8));
    objects.push_back(Object("Fones Bluetooth", 150, 0.5));
    objects.push_back(Object("HDD", 200, 0.7));
    objects.push_back(Object("Multiferramenta", 90, 0.6));
    objects.push_back(Object("Saco de Dormir", 180, 2));
    objects.push_back(Object("Barraca", 250, 3));
    objects.push_back(Object("Binoculos", 130, 0.8));
    objects.push_back(Object("Churrasqueira Portátil", 160, 1.5));
    objects.push_back(Object("Cadeira de Camping", 70, 1.2));
    objects.push_back(Object("Extensao", 40, 0.3));
    objects.push_back(Object("Termometro Digital", 25, 0.2));
    objects.push_back(Object("Chaleira Eletrica", 80, 1.0));
    objects.push_back(Object("Utensilios de Cozinha", 50, 1.5));
    objects.push_back(Object("Guia de Viagem", 60, 0.5));
    objects.push_back(Object("Manual de Primeiros Socorros", 35, 0.3));
    objects.push_back(Object("Protetor Solar", 20, 0.2));
    objects.push_back(Object("Repelente de Insetos", 25, 0.3));
    objects.push_back(Object("Canivete Multiuso", 75, 0.6));
    objects.push_back(Object("Pen Drive", 45, 0.1));
    objects.push_back(Object("Suporte para Portatil", 55, 0.8));
    objects.push_back(Object("Adaptador de Energia", 30, 0.2));
    objects.push_back(Object("Carregador Portátil", 110, 0.4));
    objects.push_back(Object("Almofada de Viagem", 40, 0.5));
    objects.push_back(Object("Capa de Chuva", 70, 0.6));
    objects.push_back(Object("Rato ", 100, 0.7));

    return objects;
}

std::vector<Object> SelectSubset(std::vector<Object>& objects, int numItens)
{


    // RNG
    std::random_device rd;
    std::mt19937 gen(rd());

    // Mistura valores no array
    std::shuffle(objects.begin(), objects.end(), gen);

    // Obtem os primeiros valores apartir do inicio durante o numero de items escolhido
    std::vector<Object> selecionados(objects.begin(), objects.begin() + numItens);

    return selecionados;
}

std::vector<Object> InitializeKnapsack(int& maxGene)
{
    std::vector<Object> allObjects = DefineObjects();

    std::vector<Object> subSet;
    while (maxGene < 5 || maxGene >40)
    {
        std::cout << "Selecionar o numero de objects para o problema entre 5 e 40" << std::endl;
        std::cin >> maxGene;


        if (std::cin.fail()) 
        {

            std::cin.clear();

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada invalida. Tem que ser entre 5 e 40." << std::endl;
            continue;
        }

        if (maxGene < 5 || maxGene > 15) 
        {
            std::cout << "Numero fora do intervalo. Tem que ser entre 5 e 40." << std::endl;
        }
    }

    try 
    {
        subSet = SelectSubset(allObjects, maxGene);

        // Display the selected subset
        std::cout << "Itens selecionados:" << std::endl;
        for (const auto& obj : subSet)
        {
            std::cout << std::left 
                << std::setw(40)
                << std::setfill('.')
                << ("Nome: " + obj.Name)       
                << std::setw(20)     
                << ("Valor:" + std::to_string(obj.value) + "eur")
                << "Peso: "                    
                << std::fixed                  
                << std::setprecision(2)        
                << (obj.weight * 100)          
                << "g"                         
                << std::endl;
        }
    }
    catch (const std::invalid_argument& e) 
    {
        std::cout << e.what() << std::endl;
        return subSet;
    }

    return subSet;
}

int DoPartitionForSort(std::vector<Individual>& population, int start, int end)
{
    int i = start - 1;
    int pivot = population[end].Fitness;

    for (int j = start; j < end; j++)
    {
        if (population[j].Fitness > pivot)
        {
            i++;
            std::swap(population[j], population[i]);
        }
    }

    i++;
    std::swap(population[i], population[end]);

    return i;
}

void OrderVectorByQuickSort(std::vector<Individual>& population, int start, int end)
{
    if (start >= end)
    {
        return;
    }
    int mid = DoPartitionForSort(population, start, end);

    OrderVectorByQuickSort(population, start, mid - 1);
    OrderVectorByQuickSort(population, mid + 1, end);
}

void DefineFitness(std::vector<Individual>& population, std::vector<Object> currObjects )
{
    int weightLimit = 1000;

    for (int i = 0; i < population.size(); i++) 
    {
        population[i].Fitness = 0;  
        double weightCounter = 0;

        for (int j = 0; j < population[i].Genes.size(); j++) 
        {
            if (population[i].Genes[j] == 0) {
                continue;  
            }

            weightCounter += currObjects[j].weight * 100;  

            if (weightCounter  > weightLimit) 
            {
                population[i].Fitness = 0; 
                break;  
            }

            population[i].Fitness += currObjects[j].value;
        }
    }

    OrderVectorByQuickSort(population, 0, (int)population.size() - 1);
    std::cout << "Results in order :" << std::endl;
    for (int i = 0; i < population.size(); i++)
    {
        std::cout << "Individual id: "
            << population[i].generation
            << population[i].id
            << " Fitnes : "
            << std::setw(5)  
            << population[i].Fitness  
            << " - "  
            << std::setfill(' ') 
            <<"Genes : ";
        PrintVector(population[i].Genes);
    }
}

