#pragma once
#include "GameObjectManager.h"
#include "ScriptComponent.h"

class ScriptingSystem
{
public:
	ScriptingSystem(GameObjectManager* g);
	~ScriptingSystem();

	void Awake();
	void Start();
	void Update(sf::Time dt);
private:
	GameObjectManager* gameObjectManager;
};

