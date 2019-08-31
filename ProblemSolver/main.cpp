#include "ClassicalSearch/Algorithm/AStarSearchAlgorithm.h"
#include "ClassicalSearch/Problem/SlidingPuzzleProblem.h"

#include "GeneticAlgorithm/Base/GeneticAlgorithm.h"
#include "GeneticAlgorithm/Samples/SampleGenes.h"

#include "NeuralNetwork/Base/NeuralNetworks.h"

#include "Utils/Utils.h"

void classicalSearch();
void geneticAlgorithm();
void neuralNetworks();

int main(){
	classicalSearch();
	//geneticAlgorithm();
	//neuralNetworks();
	printf("Program terminated successfully !\n");
	while(1);
}

void classicalSearch(){
	SlidingPuzzleProblem problem(new int[9]{4, 1, 3, 7, 2, 6, 5, 9, 8});
	AStarSearchAlgorithm algorithm;
	
	std::list<Action*>* actions = algorithm.search(&problem);

	printf("Path :\n");
	for(auto it = actions->begin(); it != actions->end(); it++){
		printf("%s\n", (*it)->toString().c_str());
	}
	printf("Done !\n");
}

void geneticAlgorithm(){
	GeneticAlgorithm ga;
	
	int populationSize = 50;
	int crossovers = 50;
	float mutationProbability = 0.5f;
	int maxGenerations = 200;
	float errorTerminationThreshold = 0.0001f;

	Chromosome* fittestChromosome = ga.start(populationSize, crossovers, mutationProbability, maxGenerations, errorTerminationThreshold, []() -> Genes*{
		return new SampleGenes();
	}, [](Chromosome* individual) -> float{
		SampleGenes* genes = (SampleGenes*) individual->genes;
		return Utils::abs(genes->data[0]);
	});
	
	printf("Fittest chromosome :\n");
	SampleGenes* genes = ((SampleGenes*) fittestChromosome->genes);
	int length = genes->chromosomeLength;
	for(int i = 0; i < length; i++){
		if(i == length - 1){
			printf("%f\n", genes->data[i]);
		}else{
			printf("%f, ", genes->data[i]);
		}
	}
}

void neuralNetworks(){
	NeuralNetworks network;

	Utils::initRandom();

	int clusters = 12;
	int classes = 4;
	NeuralNetworksParameters parameters;
	std::vector<NeuralNetworksData*> data;
	
	int sampleSize = 40;
	int dataDimension = 4;
	for(int i = 0; i < sampleSize; i++){
		NeuralNetworksData* entry = new NeuralNetworksData();
		for(int j = 0; j < dataDimension; j++){
			entry->data.push_back(Utils::random());
		}
		entry->output = Utils::randomInt(0, classes);
		data.push_back(entry);
	}

	network.train(&data, clusters, classes, &parameters);

	std::vector<int> output;
	
	network.test(&data, &parameters, &output);

	printf("Classification result :\n");
	for(int i = 0; i < output.size(); i++){
		printf("%d\n", output[i]);
	}
}