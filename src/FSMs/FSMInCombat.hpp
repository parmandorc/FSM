#pragma once

#include "FSM.hpp"


class FSMInCombat : public FSM
{
public:
	FSMInCombat();
	
protected:
	void OnLoad(const FSMStateContainer& pStateContainer) override;
};
