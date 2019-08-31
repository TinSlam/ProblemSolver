#pragma once

#include <Eigen/Dense>

#include "../../GeneticAlgorithm/Base/Chromosome.h"

class NeuralNetworksParameters{
	public :
		int clusters = 0;
		int classes = 0;
		Eigen::MatrixXd weights;
		Chromosome* chromosome = nullptr;
};
