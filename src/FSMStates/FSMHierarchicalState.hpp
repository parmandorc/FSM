#pragma once

#include "FSMState.hpp"


class FSM;

// 	This class acts as a wrapper or proxy on an FSM in order to
//		enable the implementation of a Hierarchical FSM, by
//		making it possible to use an FSM as a "state" of another FSM.
class FSMHierarchicalState : public FSMState
{
public:
	FSMHierarchicalState(FSM& pFSM);
	~FSMHierarchicalState();
	
	void Update(const Entity& pEntity) const override;
	
protected:
	void OnEnter(const Entity& pEntity) const override;
	void OnExit(const Entity& pEntity) const override;
	void OnResume(const Entity& pEntity) const override;
	void OnPause(const Entity& pEntity) const override;
	
private:
	FSM* mFSM;
};
