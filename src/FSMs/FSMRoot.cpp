#include "FSMRoot.hpp"

#include "Entity.hpp"
#include "FSMHierarchicalState.hpp"
#include "FSMInCombat.hpp"
#include "FSMOutOfCombat.hpp"
#include "RandomGenerator.hpp"
#include "World.hpp"


FSMRoot::FSMRoot()
	: FSM("Root")
{
	
}

void FSMRoot::OnLoad(const FSMStateContainer& pStateContainer)
{
	SetInitialState<FSMOutOfCombat>(pStateContainer);
	
	AddTransition<FSMOutOfCombat, FSMInCombat>(pStateContainer, [](const Entity& pEntity)
	{
		return pEntity.GetWorld().GetRandomGenerator().Get(0.0f, 1.0f) < 0.05f;
	});
	
	AddTransition<FSMInCombat, FSMOutOfCombat>(pStateContainer, [](const Entity& pEntity)
	{
		return pEntity.GetWorld().GetRandomGenerator().Get(0.0f, 1.0f) < 0.1f;
	});
}
