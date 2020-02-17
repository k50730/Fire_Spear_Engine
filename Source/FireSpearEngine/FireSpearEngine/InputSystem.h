#pragma once
#include <string>
#include "GameObjectManager.h"

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

public:
    static bool GetKeyDown(const char* Key);
	static std::map<std::string, sf::Keyboard::Key> KeyCode;
};