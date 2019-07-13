#include "GameSystem.hpp"

#include "World.hpp"

#include <cassert>


GameSystem::GameSystem(const World& pWorld)
	: mWorld(&pWorld)
{
	
}

GameSystem::~GameSystem()
{
	
}

const World& GameSystem::GetWorld() const
{
	assert(mWorld != nullptr && "Tried to get world from game system but it was null.");
	return *mWorld;
}
