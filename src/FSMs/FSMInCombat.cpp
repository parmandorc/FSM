#include "FSMInCombat.hpp"

#include "Blackboard.hpp"
#include "Entity.hpp"
#include "FSMAttackState.hpp"
#include "FSMChaseState.hpp"


FSMInCombat::FSMInCombat()
	: FSM("InCombat")
{
	
}

void FSMInCombat::OnLoad(const FSMStateContainer& pStateContainer)
{
	SetInitialState<FSMAttackState>(pStateContainer);
	
	AddTransition<FSMAttackState, FSMChaseState>(pStateContainer, [](const Entity& pEntity)
	{
		// Start chasing when line of sight is lost
		int hasLineOfSight = 0;
		pEntity.GetBlackboard().Get("HasLOS", hasLineOfSight);
		return hasLineOfSight <= 0;
	});
	
	AddTransition<FSMChaseState, FSMAttackState>(pStateContainer, [](const Entity& pEntity)
	{
		// Start attacking again when line of sight is regained
		int hasLineOfSight = 0;
		pEntity.GetBlackboard().Get("HasLOS", hasLineOfSight);
		return hasLineOfSight > 0;
	});
}
