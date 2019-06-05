#include "RandomGenerator.hpp"

#include <iostream>


RandomGenerator::RandomGenerator()
	: mEngine()
	, m01Distribution(0.0f, 1.0f)
{
	std::random_device device;
	const unsigned int randomSeed = device();
	mEngine.seed(randomSeed);
	
	std::cout << "Randomly seeded the random generator with the seed: " << randomSeed << std::endl;
}

RandomGenerator::RandomGenerator(unsigned int pSeed)
	: mEngine(pSeed)
	, m01Distribution(0.0f, 1.0f)
{

}

float RandomGenerator::GetValue01()
{
	return m01Distribution(mEngine);
}
