#include "BehaviorSystem.hpp"

#include "Entity.hpp"
#include "World.hpp"

#include <iostream>


BehaviorSystem::BehaviorSystem(const World& pWorld)
	: GameSystem(pWorld)
{
	
}

void BehaviorSystem::Load()
{
	std::cout << "Loading behavior system" << std::endl;
}

void BehaviorSystem::Unload()
{
	std::cout << "Unloading behavior system" << std::endl;
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
