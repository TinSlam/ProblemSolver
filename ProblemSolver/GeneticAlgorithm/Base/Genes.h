#pragma once

class Genes{
	public :
		int chromosomeLength = 0;

		virtual void crossover(Genes* parent1, Genes* parent2) = 0;
		virtual void mutate(int index, float randomGaussianNumber) = 0;
};

