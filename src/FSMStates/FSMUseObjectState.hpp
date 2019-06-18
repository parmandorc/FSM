#pragma once

#include "FSMState.hpp"


class FSMUseObjectState : public FSMState
{
public:
	FSMUseObjectState();
	
	void Update(const Entity& pEntity) const override;
	
protected:
	void OnEnter(const Entity& pEntity) const override;
	void OnExit(const Entity& pEntity) const override;
};
