#include "FSM.hpp"

#include "Entity.hpp"
#include "FSMState.hpp"

#include <cassert>
#include <iostream>


FSM::FSM(const char* pName)
	: mName(pName)
	, mInitialState(nullptr)
{
	
}

FSM::~FSM()
{
	
}

void FSM::SetInitialState(const FSMState& pState)
{
	mInitialState = &pState;
}

void FSM::AddTransition(const FSMState& pOriginState, const FSMState& pDestinationState, const FSMTransition::Condition& pCondition)
{
	assert(&pOriginState != &pDestinationState && "Trying to add a transition from a state to itself");
	
	FSMTransition transition;
	transition.mCondition = pCondition;
	transition.mDestinationState = &pDestinationState;
	
	mTransitionsByCurrentState[&pOriginState].push_back(std::move(transition));
}

void FSM::Load(const FSMStateContainer& pStateContainer)
{
	std::cout << "Loading FSM: " << mName << std::endl;
	
	OnLoad(pStateContainer);
}

void FSM::Unload()
{
	std::cout << "Unloading FSM: " << mName << std::endl;

	mInitialState = nullptr;
	
	mTransitionsByCurrentState.clear();
}

void FSM::Activate(const Entity& pEntity)
{
	const int entityID = pEntity.GetID();
	
	std::cout << "Activating FSM '" << mName << "' for entity with ID: " << entityID << std::endl;
	
	assert(mCurrentStateByEntityID.count(entityID) == 0 && "Tried to activate an FSM that was already active for the specified entity");
	assert(mInitialState != nullptr && "Tried to activate an FSM but no initial state had been set");
	mCurrentStateByEntityID[entityID] = mInitialState;
	
	GetCurrentState(pEntity).Enter(pEntity);
}

void FSM::Deactivate(const Entity& pEntity)
{
	const int entityID = pEntity.GetID();
	
	std::cout << "Deactivating FSM '" << mName << "' for entity with ID: " << entityID << std::endl;
	
	GetCurrentState(pEntity).Exit(pEntity);

	mCurrentStateByEntityID.erase(entityID);
}

void FSM::Update(const Entity& pEntity)
{
	const FSMState& currentState = GetCurrentState(pEntity);
	
	if (UpdateTransitions(pEntity, currentState))
		return;
	
	currentState.Update(pEntity);
}

bool FSM::UpdateTransitions(const Entity& pEntity, const FSMState& pCurrentState)
{
	if (mTransitionsByCurrentState.count(&pCurrentState) == 0)
		return false;
	
	for (const FSMTransition& transition : mTransitionsByCurrentState[&pCurrentState])
	{
		assert(transition.mCondition && "Tried to check a transition from the current state but the condition was not valid");
		if (transition.mCondition(pEntity))
		{
			assert(transition.mDestinationState != nullptr && "Tried to transition to a state but it was null");
			TransitionTo(pEntity, *transition.mDestinationState);
			return true;
		}
	}
	
	return false;
}

void FSM::TransitionTo(const Entity& pEntity, const FSMState& pDestinationState)
{
	GetCurrentState(pEntity).Exit(pEntity);
	mCurrentStateByEntityID[pEntity.GetID()] = &pDestinationState;
	GetCurrentState(pEntity).Enter(pEntity);
}

const FSMState& FSM::GetCurrentState(const Entity& pEntity) const
{
	const int entityID = pEntity.GetID();
	assert(mCurrentStateByEntityID.count(entityID) == 1 && "Tried to get current state but FSM had not been activated");
	
	const FSMState* currentState = mCurrentStateByEntityID.at(entityID);
	assert(currentState != nullptr && "Tried to get current state but it was null");
	
	return *currentState;
}
