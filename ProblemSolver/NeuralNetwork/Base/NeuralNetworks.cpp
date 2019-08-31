#include "NeuralNetworks.h"

#include "NeuralNetworksGenes.h"
#include "../../GeneticAlgorithm/Base/GeneticAlgorithm.h"
#include "../../Utils/Utils.h"

void NeuralNetworks::train(std::vector<NeuralNetworksData*>* data, int clusters, int classes, NeuralNetworksParameters* parameters){
	parameters->clusters = clusters;
	parameters->classes = classes;

	Utils::initRandom();

	Eigen::MatrixXd gMatrix(data->size(), clusters);
	Eigen::MatrixXd fittestWeights(clusters, classes);
	Eigen::MatrixXd wMatrix(clusters, classes);
	Eigen::MatrixXd predictions(data->size(), classes);
	Eigen::MatrixXd output(data->size(), classes);

	for(int i = 0; i < clusters; i++){
		for(int j = 0; j < classes; j++){
			wMatrix(i, j) = Utils::random();
		}
	}

	for(int i = 0; i < data->size(); i++){
		for(int j = 0; j < classes; j++){
			output(i, j) = 0;
		}
		output(i, (*data)[i]->output) = 1;
	}

	int dataDimension = (int) (*data)[0]->data.size();
	Eigen::MatrixXd dataMatrix(data->size(), dataDimension);
	for(int i = 0; i < data->size(); i++){
		for(int j = 0; j < dataDimension; j++){
			dataMatrix(i, j) = (*data)[i]->data[j];
		}
	}

	float minimumError = std::numeric_limits<float>::max();

	GeneticAlgorithm geneticAlgorithm;
	geneticAlgorithm.start(30, 200, 0.9f, 1000, 0,
		[clusters, dataDimension]() -> Genes*{
			return new NeuralNetworksGenes(clusters * (dataDimension + 1));
		},
		[&](Chromosome* individual) -> float{
			NeuralNetworksGenes* genes = (NeuralNetworksGenes*) individual->genes;
			
			for(int i = 0; i < data->size(); i++)
				for(int j = 0; j < clusters; j++){
					double error = 0;
					for(int k = 0; k < dataDimension; k++){
						error += pow(dataMatrix(i, k) - genes->data[j * (dataDimension + 1) + k + 1], 2) / 100;
					}
					gMatrix(i, j) = exp((float) (-genes->data[j * (dataDimension + 1)] / 100 * error));
				}
			
			predictions = gMatrix * wMatrix;
			
			float error = 0;
			float value;
			for(int i = 0; i < data->size(); i++){
				int index = 0;
				value = (float) predictions(i, 0);
				for(int j = 1; j < parameters->classes; j++){
					if(predictions(i, j) > value){
						value = (float) predictions(i, j);
						index = j;
					}
				}
				if(output(i, index) == 0)
					error++;
			}

			if(error < minimumError){
				Eigen::MatrixXd temp = gMatrix.transpose() * gMatrix;
				if(temp.determinant() != 0)
					wMatrix = temp.inverse() * gMatrix.transpose() * output;
				
				minimumError = error;
				parameters->weights = wMatrix;

				Chromosome* chromosome = new Chromosome(new NeuralNetworksGenes(clusters * (dataDimension + 1)));
				for(int i = 0; i < clusters * (dataDimension + 1); i++){
					((NeuralNetworksGenes*) chromosome->genes)->data[i] = genes->data[i];
				}
				parameters->chromosome = chromosome;
			}

			return error;
		}
	);
}

void NeuralNetworks::test(std::vector<NeuralNetworksData*>* data, NeuralNetworksParameters* parameters, std::vector<int>* output){
	NeuralNetworksGenes* genes = (NeuralNetworksGenes*) parameters->chromosome->genes;
	int dataDimension = (int) (*data)[0]->data.size();
	
	Eigen::MatrixXd dataMatrix(data->size(), dataDimension);
	for(int i = 0; i < data->size(); i++){
		for(int j = 0; j < dataDimension; j++){
			dataMatrix(i, j) = (*data)[i]->data[j];
		}
	}

	Eigen::MatrixXd gMatrix(data->size(), parameters->clusters);
	Eigen::MatrixXd wMatrix = parameters->weights;
	Eigen::MatrixXd predictions(data->size(), parameters->classes);

	for(int i = 0; i < data->size(); i++)
		for(int j = 0; j < parameters->clusters; j++){
			double error = 0;
			for(int k = 0; k < dataDimension; k++){
				error += pow(dataMatrix(i, k) - genes->data[j * (dataDimension + 1) + k + 1], 2) / 100;
			}
			gMatrix(i, j) = exp((float) (-genes->data[j * (dataDimension + 1)] / 100 * error));
		}

	predictions = gMatrix * wMatrix;

	float value;
	for(int i = 0; i < data->size(); i++){
		(*output).push_back(0);
		value = (float) predictions(i, 0);
		for(int j = 1; j < parameters->classes; j++){
			if(predictions(i, j) > value){
				value = (float) predictions(i, j);
				(*output)[i] = j;
			}
		}
	}
}