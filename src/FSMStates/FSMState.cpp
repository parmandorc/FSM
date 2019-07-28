#include "FSMState.hpp"

#include "Entity.hpp"

#include <iostream>


FSMState::FSMState(const char* pName)
	: mName(pName)
{
	std::cout << "Creating state: " << mName << std::endl;
}

FSMState::~FSMState()
{
	
}

void FSMState::Enter(const Entity& pEntity) const
{
	std::cout << "Entering state '" << mName << "' for entity with ID: " << pEntity.GetID() << std::endl;
	
	OnEnter(pEntity);
}

void FSMState::OnEnter(const Entity& pEntity) const
{

}

void FSMState::Exit(const Entity& pEntity) const
{
	std::cout << "Exiting state '" << mName << "' for entity with ID: " << pEntity.GetID() << std::endl;

	OnExit(pEntity);
}

void FSMState::OnExit(const Entity& pEntity) const
{
	
}

void FSMState::Resume(const Entity& pEntity) const
{
	std::cout << "Resuming state '" << mName << "' for entity with ID: " << pEntity.GetID() << std::endl;
	
	OnResume(pEntity);
}

void FSMState::OnResume(const Entity& pEntity) const
{
	OnEnter(pEntity);
}

void FSMState::Pause(const Entity& pEntity) const
{
	std::cout << "Pausing state '" << mName << "' for entity with ID: " << pEntity.GetID() << std::endl;
	
	OnPause(pEntity);
}

void FSMState::OnPause(const Entity& pEntity) const
{
	OnExit(pEntity);
}

void FSMState::Update(const Entity& pEntity) const
{
	
}
