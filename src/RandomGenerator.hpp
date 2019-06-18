#pragma once

#include <random>


class RandomGenerator
{
public:
	RandomGenerator();
	RandomGenerator(unsigned int pSeed);
	
	int Get(int pMin, int pMax);
	float Get(float pMin, float pMax);
	
private:
	std::mt19937 mEngine;
};
