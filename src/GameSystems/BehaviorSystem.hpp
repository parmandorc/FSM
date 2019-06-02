#pragma once

#include "GameSystem.hpp"


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
	FSMStateContainer* mStateContainer;
};
