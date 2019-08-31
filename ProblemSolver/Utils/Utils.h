#pragma once

#include <random>

class Utils{
	private :
		static std::default_random_engine generator;

	public :
		static float abs(float num);

		static void initRandom();
		static float random();
		static float randomGaussian();
		static int randomInt(int a, int b);
};