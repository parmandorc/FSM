#pragma once

#include "GameSystem.hpp"


class FSM;
class FSMContainer;
class FSMStateContainer;
class World;

class BehaviorSystem : public GameSystem
{
public:
	BehaviorSystem(const World& pWorld);
	~BehaviorSystem();
	
	void Load() override;
	void Unload() override;
	void Update() override;
	
private:
	FSM* mRootFSM;
	FSMContainer* mFSMContainer;
	FSMStateContainer* mStateContainer;
};
