#include "FSMInCombat.hpp"

#include "Entity.hpp"
#include "FSMAttackState.hpp"
#include "FSMChaseState.hpp"
#include "RandomGenerator.hpp"
#include "World.hpp"


FSMInCombat::FSMInCombat()
	: FSM("InCombat")
{
	
}

void FSMInCombat::OnLoad(const FSMStateContainer& pStateContainer)
{
	SetInitialState<FSMAttackState>(pStateContainer);
	
	AddTransition<FSMAttackState, FSMChaseState>(pStateContainer, [](const Entity& pEntity)
	{
		return pEntity.GetWorld().GetRandomGenerator().Get(0.0f, 1.0f) < 0.2f;
	});
	
	AddTransition<FSMAttackState, FSMChaseState>(pStateContainer, [](const Entity& pEntity)
	{
		return pEntity.GetWorld().GetRandomGenerator().Get(0.0f, 1.0f) < 0.2f;
	});
}
