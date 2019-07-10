#pragma once

#include "FSM.hpp"


class FSMRoot : public FSM
{
public:
	FSMRoot();
	
protected:
	void OnLoad(const FSMStateContainer& pStateContainer) override;
};
