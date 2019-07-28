#pragma once

#include <string>


class Entity;

// This is the base class for all states to be used by the FSMs
// Since only one single instance exists of each state, which is shared by
// 		all entities, the derived state objects themselves should remain state-less.
//		All functions that drive state logic receive a reference to the
//		entity that is being updated, so that any entity-specific state
//		data can be saved in the entity itself (or its blackboard).
class FSMState
{
public:
	FSMState(const char* pName);
	virtual ~FSMState();
	
	void Enter(const Entity& pEntity) const;
	void Exit(const Entity& pEntity) const;
	
	void Resume(const Entity& pEntity) const;
	void Pause(const Entity& pEntity) const;

	virtual void Update(const Entity& pEntity) const;
	
protected:
	virtual void OnEnter(const Entity& pEntity) const;
	virtual void OnExit(const Entity& pEntity) const;
	
	// If these are not overridden, the normal transition callbacks will be executed by default
	virtual void OnResume(const Entity& pEntity) const;
	virtual void OnPause(const Entity& pEntity) const;
	
private:
	std::string mName;
};
