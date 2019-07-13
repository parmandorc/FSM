#pragma once

#include "FSMState.hpp"


class FSMChaseState : public FSMState
{
public:
	FSMChaseState();
	
protected:
	void OnEnter(const Entity& pEntity) const;
	void OnExit(const Entity& pEntity) const;
};
