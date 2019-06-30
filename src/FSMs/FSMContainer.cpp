#include "FSMContainer.hpp"

#include "FSM.hpp"
#include "FSMOutOfCombat.hpp"

#include <cassert>
#include <iostream>


void FSMContainer::Load(const FSMStateContainer& pStateContainer)
{
	RegisterFSM<FSMOutOfCombat>(pStateContainer);
}

template<typename FSMType>
void FSMContainer::RegisterFSM(const FSMStateContainer& pStateContainer)
{
	const std::type_index typeIndex(typeid(FSMType));
	assert(mFSMsByType.count(typeIndex) == 0 && "Trying to register an FSM that had already been registered");
	mFSMsByType[typeIndex] = new FSMType();
	mFSMsByType[typeIndex]->Load(pStateContainer);
}

FSM& FSMContainer::GetFSMByType(const std::type_index& pType) const
{
	assert(mFSMsByType.count(pType) == 1 && "Trying to get an FSM that had not been registered");
	FSM* fsm = mFSMsByType.at(pType);
	assert(fsm != nullptr && "Trying to get an FSM but it was null");
	return *fsm;
}

void FSMContainer::Unload()
{
	std::cout << "Unloading FSMs" << std::endl;
	
	for (const auto& pair : mFSMsByType)
	{
		const FSM* fsm = pair.second;
		delete fsm;
	}
	
	mFSMsByType.clear();
}
