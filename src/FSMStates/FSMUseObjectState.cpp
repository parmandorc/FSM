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
	const bool isInteractionResumable = randomGenerator.Get(0.0f, 1.0f) < 0.5f;
	
	Blackboard& blackboard = pEntity.GetBlackboard();
	blackboard.Set("CurrentObject", objectID);
	blackboard.Set("InteractionDuration", interactionDuration);
	blackboard.Set("RemainingInteractionTime", interactionDuration);
	blackboard.Set("IsInteractionResumable", isInteractionResumable ? 1 : 0);
	
	std::cout << "Entity with ID: " << pEntity.GetID() << " started using object with ID: " << objectID << ". The interaction will take a duration of " << interactionDuration << "." << std::endl;
}

void FSMUseObjectState::Update(const Entity &pEntity) const
{
	Blackboard& blackboard = pEntity.GetBlackboard();

	int remainingInteractionTime = -1;
	if (blackboard.Get("RemainingInteractionTime", remainingInteractionTime))
	{
		remainingInteractionTime--;
		blackboard.Set("RemainingInteractionTime", remainingInteractionTime);
		
		if (remainingInteractionTime <= 0)
		{
			int objectID = -1;
			blackboard.Get("CurrentObject", objectID);
			
			blackboard.Clear("CurrentObject");
			
			std::cout << "Entity with ID: " << pEntity.GetID() << " finished using object with ID: " << objectID << "." << std::endl;
		}
	}
}

void FSMUseObjectState::OnExit(const Entity &pEntity) const
{
	Blackboard& blackboard = pEntity.GetBlackboard();
	blackboard.Clear("CurrentObject");
	blackboard.Clear("InteractionDuration");
	blackboard.Clear("RemainingInteractionTime");
	blackboard.Clear("IsInteractionResumable");
}

void FSMUseObjectState::OnResume(const Entity& pEntity) const
{
	Blackboard& blackboard = pEntity.GetBlackboard();
	int objectID = -1;
	if (blackboard.Get("CurrentObject", objectID))
	{
		int interactionDuration = -1;
		int remainingInteractionTime = -1;
		int isInteractionResumable = -1;
		if (blackboard.Get("InteractionDuration", interactionDuration) &&
			blackboard.Get("RemainingInteractionTime", remainingInteractionTime) &&
			blackboard.Get("IsInteractionResumable", isInteractionResumable))
		{
			if (isInteractionResumable > 0)
			{
				std::cout << "Entity with ID: " << pEntity.GetID() << " resumed the interaction with object with ID: " << objectID << ". The interaction has a remaining duration of " << remainingInteractionTime << "." << std::endl;
			}
			else
			{
				std::cout << "Entity with ID: " << pEntity.GetID() << " restarted the interaction with object with ID: " << objectID << ". The interaction will take a duration of " << interactionDuration << "." << std::endl;
				
				blackboard.Set("RemainingInteractionTime", interactionDuration);
			}
		}
		else
		{
			std::cout << "Entity with ID: " << pEntity.GetID() << " was not able to resume the interaction with object with ID: " << objectID << ", so it was aborted." << std::endl;
			
			blackboard.Clear("CurrentObject");
		}
	}
	else
	{
		std::cout << "Entity with ID: " << pEntity.GetID() << " was not able to resume the interaction since it had already been completed." << std::endl;
	}
}

void FSMUseObjectState::OnPause(const Entity& pEntity) const
{
	// Do not clear the information about the current object so the interaction can be resumed
}
