#include "FSMChaseState.hpp"

#include "Blackboard.hpp"
#include "Entity.hpp"

#include <iostream>


FSMChaseState::FSMChaseState()
	: FSMState("Chase")
{
	
}

void FSMChaseState::OnEnter(const Entity& pEntity) const
{
	int enemyID = -1;
	pEntity.GetBlackboard().Get("TargetEnemy", enemyID);
	
	std::cout << "Entity with ID: " << pEntity.GetID() << " started chasing enemy with ID: " << enemyID << "." << std::endl;
}

void FSMChaseState::OnExit(const Entity& pEntity) const
{
	std::cout << "Entity with ID: " << pEntity.GetID() << " stopped chasing its target enemy." << std::endl;
}
