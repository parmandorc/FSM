#include "FSMOutOfCombat.hpp"

#include "Blackboard.hpp"
#include "Entity.hpp"
#include "FSMIdleState.hpp"
#include "FSMPatrolState.hpp"
#include "FSMUseObjectState.hpp"
#include "RandomGenerator.hpp"
#include "World.hpp"


FSMOutOfCombat::FSMOutOfCombat()
	: FSM("OutOfCombat")
{

}

void FSMOutOfCombat::OnLoad(const FSMStateContainer& pStateContainer)
{
	SetInitialState<FSMIdleState>(pStateContainer);
	
	AddTransition<FSMIdleState, FSMPatrolState>(pStateContainer, [](const Entity& pEntity)
	{
		return pEntity.GetWorld().GetRandomGenerator().Get(0.0f, 1.0f) < 0.2f;
	});
	
	AddTransition<FSMIdleState, FSMUseObjectState>(pStateContainer, [](const Entity& pEntity)
	{
		return pEntity.GetWorld().GetRandomGenerator().Get(0.0f, 1.0f) < 0.1f;
	});
	
	AddTransition<FSMPatrolState, FSMIdleState>(pStateContainer, [](const Entity& pEntity)
	{
		// Exit 'Patrol' state when the current waypoint was reached
		int currentWaypoint = -1;
		return !pEntity.GetBlackboard().Get("CurrentWaypoint", currentWaypoint);
	});
	
	AddTransition<FSMUseObjectState, FSMIdleState>(pStateContainer, [](const Entity& pEntity)
	{
		// Exit 'UseObject' state when the entity finished using the object
		int objectID = -1;
		return !pEntity.GetBlackboard().Get("CurrentObject", objectID);
	});
}
