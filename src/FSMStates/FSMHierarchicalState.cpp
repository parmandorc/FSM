#include "FSMHierarchicalState.hpp"

#include "FSM.hpp"

#include <string>


FSMHierarchicalState::FSMHierarchicalState(FSM& pFSM)
: FSMState(("Hierarchical (" + pFSM.GetName() + ")").c_str())
	, mFSM(&pFSM)
{
	
}

FSMHierarchicalState::~FSMHierarchicalState()
{
	mFSM = nullptr;
}

void FSMHierarchicalState::OnEnter(const Entity& pEntity) const
{
	mFSM->Activate(pEntity);
}

void FSMHierarchicalState::OnExit(const Entity& pEntity) const
{
	mFSM->Deactivate(pEntity);
}

void FSMHierarchicalState::Update(const Entity& pEntity) const
{
	mFSM->Update(pEntity);
}
