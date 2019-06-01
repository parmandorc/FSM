#pragma once

#include <vector>


class Entity;

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
	
private:
	std::vector<Entity*> mEntityList;
};
