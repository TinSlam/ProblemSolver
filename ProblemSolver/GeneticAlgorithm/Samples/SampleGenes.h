#pragma once

#include "../Base/Genes.h"

class SampleGenes : public Genes{
	public :
		float* data = nullptr;
		
		SampleGenes();
		~SampleGenes();

		void crossover(Genes* parent1, Genes* parent2);
		void mutate(int index, float randomGaussianNumber);
};

