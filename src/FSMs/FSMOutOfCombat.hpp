#pragma once

#include "FSM.hpp"


class FSMStateContainer;

class FSMOutOfCombat : public FSM
{
public:
	FSMOutOfCombat();
	
protected:
	void OnLoad(const FSMStateContainer& pStateContainer) override;
};
