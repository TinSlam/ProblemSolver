#pragma once

#include <vector>
#include <Eigen/Dense>

#include "NeuralNetworksData.h"
#include "NeuralNetworksParameters.h"

class NeuralNetworks{
	public :
		void train(std::vector<NeuralNetworksData*>* data, int clusters, int classes, NeuralNetworksParameters* parameters);
		void test(std::vector<NeuralNetworksData*>* data, NeuralNetworksParameters* parameters, std::vector<int>* output);
};