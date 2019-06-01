#pragma once


class World;

class GameSystem
{
public:
	GameSystem(const World& pWorld);
	virtual ~GameSystem();
	
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update() = 0;
	
protected:
	const World* GetWorld() const;
	
private:
	const World* mWorld;
};
