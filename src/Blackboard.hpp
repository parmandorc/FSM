#pragma once

#include <string>
#include <unordered_map>


// For simplicity, values for the blackboard entries will only be integers.
// In a final implementation, entries should be able to have multiple (or any) types.
class Blackboard
{
public:
	bool Get(const char* pKey, int& oValue) const;
	void Set(const char* pKey, int pValue);
	void Clear(const char* pKey);
	
private:
	std::unordered_map<std::string, int> mEntries;
};
