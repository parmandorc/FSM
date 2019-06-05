#include "Entity.hpp"

#include <cassert>
#include <iostream>


Entity::Entity(const World& pWorld, int pID)
	: mWorld(&pWorld)
	, mID(pID)
{
	std::cout << "Creating entity with ID: " << mID << std::endl;
}

Entity::~Entity()
{
	std::cout << "Destoying entity with ID: " << mID << std::endl;
}

const World& Entity::GetWorld() const
{
	assert(mWorld != nullptr && "Tried to get world from entity but it was null");
	return *mWorld;
}

int Entity::GetID() const
{
	return mID;
}
