#pragma once

#include "../../GeneticAlgorithm/Base/Genes.h"

class NeuralNetworksGenes : public Genes{
	public :
		float* data = nullptr;

		NeuralNetworksGenes(int chromosomeLength);
		~NeuralNetworksGenes();

		void crossover(Genes* parent1, Genes* parent2);
		void mutate(int index, float randomGaussianNumber);
};

