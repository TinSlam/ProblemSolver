#pragma once

#include "Chromosome.h"
#include <functional>
#include <list>

class GeneticAlgorithm{
	private :
		int populationSize = 0;
		int crossoversSize = 0;
		float mutationProbability = 0;
		int maxGenerations = 0;
		float errorTerminationThreshold = 0;

		Chromosome** population = nullptr;
		Chromosome** crossovers = nullptr;

		Chromosome* fittestChromosome = nullptr;
		std::list<Chromosome*> fittestList;

	public :
		~GeneticAlgorithm();

		Chromosome* start(int populationSize, int crossoversSize, float mutationProbability, int maxGenerations, float errorTerminationThreshold,
			std::function<Genes*()> generateChromosome,
			std::function<float(Chromosome*)> fitnessFunction);
		float nextGeneration(std::function<Genes*()> generateGenes, std::function<float(Chromosome*)> fitnessFunction);

		Chromosome* chooseParent(Chromosome** population);
		Chromosome* crossover(Chromosome* parent1, Chromosome* parent2, std::function<Genes*()> generateGenes);
		void mutate(Chromosome* chromosome);
		void selectBest(Chromosome** population, Chromosome** crossovers);

		int partition(Chromosome** a, int start, int end);
		void quickSort(Chromosome** a, int start, int end);
};

