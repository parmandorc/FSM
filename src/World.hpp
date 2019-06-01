#pragma once

#include <vector>


class Entity;
class GameSystem;

class World
{
public:
	World();
	~World();
	
	void Load();
	void Unload();
	void Update();
	
	unsigned int GetEntitiesCount() const;
	const Entity& GetEntityByIndex(unsigned int pIndex) const;
	
private:
	void LoadEntities();
	void UnloadEntities();
	
	void LoadGameSystems();
	void UnloadGameSystems();
	
private:
	std::vector<Entity*> mEntityList;
	std::vector<GameSystem*> mGameSystemList;
};
