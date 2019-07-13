#pragma once

#include "FSMState.hpp"


class FSMAttackState : public FSMState
{
public:
	FSMAttackState();
	
protected:
	void OnEnter(const Entity& pEntity) const;
	void OnExit(const Entity& pEntity) const;
};
