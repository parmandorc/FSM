#include "World.hpp"

#include "Entity.hpp"

#include <iostream>
#include <cassert>


World::World()
{
	std::cout << "Creating world" << std::endl;
}

World::~World()
{
	std::cout << "Destroying world" << std::endl;
}

void World::Load()
{
	std::cout << "Loading world" << std::endl;
	
	LoadEntities();
}

void World::LoadEntities()
{
	static const unsigned int numberOfTotalEntities = 4;
	
	for (int i = 0; i < numberOfTotalEntities; i++)
		mEntityList.push_back(new Entity(i));
}

void World::Unload()
{
	std::cout << "Unloading world" << std::endl;
	
	UnloadEntities();
}

void World::UnloadEntities()
{
	for (Entity* entity : mEntityList)
		delete entity;
	
	mEntityList.clear();
}

void World::Update()
{
	std::cout << "Updating world" << std::endl;
}

unsigned int World::GetEntitiesCount() const
{
	return static_cast<unsigned int>(mEntityList.size());
}

const Entity& World::GetEntityByIndex(unsigned int pIndex) const
{
	assert(pIndex < GetEntitiesCount() && "Index out of bounds");
	return *mEntityList[pIndex];
}
