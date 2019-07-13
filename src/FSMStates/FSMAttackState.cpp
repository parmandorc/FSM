#include "FSMAttackState.hpp"

#include "Blackboard.hpp"
#include "Entity.hpp"

#include <iostream>


FSMAttackState::FSMAttackState()
	: FSMState("Attack")
{
	
}

void FSMAttackState::OnEnter(const Entity& pEntity) const
{
	Blackboard& blackboard = pEntity.GetBlackboard();
	
	int enemyID = -1;
	blackboard.Get("TargetEnemy", enemyID);
	
	blackboard.Set("IsAttacking", 0);
	
	std::cout << "Entity with ID: " << pEntity.GetID() << " started attacking enemy with ID: " << enemyID << "." << std::endl;
}

void FSMAttackState::OnExit(const Entity& pEntity) const
{
	pEntity.GetBlackboard().Clear("IsAttacking");
	
	std::cout << "Entity with ID: " << pEntity.GetID() << " stopped attacking its target enemy." << std::endl;
}
