#include "FSMStateContainer.hpp"

#include "FSMState.hpp"

#include <cassert>
#include <iostream>


void FSMStateContainer::Load()
{
	std::cout << "Registering states" << std::endl;
}

template<typename StateType>
void FSMStateContainer::RegisterState()
{
	const std::type_index typeIndex(typeid(StateType));
	assert(mStatesByType.count(typeIndex) == 0 && "Trying to register a state that had already been registered");
	mStatesByType[typeIndex] = new StateType();
}

const FSMState& FSMStateContainer::GetStateByType(const std::type_index& pType) const
{
	assert(mStatesByType.count(pType) == 1 && "Trying to get a state that had not been registered");
	const FSMState* state = mStatesByType.at(pType);
	assert(state != nullptr && "Trying to get a state but it was null");
	return *mStatesByType.at(pType);
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
