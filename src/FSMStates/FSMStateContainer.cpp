#include "FSMStateContainer.hpp"

#include "FSMAttackState.hpp"
#include "FSMChaseState.hpp"
#include "FSMIdleState.hpp"
#include "FSMPatrolState.hpp"
#include "FSMState.hpp"
#include "FSMUseObjectState.hpp"

#include <cassert>
#include <iostream>


void FSMStateContainer::Load()
{
	std::cout << "Registering states" << std::endl;
	
	RegisterState<FSMAttackState>();
	RegisterState<FSMChaseState>();
	RegisterState<FSMIdleState>();
	RegisterState<FSMPatrolState>();
	RegisterState<FSMUseObjectState>();
}

template<typename StateType>
void FSMStateContainer::RegisterState()
{
	RegisterStateWithAlias<StateType, StateType>();
}

void FSMStateContainer::RegisterState(const FSMState& pState, const std::type_index& pTypeIndex)
{
	assert(mStatesByType.count(pTypeIndex) == 0 && "Trying to register a state that had already been registered");
	mStatesByType[pTypeIndex] = &pState;
}

const FSMState& FSMStateContainer::GetStateByType(const std::type_index& pType) const
{
	assert(mStatesByType.count(pType) == 1 && "Trying to get a state that had not been registered");
	const FSMState* state = mStatesByType.at(pType);
	assert(state != nullptr && "Trying to get a state but it was null");
	return *state;
}

void FSMStateContainer::Unload()
{
	std::cout << "Unloading states" << std::endl;
	
	for (const auto& pair : mStatesByType)
	{
		const FSMState* state = pair.second;
		delete state;
	}

	mStatesByType.clear();
}
