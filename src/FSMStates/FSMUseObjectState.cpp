#include "FSMUseObjectState.hpp"

#include "Blackboard.hpp"
#include "Entity.hpp"
#include "RandomGenerator.hpp"
#include "World.hpp"

#include <iostream>


static const int lMaxObjectID = 100;
static const int lMinInteractionDuration = 3;
static const int lMaxInteractionDuration = 10;

FSMUseObjectState::FSMUseObjectState()
	: FSMState("UseObject")
{
	
}

void FSMUseObjectState::OnEnter(const Entity &pEntity) const
{
	RandomGenerator& randomGenerator = pEntity.GetWorld().GetRandomGenerator();
	const int objectID = randomGenerator.Get(0, lMaxObjectID);
	const int interactionDuration = randomGenerator.Get(lMinInteractionDuration, lMaxInteractionDuration);
	
	pEntity.GetBlackboard().Set("CurrentObject", objectID);
	pEntity.GetBlackboard().Set("RemainingInteractionTime", interactionDuration);
	
	std::cout << "Entity with ID: " << pEntity.GetID() << " started using object with ID: " << objectID << ". The interaction will take a duration of " << interactionDuration << "." << std::endl;
}

void FSMUseObjectState::Update(const Entity &pEntity) const
{
	int remainingInteractionTime = -1;
	if (pEntity.GetBlackboard().Get("RemainingInteractionTime", remainingInteractionTime))
	{
		remainingInteractionTime--;
		pEntity.GetBlackboard().Set("RemainingInteractionTime", remainingInteractionTime);
		
		if (remainingInteractionTime <= 0)
		{
			int objectID = -1;
			pEntity.GetBlackboard().Get("CurrentObject", objectID);
			
			pEntity.GetBlackboard().Clear("CurrentObject");
			
			std::cout << "Entity with ID: " << pEntity.GetID() << " finished using object with ID: " << objectID << "." << std::endl;
		}
	}
}

void FSMUseObjectState::OnExit(const Entity &pEntity) const
{
	pEntity.GetBlackboard().Clear("CurrentObject");
	pEntity.GetBlackboard().Clear("RemainingInteractionTime");
}
