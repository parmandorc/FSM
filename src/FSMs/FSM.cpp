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

const std::string& FSM::GetName() const
{
	return mName;
}

void FSM::SetInitialState(const FSMState& pState)
{
	mInitialState = &pState;
}

void FSM::AddTransition(const FSMState& pOriginState,
						const FSMState* pDestinationState,
						const FSMTransition::Type pType,
						const FSMTransition::Condition& pCondition)
{
	if (pType != FSMTransition::Type::Pop)
	{
		assert(pDestinationState != nullptr &&
			   "Tried to add a transition with no destination state, but the type was not Pop");
		assert(&pOriginState != pDestinationState &&
			   "Tried to add a transition from a state to itself");
	}
	
	FSMTransition transition;
	transition.mCondition = pCondition;
	transition.mDestinationState = pDestinationState;
	transition.mType = pType;
	
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
	
	assert(mStateStackByEntityID.count(entityID) == 0 &&
		   "Tried to activate an FSM that was already active for the specified entity");
	assert(mInitialState != nullptr &&
		   "Tried to activate an FSM but no initial state had been set");
	mStateStackByEntityID[entityID].push(mInitialState);
	
	GetCurrentState(pEntity).Enter(pEntity);
}

void FSM::Deactivate(const Entity& pEntity)
{
	const int entityID = pEntity.GetID();
	
	std::cout << "Deactivating FSM '" << mName << "' for entity with ID: " << entityID << std::endl;
	
	GetCurrentState(pEntity).Exit(pEntity);

	mStateStackByEntityID.erase(entityID);
}

void FSM::Resume(const Entity& pEntity)
{
	const int entityID = pEntity.GetID();
	
	std::cout << "Resuming FSM '" << mName << "' for entity with ID: " << entityID << std::endl;
	
	assert(mStateStackByEntityID.count(entityID) == 1 &&
		   "Tried to resume an FSM but it had not been activated");
	
	GetCurrentState(pEntity).Resume(pEntity);
}

void FSM::Pause(const Entity& pEntity)
{
	const int entityID = pEntity.GetID();
	
	std::cout << "Pausing FSM '" << mName << "' for entity with ID: " << entityID << std::endl;
	
	GetCurrentState(pEntity).Pause(pEntity);
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
		assert(transition.mCondition &&
			   "Tried to check a transition from the current state but the condition was not valid");
		
		if (transition.mCondition(pEntity))
		{
			PerformTransition(pEntity, transition);
			return true;
		}
	}
	
	return false;
}

void FSM::PerformTransition(const Entity& pEntity, const FSMTransition& pTransition)
{
	if (pTransition.mType != FSMTransition::Type::Pop)
	{
		assert(pTransition.mDestinationState != nullptr &&
			   "Tried to transition to a state but it was null and the type was not Pop");
	}
	else
	{
		const std::stack<const FSMState*>& stateStack = GetStateStack(pEntity);
		assert(stateStack.size() > 1 &&
			   "Tried to perform a Pop transition but that would have left the state stack empty.");
	}
	
	const int entityID = pEntity.GetID();

	switch (pTransition.mType)
	{
		case FSMTransition::Type::Normal:
			GetCurrentState(pEntity).Exit(pEntity);
			mStateStackByEntityID[entityID].pop();
			mStateStackByEntityID[entityID].push(pTransition.mDestinationState);
			GetCurrentState(pEntity).Enter(pEntity);
			break;
			
		case FSMTransition::Type::Push:
			GetCurrentState(pEntity).Pause(pEntity);
			mStateStackByEntityID[entityID].push(pTransition.mDestinationState);
			GetCurrentState(pEntity).Enter(pEntity);
			break;
			
		case FSMTransition::Type::Pop:
			GetCurrentState(pEntity).Exit(pEntity);
			mStateStackByEntityID[entityID].pop();
			GetCurrentState(pEntity).Resume(pEntity);
			break;
			
		default:
			assert(false && "Unhandled transition type");
	}
}

const std::stack<const FSMState*>& FSM::GetStateStack(const Entity& pEntity) const
{
	const int entityID = pEntity.GetID();
	assert(mStateStackByEntityID.count(entityID) == 1 &&
		   "Tried to get state stack but FSM had not been activated");
	
	return mStateStackByEntityID.at(entityID);
}

const FSMState& FSM::GetCurrentState(const Entity& pEntity) const
{
	const std::stack<const FSMState*>& stateStack = GetStateStack(pEntity);
	assert(!stateStack.empty() &&
		   "Tried to get current state but state stack was empty");
	
	const FSMState* currentState = stateStack.top();
	assert(currentState != nullptr &&
		   "Tried to get current state but it was null");
	
	return *currentState;
}
