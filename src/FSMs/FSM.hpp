#pragma once

#include "FSMStateContainer.hpp"

#include <stack>
#include <string>
#include <unordered_map>
#include <vector>


class Entity;
class FSMState;

// This is the base class for all FSMs.
// Derived FSM types will only need to specify the initial state,
// 		as well as the transition logic of the state machine.
// 		This will be done by defining a set of transition rules,
// 		which specify the origin and destination states,
//		as well as the condition function that needs to return true
//		for the transition rule to fire.
// Similar to FSMStates, there will only exist one single instance
//		of a particular state machine, which will be shared by
//		all entities that use it. This optimizes memory costs,
//		as the transition logic data (and initial state) can be shared.
//		The only entity-specific data that needs to be stored
//		is the current state.
class FSM
{
private:
	struct FSMTransition
	{
		enum Type
		{
			Normal,
			Push,
			Pop
		};
		
		typedef std::function<bool(const Entity&)> Condition;
		
		Condition mCondition;
		const FSMState* mDestinationState;
		Type mType;
	};
	
public:
	FSM(const char* pName);
	virtual ~FSM();
	
	const std::string& GetName() const;
	
	void Load(const FSMStateContainer& pStateContainer);
	void Unload();
	
	void Activate(const Entity& pEntity);
	void Deactivate(const Entity& pEntity);
	void Resume(const Entity& pEntity);
	void Pause(const Entity& pEntity);
	void Update(const Entity& pEntity);
	
protected:
	virtual void OnLoad(const FSMStateContainer& pStateContainer) = 0;
	
	template<typename StateType>
	void SetInitialState(const FSMStateContainer& pStateContainer)
	{
		const FSMState& state = pStateContainer.GetState<StateType>();
		SetInitialState(state);
	}
	
	template<typename OriginStateType, typename DestinationStateType>
	void AddTransition(const FSMStateContainer& pStateContainer, const FSMTransition::Condition& pCondition)
	{
		const FSMState& originState = pStateContainer.GetState<OriginStateType>();
		const FSMState& destinationState = pStateContainer.GetState<DestinationStateType>();
		AddTransition(originState, &destinationState, FSMTransition::Type::Normal, pCondition);
	}
	
	template<typename OriginStateType, typename DestinationStateType>
	void AddPushTransition(const FSMStateContainer& pStateContainer, const FSMTransition::Condition& pCondition)
	{
		const FSMState& originState = pStateContainer.GetState<OriginStateType>();
		const FSMState& destinationState = pStateContainer.GetState<DestinationStateType>();
		AddTransition(originState, &destinationState, FSMTransition::Type::Push, pCondition);
	}
	
	template<typename OriginStateType>
	void AddPopTransition(const FSMStateContainer& pStateContainer, const FSMTransition::Condition& pCondition)
	{
		const FSMState& originState = pStateContainer.GetState<OriginStateType>();
		AddTransition(originState, nullptr, FSMTransition::Type::Pop, pCondition);
	}
	
private:
	void SetInitialState(const FSMState& pState);
	void AddTransition(const FSMState& pOriginState,
					   const FSMState* pDestinationState,
					   const FSMTransition::Type pType,
					   const FSMTransition::Condition& pCondition);
	
	bool UpdateTransitions(const Entity& pEntity, const FSMState& pCurrentState);
	void PerformTransition(const Entity& pEntity, const FSMTransition& pTransition);
	
	const std::stack<const FSMState*>& GetStateStack(const Entity& pEntity) const;
	const FSMState& GetCurrentState(const Entity& pEntity) const;
	
private:
	std::unordered_map<const FSMState*, std::vector<FSMTransition>> mTransitionsByCurrentState;
	std::unordered_map<int, std::stack<const FSMState*>> mStateStackByEntityID;
	std::string mName;
	const FSMState* mInitialState;
};
