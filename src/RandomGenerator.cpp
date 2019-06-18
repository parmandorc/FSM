#include "RandomGenerator.hpp"

#include <iostream>


RandomGenerator::RandomGenerator()
	: mEngine()
{
	std::random_device device;
	const unsigned int randomSeed = device();
	mEngine.seed(randomSeed);
	
	std::cout << "Randomly seeded the random generator with the seed: " << randomSeed << std::endl;
}

RandomGenerator::RandomGenerator(unsigned int pSeed)
	: mEngine(pSeed)
{

}

int RandomGenerator::Get(int pMin, int pMax)
{
	std::uniform_int_distribution<int> distribution(pMin, pMax);
	return distribution(mEngine);
}

float RandomGenerator::Get(float pMin, float pMax)
{
	std::uniform_real_distribution<float> distribution(pMin, pMax);
	return distribution(mEngine);
}
