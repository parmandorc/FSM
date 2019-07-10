#pragma once

#include <typeindex>
#include <unordered_map>
#include <utility>


class FSMState;

// This container class allows having one single shared instance for each FSMState,
// 		which optimizes memory costs regardless of the number of entities that use
//		that state or the number of FSMs it is used in.
class FSMStateContainer
{
public:
	void Load();
	void Unload();
	
	template<typename StateType>
	const FSMState& GetState() const
	{
		const std::type_index typeIndex(typeid(StateType));
		return GetStateByType(typeIndex);
	}
	
	template<typename StateType, typename AliasType, typename ... Args>
	void RegisterStateWithAlias(Args&&... pArgs)
	{
		const FSMState* state = new StateType(std::forward<Args>(pArgs)...);
		const std::type_index typeIndex(typeid(AliasType));
		RegisterState(*state, typeIndex);
	}
	
private:
	const FSMState& GetStateByType(const std::type_index& pType) const;
	
	template<typename StateType>
	void RegisterState();
	
	void RegisterState(const FSMState& pState, const std::type_index& pTypeIndex);
	
private:
	std::unordered_map<std::type_index, const FSMState*> mStatesByType;
};
