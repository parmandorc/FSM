#include "Entity.hpp"

#include "Blackboard.hpp"

#include <cassert>
#include <iostream>


Entity::Entity(const World& pWorld, int pID)
	: mWorld(&pWorld)
	, mID(pID)
{
	std::cout << "Creating entity with ID: " << mID << std::endl;
	
	mBlackboard = new Blackboard();
}

Entity::~Entity()
{
	std::cout << "Destoying entity with ID: " << mID << std::endl;
	
	delete mBlackboard;
	mBlackboard = nullptr;
}

Blackboard& Entity::GetBlackboard() const
{
	assert(mBlackboard != nullptr && "Tried to get blackboard from entity but it was null");
	return *mBlackboard;
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
