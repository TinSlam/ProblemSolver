#include "SampleGenes.h"

#include "../../Utils/Utils.h"

SampleGenes::SampleGenes(){
	chromosomeLength = 10;
	data = new float[chromosomeLength];
	for(int i = 0; i < chromosomeLength; i++){
		data[i] = Utils::random();
	}
}

SampleGenes::~SampleGenes(){
	if(data != nullptr)
		delete(data);
}

void SampleGenes::crossover(Genes* parent1, Genes* parent2){
	SampleGenes* p1 = (SampleGenes*) parent1;
	SampleGenes* p2 = (SampleGenes*) parent2;
	for(int i = 0; i < chromosomeLength; i++){
		if(Utils::randomInt(0, 10) <= 5){
			data[i] = p1->data[i];
		}else{
			data[i] = p2->data[i];
		}
	}
}

void SampleGenes::mutate(int index, float randomGaussianNumber){
	data[index] += randomGaussianNumber * 0.001f;
}