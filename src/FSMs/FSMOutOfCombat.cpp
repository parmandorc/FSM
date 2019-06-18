#include "FSMOutOfCombat.hpp"

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
		return pEntity.GetWorld().GetRandomGenerator().Get(0.0f, 1.0f) < 0.1f;
	});
	
	AddTransition<FSMUseObjectState, FSMIdleState>(pStateContainer, [](const Entity& pEntity)
	{
		return pEntity.GetWorld().GetRandomGenerator().Get(0.0f, 1.0f) < 0.3f;
	});
}