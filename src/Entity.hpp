#pragma once


class World;

class Entity
{
public:
	Entity(const World& pWorld, int pID);
	virtual ~Entity();
	
	const World& GetWorld() const;
	
	int GetID() const;
	
private:
	const World* mWorld;
	int mID;
};
