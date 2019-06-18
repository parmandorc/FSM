#include "Blackboard.hpp"


bool Blackboard::Get(const char* pKey, int& oValue) const
{
	if (mEntries.count(pKey) == 0)
		return false;
	
	oValue = mEntries.at(pKey);
	return true;
}

void Blackboard::Set(const char* pKey, int pValue)
{
	mEntries[pKey] = pValue;
}

void Blackboard::Clear(const char* pKey)
{
	mEntries.erase(pKey);
}
