#pragma once


class Blackboard;
class World;

class Entity
{
public:
	Entity(const World& pWorld, int pID);
	virtual ~Entity();
	
	Blackboard& GetBlackboard() const;
	const World& GetWorld() const;
	int GetID() const;
	
private:
	Blackboard* mBlackboard;
	const World* mWorld;
	int mID;
};
