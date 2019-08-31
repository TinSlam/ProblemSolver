#include "Utils.h"

#include <cstdlib>
#include <time.h>

std::default_random_engine Utils::generator;

float Utils::abs(float num){
	if(num < 0)
		return -num;
	return num;
}

void Utils::initRandom(){
	srand((unsigned int) time(0));
	generator.seed((unsigned int) time(0));
}

float Utils::random(){
	return ((float) rand() / RAND_MAX - 0.5f) * 2;
}

float Utils::randomGaussian(){
	std::normal_distribution<float> normalDistribution(0, 10);
	return normalDistribution(generator);
}

int Utils::randomInt(int a, int b){
	int random = rand();
	if(random == RAND_MAX)
		return randomInt(a, b);
	return (int) ((float) random / RAND_MAX * (b - a) + a);
}