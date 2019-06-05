#include "World.hpp"

#include "BehaviorSystem.hpp"
#include "Entity.hpp"
#include "GameSystem.hpp"
#include "RandomGenerator.hpp"

#include <cassert>
#include <iostream>


World::World()
{
	std::cout << "Creating world" << std::endl;
	
	mRandomGenerator = new RandomGenerator();
}

World::~World()
{
	std::cout << "Destroying world" << std::endl;
	
	delete mRandomGenerator;
	mRandomGenerator = nullptr;
}

void World::Load()
{
	std::cout << "Loading world" << std::endl;
	
	LoadEntities();
	LoadGameSystems();
}

void World::LoadEntities()
{
	std::cout << "Loading entities" << std::endl;
	
	static const unsigned int numberOfTotalEntities = 4;
	
	for (int i = 0; i < numberOfTotalEntities; i++)
		mEntityList.push_back(new Entity(*this, i));
}

void World::LoadGameSystems()
{
	std::cout << "Loading game systems" << std::endl;
	
	// This defines the order of execution
	mGameSystemList.push_back(new BehaviorSystem(*this));
	
	for (GameSystem* system : mGameSystemList)
		system->Load();
}

void World::Unload()
{
	std::cout << "Unloading world" << std::endl;
	
	UnloadGameSystems();
	UnloadEntities();
}

void World::UnloadEntities()
{
	std::cout << "Unloading entities" << std::endl;
	
	for (Entity* entity : mEntityList)
		delete entity;
	
	mEntityList.clear();
}

void World::UnloadGameSystems()
{
	std::cout << "Unloading game systems" << std::endl;
	
	for (GameSystem* system : mGameSystemList)
	{
		system->Unload();
		delete system;
	}
	
	mGameSystemList.clear();
}

void World::Update()
{
	std::cout << "Updating world" << std::endl;
	
	for (GameSystem* system : mGameSystemList)
		system->Update();
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

RandomGenerator& World::GetRandomGenerator() const
{
	assert(mRandomGenerator != nullptr && "Tried to get random generator but it was null");
	return *mRandomGenerator;
}
