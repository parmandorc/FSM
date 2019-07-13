#pragma once

#include "GameSystem.hpp"


class Entity;

class TargetingSystem : public GameSystem
{
public:
	TargetingSystem(const World& pWorld);
	
	void Load() override;
	void Unload() override;
	void Update() override;
	
private:
	void AddTargetEnemy(const Entity& pEntity) const;
	void RemoveTargetEnemy(const Entity& pEntity) const;
	
	void ToggleLineOfSight(const Entity& pEntity) const;
};
