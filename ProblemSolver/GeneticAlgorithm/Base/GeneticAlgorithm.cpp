#include "GeneticAlgorithm.h"

#include <vector>

#include "../../Utils/Utils.h"

GeneticAlgorithm::~GeneticAlgorithm(){
	for(int i = 0; i < populationSize; i++){
		delete(population[i]);
	}
	for(int i = 0; i < crossoversSize; i++){
		//if(crossovers[i] != nullptr)
			//delete(crossovers[i]); // TODO : Free leftover crossovers and fittestChromosomes.
	}
	delete(population);
	delete(crossovers);
}

Chromosome* GeneticAlgorithm::start(int populationSize, int crossoversSize, float mutationProbability, int maxGenerations, float errorTerminationThreshold, std::function<Genes*()> generateGenes, std::function<float(Chromosome*)> fitnessFunction){
	this->populationSize = populationSize;
	this->crossoversSize = crossoversSize;
	this->mutationProbability = mutationProbability;
	this->maxGenerations = maxGenerations;
	this->errorTerminationThreshold = errorTerminationThreshold;

	Utils::initRandom();

	population = new Chromosome*[populationSize];
	crossovers = new Chromosome*[crossoversSize];
	for(int i = 0; i < populationSize; i++){
		population[i] = new Chromosome(generateGenes());
	}

	printf("GA initiated...\n");
	double error;
	int terminationCounter = 0;
	do{
		printf("Generation %d.\n", terminationCounter);
		error = nextGeneration(generateGenes, fitnessFunction);
		terminationCounter++;
	}while(error > errorTerminationThreshold && terminationCounter < maxGenerations);
	printf("Termination condition met on generation %d out of the maximum of %d.\n", terminationCounter, maxGenerations);

	return fittestChromosome;
}

float GeneticAlgorithm::nextGeneration(std::function<Genes*()> generateGenes, std::function<float(Chromosome*)> fitnessFunction){
	float error = 0;
	float minimumFitness = fitnessFunction(population[0]);
	float maximumFitness = minimumFitness;
	//fittestList.push_back(fittestChromosome);
	float averageFitness = minimumFitness;
	population[0]->fitness = minimumFitness;
	fittestChromosome = population[0];
	//fittestList.push_back(fittestChromosome);
	for(int i = 1; i < populationSize; i++){
		error = fitnessFunction(population[i]);
		population[i]->fitness = error;
		if(error > maximumFitness)
			maximumFitness = error;
		if(error < minimumFitness){
			minimumFitness = error;
			fittestChromosome = population[i];
		}
		averageFitness += error;
	}
	averageFitness /= populationSize;
	printf("Average : %lf\nMinimum %lf\nMaximum %lf\n\n", averageFitness, minimumFitness, maximumFitness);

	for(int i = 0; i < crossoversSize; i++){
		Chromosome* parent1 = chooseParent(population);
		Chromosome* parent2 = chooseParent(population);
		crossovers[i] = crossover(parent1, parent2, generateGenes);
		mutate(crossovers[i]);
		crossovers[i]->fitness = fitnessFunction(crossovers[i]);
	}

	selectBest(population, crossovers);

	return minimumFitness;
}

Chromosome* GeneticAlgorithm::chooseParent(Chromosome** population){
	std::vector<Chromosome*> contestants;
	for(int i = 0; i < 3; i++){
		contestants.push_back(population[Utils::randomInt(0, populationSize)]);
	}

	Chromosome* contestant = contestants[0];
	for(int i = 1; i < (int) contestants.size(); i++)
		if(contestants[i]->fitness < contestant->fitness)
			contestant = contestants[i];

	return contestant;
}

Chromosome* GeneticAlgorithm::crossover(Chromosome* parent1, Chromosome* parent2, std::function<Genes*()> generateGenes){
	Chromosome* child = new Chromosome(generateGenes());
	child->genes->crossover(parent1->genes, parent2->genes);
	return child;
}

void GeneticAlgorithm::mutate(Chromosome* chromosome){
	for(int i = 0; i < fittestChromosome->genes->chromosomeLength; i++)
		if(Utils::random() < mutationProbability){
			chromosome->genes->mutate(i, Utils::randomGaussian());
		}
}

void GeneticAlgorithm::selectBest(Chromosome** population, Chromosome** crossovers){
	quickSort(population, 0, populationSize - 1);
	quickSort(crossovers, 0, crossoversSize - 1);
	int populationCounter = 0;
	int crossoversCounter = 0;
	Chromosome** newPopulation = new Chromosome*[populationSize];
	for(int i = 0; i < populationSize; i++){
		if(crossoversCounter == crossoversSize){
			newPopulation[i] = population[populationCounter];
			populationCounter++;
			continue;
		}
		if(population[populationCounter]->fitness < crossovers[crossoversCounter]->fitness){
			newPopulation[i] = population[populationCounter];
			populationCounter++;
		}else{
			newPopulation[i] = crossovers[crossoversCounter];
			crossoversCounter++;
		}
	}
	for(int i = populationCounter; i < populationSize; i++){
		if(population[i] != fittestChromosome)
			delete(population[i]);
	}
	for(int i = crossoversCounter; i < crossoversSize; i++){
		delete(crossovers[i]);
	}
	for(int i = 0; i < populationSize; i++){
		population[i] = newPopulation[i];
	}
	delete(newPopulation);
}

int GeneticAlgorithm::partition(Chromosome** a, int start, int end){
	Chromosome* pivot = a[end];
	Chromosome* t;
	int index = start;

	for(int i = start; i < end; i++){
		if(a[i]->fitness <= pivot->fitness){
			t = a[i];
			a[i] = a[index];
			a[index] = t;
			index++;
		}
	}

	t = a[end];
	a[end] = a[index];
	a[index] = t;

	return index;
}
void GeneticAlgorithm::quickSort(Chromosome** a, int start, int end){
	if(start < end){
		int index = partition(a, start, end);
		quickSort(a, start, index - 1);
		quickSort(a, index + 1, end);
	}
}