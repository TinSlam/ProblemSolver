#include "Chromosome.h"
#include <stdio.h>

Chromosome::Chromosome(Genes* genes){
	this->genes = genes;
}

Chromosome::~Chromosome(){
	delete(genes);
}