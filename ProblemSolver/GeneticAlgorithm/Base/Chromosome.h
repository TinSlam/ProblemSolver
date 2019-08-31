#pragma once

#include "Genes.h"

class Chromosome{
	public :
		float fitness = 0;
		Genes* genes = nullptr;

		Chromosome(Genes* genes);
		~Chromosome();
};

