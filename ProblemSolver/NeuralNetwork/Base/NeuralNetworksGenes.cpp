#include "NeuralNetworksGenes.h"

#include "../../Utils/Utils.h"

NeuralNetworksGenes::NeuralNetworksGenes(int chromosomeLength){
	this->chromosomeLength = chromosomeLength;
	data = new float[chromosomeLength];
	for(int i = 0; i < chromosomeLength; i++){
		data[i] = Utils::random();
	}
}

NeuralNetworksGenes::~NeuralNetworksGenes(){
	if(data != nullptr)
		delete(data);
}

void NeuralNetworksGenes::crossover(Genes* parent1, Genes* parent2){
	NeuralNetworksGenes* p1 = (NeuralNetworksGenes*) parent1;
	NeuralNetworksGenes* p2 = (NeuralNetworksGenes*) parent2;
	for(int i = 0; i < chromosomeLength; i++){
		if(Utils::randomInt(0, 10) <= 5){
			data[i] = p1->data[i];
		}else{
			data[i] = p2->data[i];
		}
	}
}

void NeuralNetworksGenes::mutate(int index, float randomGaussianNumber){
	data[index] += randomGaussianNumber * 0.4f;
}