#pragma once

#include "GameSystem.hpp"


class World;

class BehaviorSystem : public GameSystem
{
public:
	BehaviorSystem(const World& pWorld);
	
	void Load() override;
	void Unload() override;
	void Update() override;
};
