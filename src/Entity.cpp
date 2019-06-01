#include "Entity.hpp"

#include <iostream>


Entity::Entity(int pID)
	: mID(pID)
{
	std::cout << "Creating entity with ID: " << mID << std::endl;
}

Entity::~Entity()
{
	std::cout << "Destoying entity with ID: " << mID << std::endl;
}

int Entity::GetID() const
{
	return mID;
}
