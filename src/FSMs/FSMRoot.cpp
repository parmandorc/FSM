#include "FSMRoot.hpp"

#include "Blackboard.hpp"
#include "Entity.hpp"
#include "FSMHierarchicalState.hpp"
#include "FSMInCombat.hpp"
#include "FSMOutOfCombat.hpp"


FSMRoot::FSMRoot()
	: FSM("Root")
{
	
}

void FSMRoot::OnLoad(const FSMStateContainer& pStateContainer)
{
	SetInitialState<FSMOutOfCombat>(pStateContainer);
	
	AddTransition<FSMOutOfCombat, FSMInCombat>(pStateContainer, [](const Entity& pEntity)
	{
		// Enter combat when there is a target enemy
		int enemyID = -1;
		return pEntity.GetBlackboard().Get("TargetEnemy", enemyID);
	});
	
	AddTransition<FSMInCombat, FSMOutOfCombat>(pStateContainer, [](const Entity& pEntity)
	{
		// Exit combat when there is a target enemy
		int enemyID = -1;
		return !pEntity.GetBlackboard().Get("TargetEnemy", enemyID);
	});
}
