#include "GameSystem.hpp"

#include "World.hpp"


GameSystem::GameSystem(const World& pWorld)
	: mWorld(&pWorld)
{
	
}

GameSystem::~GameSystem()
{
	
}

const World* GameSystem::GetWorld() const
{
	return mWorld;
}
