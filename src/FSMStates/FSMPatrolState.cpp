#include "FSMPatrolState.hpp"

#include "Blackboard.hpp"
#include "Entity.hpp"
#include "RandomGenerator.hpp"
#include "World.hpp"

#include <iostream>


static const char lFirstWaypoint = 'A';
static const char lLastWaypoint = 'Z';

FSMPatrolState::FSMPatrolState()
	: FSMState("Patrol")
{
	
}

void FSMPatrolState::OnEnter(const Entity &pEntity) const
{
	const int randomWaypointIndex = pEntity.GetWorld().GetRandomGenerator().Get((int)lFirstWaypoint, (int)lLastWaypoint);
	pEntity.GetBlackboard().Set("CurrentWaypoint", randomWaypointIndex);
	
	std::cout << "Entity with ID: " << pEntity.GetID() << " started patrolling towards waypoint '" << (char)randomWaypointIndex << "'." << std::endl;
}

void FSMPatrolState::Update(const Entity &pEntity) const
{
	// Reach the current waypoint by random chance
	if (pEntity.GetWorld().GetRandomGenerator().Get(0.0f, 1.0f) < 0.1f)
	{
		int currentWaypointIndex = -1;
		if (pEntity.GetBlackboard().Get("CurrentWaypoint", currentWaypointIndex))
		{
			std::cout << "Entity with ID: " << pEntity.GetID() << " reached waypoint '" << (char)currentWaypointIndex << "'." << std::endl;
		}
		
		pEntity.GetBlackboard().Clear("CurrentWaypoint");
	}
}

void FSMPatrolState::OnExit(const Entity &pEntity) const
{
	// Remember that the transition logic is define on the FSMs that use this state.
	// The intented (and current) use is to exit this state when reaching the current waypoint.
	// However, an FSM might define a different transition logic, so it is necessary
	// 		to stop following the current waypoint in case that happens.
	pEntity.GetBlackboard().Clear("CurrentWaypoint");
}

void FSMPatrolState::OnResume(const Entity& pEntity) const
{
	int currentWaypointIndex = -1;
	if (pEntity.GetBlackboard().Get("CurrentWaypoint", currentWaypointIndex))
	{
		std::cout << "Entity with ID: " << pEntity.GetID() << " continued patrolling towards waypoint '" << (char)currentWaypointIndex << "'." << std::endl;
	}
	else
	{
		// Fall back to choosing a new random waypoint if current waypoint is not available
		OnEnter(pEntity);
	}
}

void FSMPatrolState::OnPause(const Entity& pEntity) const
{
	// Do not clear the current waypoint so that the path to it can be resumed
}
