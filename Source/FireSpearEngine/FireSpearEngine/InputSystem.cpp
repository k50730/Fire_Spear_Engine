#include "InputSystem.h"

InputSystem::InputSystem(GameObjectManager* g)
{
	gameObjectManager = g;
}

InputSystem::~InputSystem()
{
}

void InputSystem::Instantiate()
{
	for (std::map<int, GameObject*>::iterator i = gameObjectManager->gameObjects.begin(); i != gameObjectManager->gameObjects.end(); ++i)
	{
		if ((i->second)->GetComponent<InputComponent*>() != nullptr)
		{
			(i->second)->GetComponent<InputComponent*>()->owner = i->second;
		}
	}
}

void InputSystem::Awake()
{
}

void InputSystem::Start()
{
}

void InputSystem::Update(sf::Time dt)
{
	for (std::map<int, GameObject*>::iterator i = gameObjectManager->gameObjects.begin(); i != gameObjectManager->gameObjects.end(); ++i)
	{
		if ((i->second)->GetComponent<InputComponent*>() != nullptr)
		{
			(i->second)->GetComponent<InputComponent*>()->Update(dt);
		}
	}
}
