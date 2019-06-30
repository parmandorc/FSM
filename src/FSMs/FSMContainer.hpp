#pragma once

#include <typeindex>
#include <unordered_map>

class FSM;
class FSMStateContainer;

// This container class allows having one single shared instance for each FSM,
// 		which optimizes memory costs regardless of the number of entities that use it
class FSMContainer
{
public:
	void Load(const FSMStateContainer& pStateContainer);
	void Unload();
	
	template<typename FSMType>
	FSMType& GetFSM() const
	{
		const std::type_index typeIndex(typeid(FSMType));
		return static_cast<FSMType&>(GetFSMByType(typeIndex));
	}
	
private:
	FSM& GetFSMByType(const std::type_index& pType) const;
	
	template<typename FSMType>
	void RegisterFSM(const FSMStateContainer& pStateContainer);
	
private:
	std::unordered_map<std::type_index, FSM*> mFSMsByType;
};
