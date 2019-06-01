#pragma once

#include <string>


class Entity;

class FSMState
{
public:
	FSMState(const char* pName);
	virtual ~FSMState();
	
	void Enter(const Entity& pEntity) const;
	void Exit(const Entity& pEntity) const;

	virtual void Update(const Entity& pEntity) const;
	
protected:
	virtual void OnEnter(const Entity& pEntity) const;
	virtual void OnExit(const Entity& pEntity) const;
	
private:
	std::string mName;
};
