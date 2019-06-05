#include "BehaviorSystem.hpp"

#include "Entity.hpp"
#include "FSM.hpp"
#include "FSMOutOfCombat.hpp"
#include "FSMStateContainer.hpp"
#include "World.hpp"

#include <iostream>


BehaviorSystem::BehaviorSystem(const World& pWorld)
	: GameSystem(pWorld)
	, mStateContainer(new FSMStateContainer())
	, mMainFSM(nullptr)
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
	
	mMainFSM = new FSMOutOfCombat();
	mMainFSM->Load(*mStateContainer);
	
	const World* world = GetWorld();
	for (int i = 0; i < world->GetEntitiesCount(); i++)
	{
		const Entity& entity = world->GetEntityByIndex(i);
		mMainFSM->Activate(entity);
	}
}

void BehaviorSystem::Unload()
{
	std::cout << "Unloading behavior system" << std::endl;
	
	const World* world = GetWorld();
	for (int i = 0; i < world->GetEntitiesCount(); i++)
	{
		const Entity& entity = world->GetEntityByIndex(i);
		mMainFSM->Deactivate(entity);
	}
	
	mMainFSM->Unload();
	delete mMainFSM;
	mMainFSM = nullptr;
	
	mStateContainer->Unload();
}

void BehaviorSystem::Update()
{
	assert(mMainFSM != nullptr && "Tried to update behavior system but the main FSM was null");
	
	const World* world = GetWorld();
	for (int i = 0; i < world->GetEntitiesCount(); i++)
	{
		const Entity& entity = world->GetEntityByIndex(i);
		mMainFSM->Update(entity);
	}
}
