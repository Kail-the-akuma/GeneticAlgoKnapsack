from random import random, choices, randint, randrange
from typing import List, Callable, Tuple
from collections import namedtuple
from functools import partial



#Indica o tipo de variavel associado ao genome (individuo) pode conter x numeros internamente
Genome = list[int]
Population = List[Genome]
#Inicializa a population
PopulateFunc = Callable[[], Population]
#Função de fitness generica
FitnessFunc = Callable[[Genome], int]
#Inicializa a seleçao
SelectFunc = Callable[[Population,FitnessFunc], Tuple[Genome,Genome]]
#Dados dois Genomes (Pais) devolve dois novos
CrossoverFunc = Callable[[Genome,Genome], Tuple[Genome,Genome]]
#Altera valores do Genome se condiçoes se aplicarem
MutationFunc = Callable[[Genome], Genome]

#Uma coisa refere-se a um objeto com nome valor e pesso estes seram os objetos a considerar
Thing = namedtuple('Thing', ['name','value','weight'])

things = [
        Thing('Laptop', 500, 2200),
        Thing('Headphones', 150, 160),
        Thing('Coffe Mug', 60, 350),
        Thing('Notepad', 40, 333),
        Thing('WaterBotle', 30, 192)
    ]

other_things = [
    Thing('Mints', 5, 25),
    Thing('Socks', 10, 38),
    Thing('Tissues', 15, 80),
    Thing('Phone', 500, 200),
    Thing('Baseball Cap', 100, 70)
] + things


#define uma função que recebe o lenght como input sendo associada ao tipo declarado anteriormente
#nota sobre python o operador -> indica o tipo de return 
def generate_genome(length: int) -> Genome:
    #Devolve uma serie de numeros aleatorios entre 0 e 1 para atribuir a população
    #k= lenght indica o tamanho da geração (k é um parametro do metodo choices)
    return choices([0,1], k=length)



#Cria uma população com base no metodo anterior para a extenção definida
def generate_population(size: int, genome_length: int) -> Population:
    #devolve a população criada aleatoriamente  com base no metodo e tamanho definidos
    #nota sobre python o uso de "_" dentro de um for loop indica que a variavel em questão não é importante para o loop apenas o loop em si
    return [generate_genome(genome_length) for _ in range(size)]

#Função que calcula a fitness especificamente para o problema em questão
def fitness(genome: Genome, things: List[Thing], weight_limit:int) -> int:
    if len(genome) != len(things):
        raise ValueError("A lista de genome e de objetos devem ser do mesmo tamanho")
    
    weight = 0
    value = 0

    #por cada objeto
    for i, thing in enumerate(things):
        #se o valor for 1 é parte da solução se for 0 não
        if genome[i] ==1:

            #atribuimos os valores do genome atual as variaveis
            weight += thing.weight
            value += thing.value

            #se o pesso atual for acima do limite significa que a solução não é valida devolvemos o 0
            if weight > weight_limit:
                return 0
    
    #Se a lista terminar sem passar o pesso significa que a solução é valida
    return value

#Função que seleciona os pares de soluções utilizados como pais para futuras seleções
def selection_pair(population: Population, fitnes_func: FitnessFunc) -> Population:
    
    #Nota sobre phython o metodo choices devolve uma lista (população) com os elementos alterados
    return choices(
        population=population,
        weights=[fitnes_func(genome) for genome in population],
        #recolhe duas vezes da população
        k=2
    )

#Corta os dois genomes e cria dois novos com as misturas de ambos
def single_point_crossover(a: Genome, b: Genome) -> Tuple[Genome, Genome]:
    #Ambos genomes devem ter o mesmo tamanho
    if len(a) != len(b):
        raise ValueError("Os Genomas devem ter o mesmo tamanho")

    length = len(a)

   #Se o lenght for menor que dois é impossivel criar divisao
    if length < 2:
        return a, b

    #Gera um ponto aleatorio para separar os genomes com base nas dimensoes dos mesmos
    p = randint(1, length - 1)
    
    #novo genome devolve a primeira parte do a e o final do b
    genA = a[0:p] + b[p:]
    #novo genome devolve a primeira parte do b e o final do a
    genB = b[0:p] + a[p:]

    #Evita que a função retorne Tipo None
    if genA is None or genB is None:
        print(f"Crossover falhou no ponto {p} com pais {a} e {b}")
        return a, b  # Retorne pais em caso de falho
    
    return genA, genB

def mutation(genome: Genome, num: int = 1, probability: float = 0.5) -> Genome:
    for _ in range(num):
        index = randrange(len(genome))
        #Validamos se ocorre mutação
        #Se valido fazemos bit flip no valor do index atual
        genome[index] = genome[index] if random() > probability else abs(genome[index] - 1)
    return genome

def run_evolution(
    populate_func: PopulateFunc,
    fitness_func: FitnessFunc,
    fitness_limit: int,
    selection_func: SelectFunc = selection_pair,
    crossover_func: CrossoverFunc = single_point_crossover,
    mutation_func: MutationFunc = mutation,
    generation_limit: int = 100
) -> Tuple[Population, int]:
    population = populate_func()

    for i in range(generation_limit):
        population = sorted(
            population,
            key=lambda genome: fitness_func(genome),
            reverse=True
        )
    
        if fitness_func(population[0]) >= fitness_limit:
            break

        next_generation = population[0:2]

        for j in range(int(len(population) / 2) - 1):
            parents = selection_func(population, fitness_func)
            child_a, child_b = crossover_func(parents[0], parents[1])
            child_a = mutation_func(child_a)
            child_b = mutation_func(child_b)

            if child_a is None or child_b is None:
                print(f"Error: Foi gerado um genoma com tipo none na geração {i}")
                print(f"Pais: {parents[0]}, {parents[1]}")
                print(f"Filhos: {child_a}, {child_b}")

            next_generation = next_generation + [child_a, child_b]

        population = next_generation

    population = sorted(
        population,
        key=lambda genome: fitness_func(genome),
        reverse=True
    )

    return population, i


population, generations = run_evolution(
    populate_func=partial(
        generate_population, size=10, genome_length= len(things)
    ),
    fitness_func=partial(
        fitness, things=things, weight_limit=3000
    ),
    fitness_limit=740,
    generation_limit=100
)

def genome_to_things(genome : Genome, things: List[Thing])-> List[Thing]:
    
    result = []
    
    for i, thing in enumerate(things):
        if genome[i] == 1:
            result += [thing.name]
    
    return result

print(f"number of generations:{generations}")
print(f"best solution: {genome_to_things(population[0], things)}")