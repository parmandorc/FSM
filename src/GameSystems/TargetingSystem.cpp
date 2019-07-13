#include "TargetingSystem.hpp"

#include "Blackboard.hpp"
#include "Entity.hpp"
#include "RandomGenerator.hpp"
#include "World.hpp"

#include <iostream>


TargetingSystem::TargetingSystem(const World& pWorld)
	: GameSystem(pWorld)
{
	
}

void TargetingSystem::Load()
{
	
}

void TargetingSystem::Unload()
{
	
}

void TargetingSystem::Update()
{
	const World& world = GetWorld();
	RandomGenerator& random = world.GetRandomGenerator();
	
	for (int i = 0; i < world.GetEntitiesCount(); i++)
	{
		const Entity& entity = world.GetEntityByIndex(i);
		Blackboard& blackboard = entity.GetBlackboard();
		
		int enemyID = -1;
		if (blackboard.Get("TargetEnemy", enemyID))
		{
			float chanceOfRemoval = 0.1f;
			
			int attackingValue = -1;
			if (blackboard.Get("IsAttacking", attackingValue))
			{
				chanceOfRemoval = 0.25f;
			}
			
			if (random.Get(0.0f, 1.0f) < chanceOfRemoval)
				RemoveTargetEnemy(entity);
		}
		else
		{
			if (random.Get(0.0f, 1.0f) < 0.05f)
				AddTargetEnemy(entity);
		}
	}
}

void TargetingSystem::AddTargetEnemy(const Entity& pEntity) const
{
	static const int maxEnemyCount = 100;
	const int enemyID = GetWorld().GetRandomGenerator().Get(0, maxEnemyCount - 1);
	
	pEntity.GetBlackboard().Set("TargetEnemy", enemyID);
}

void TargetingSystem::RemoveTargetEnemy(const Entity& pEntity) const
{
	Blackboard& blackboard = pEntity.GetBlackboard();
	
	int enemyID = -1;
	blackboard.Get("TargetEnemy", enemyID);

	int value = -1;
	if (blackboard.Get("IsAttacking", value))
	{
		std::cout << "Entity with ID: " << pEntity.GetID() << " killed its target enemy (ID: " << enemyID << ")." << std::endl;
	}
	else
	{
		std::cout << "Enemy with ID: " << enemyID << " escaped from entity with ID: " << pEntity.GetID() << "." << std::endl;
	}
	
	blackboard.Clear("TargetEnemy");
}
