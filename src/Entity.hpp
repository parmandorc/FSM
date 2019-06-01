#pragma once


class Entity
{
public:
	Entity(int pID);
	virtual ~Entity();
	
	int GetID() const;
	
private:	
	int mID;
};
