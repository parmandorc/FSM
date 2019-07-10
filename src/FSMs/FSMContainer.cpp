#include "FSMContainer.hpp"

#include "FSM.hpp"
#include "FSMInCombat.hpp"
#include "FSMHierarchicalState.hpp"
#include "FSMOutOfCombat.hpp"
#include "FSMRoot.hpp"

#include <cassert>
#include <iostream>


void FSMContainer::Load(FSMStateContainer& pStateContainer)
{
	RegisterFSM<FSMInCombat>(pStateContainer);
	RegisterFSM<FSMOutOfCombat>(pStateContainer);
	RegisterFSM<FSMRoot>(pStateContainer);
	
	// Load FSMs after all types have been registered, as well as their Hierarchical proxy states,
	//		since they might be used during loading of some FSMs.
	for (const auto& pair : mFSMsByType)
	{
		FSM* fsm = pair.second;
		fsm->Load(pStateContainer);
	}
}

template<typename FSMType>
void FSMContainer::RegisterFSM(FSMStateContainer& pStateContainer)
{
	const std::type_index typeIndex(typeid(FSMType));
	assert(mFSMsByType.count(typeIndex) == 0 && "Trying to register an FSM that had already been registered");
	FSM* fsm = new FSMType();
	mFSMsByType[typeIndex] = fsm;

	pStateContainer.RegisterStateWithAlias<FSMHierarchicalState, FSMType>(*fsm);
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
