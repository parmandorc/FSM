#pragma once

#include <random>


class RandomGenerator
{
public:
	RandomGenerator();
	RandomGenerator(unsigned int pSeed);
	
	float GetValue01();
	
private:
	std::mt19937 mEngine;
	std::uniform_real_distribution<float> m01Distribution;
};
