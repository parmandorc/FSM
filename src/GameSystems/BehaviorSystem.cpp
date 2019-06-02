#include "BehaviorSystem.hpp"

#include "Entity.hpp"
#include "FSMStateContainer.hpp"
#include "World.hpp"

#include <iostream>


BehaviorSystem::BehaviorSystem(const World& pWorld)
	: GameSystem(pWorld)
	, mStateContainer(new FSMStateContainer())
{
	
}

BehaviorSystem::~BehaviorSystem()
{
	delete mStateContainer;
	mStateContainer = nullptr;
}

void BehaviorSystem::Load()
{
	std::cout << "Loading behavior system" << std::endl;
	
	mStateContainer->Load();
}

void BehaviorSystem::Unload()
{
	std::cout << "Unloading behavior system" << std::endl;
	
	mStateContainer->Unload();
}

void BehaviorSystem::Update()
{
	const World* world = GetWorld();
	
	for (int i = 0; i < world->GetEntitiesCount(); i++)
	{
		const Entity& entity = world->GetEntityByIndex(i);
		
		std::cout << "Updating behavior for entity with ID: " << entity.GetID() << std::endl;
	}
}
