#pragma once
#include "GameObjectManager.h"
#include "InputComponent.h"

class InputSystem
{
public:
	InputSystem(GameObjectManager* g);
	~InputSystem();
	
	void Instantiate();
	void Awake();
	void Start();
	void Update(sf::Time dt);
private:
	GameObjectManager* gameObjectManager;
};