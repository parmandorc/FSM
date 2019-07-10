#include "BehaviorSystem.hpp"

#include "Entity.hpp"
#include "FSM.hpp"
#include "FSMContainer.hpp"
#include "FSMRoot.hpp"
#include "FSMStateContainer.hpp"
#include "World.hpp"

#include <iostream>


BehaviorSystem::BehaviorSystem(const World& pWorld)
	: GameSystem(pWorld)
	, mFSMContainer(new FSMContainer())
	, mStateContainer(new FSMStateContainer())
	, mRootFSM(nullptr)
{
	
}

BehaviorSystem::~BehaviorSystem()
{
	delete mFSMContainer;
	mFSMContainer = nullptr;
	
	delete mStateContainer;
	mStateContainer = nullptr;
}

void BehaviorSystem::Load()
{
	std::cout << "Loading behavior system" << std::endl;
	
	mStateContainer->Load();
	
	// Load FSMs after States have been loaded
	mFSMContainer->Load(*mStateContainer);
	
	mRootFSM = &mFSMContainer->GetFSM<FSMRoot>();
	
	const World* world = GetWorld();
	for (int i = 0; i < world->GetEntitiesCount(); i++)
	{
		const Entity& entity = world->GetEntityByIndex(i);
		mRootFSM->Activate(entity);
	}
}

void BehaviorSystem::Unload()
{
	std::cout << "Unloading behavior system" << std::endl;
	
	const World* world = GetWorld();
	for (int i = 0; i < world->GetEntitiesCount(); i++)
	{
		const Entity& entity = world->GetEntityByIndex(i);
		mRootFSM->Deactivate(entity);
	}
	
	mRootFSM = nullptr;
	mFSMContainer->Unload();
	mStateContainer->Unload();
}

void BehaviorSystem::Update()
{
	assert(mRootFSM != nullptr && "Tried to update behavior system but the root FSM was null");
	
	const World* world = GetWorld();
	for (int i = 0; i < world->GetEntitiesCount(); i++)
	{
		const Entity& entity = world->GetEntityByIndex(i);
		mRootFSM->Update(entity);
	}
}
