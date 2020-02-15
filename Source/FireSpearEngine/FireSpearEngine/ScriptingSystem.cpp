#include "ScriptingSystem.h"

ScriptingSystem::ScriptingSystem(GameObjectManager* g)
{
	gameObjectManager = g;
}

ScriptingSystem::~ScriptingSystem()
{
}

void ScriptingSystem::Awake()
{
}

void ScriptingSystem::Start()
{
    for (std::map<int, GameObject*>::iterator i = gameObjectManager->gameObjects.begin(); i != gameObjectManager->gameObjects.end(); ++i)
    {
        if ((i->second)->GetComponent<ScriptComponent*>() != nullptr)
        {
            (i->second)->GetComponent<ScriptComponent*>()->owner = i->second;
        }
    }
}

void ScriptingSystem::Update(sf::Time dt)
{
}
