#include "GameObjectManager.h"

int GameObjectManager::nextObjectID = 0;

GameObjectManager::~GameObjectManager()
{
	for (const auto& p : gameObjects)
	{
		delete p.second;
	}
	gameObjects.clear();
	
}

GameObject* GameObjectManager::CreateObject()
{
	GameObject* newObj = new GameObject(nextObjectID++);
	gameObjects[newObj->GetID()] = newObj;
	//std::cout << "DEBUG: NUMBER OF GAMEOBJECTS: " << nextObjectID << std::endl;
	return newObj;
}

void GameObjectManager::DestroyObject(GameObject* o)
{
	for (int i = 0; i < o->GetChildren().size(); i++)
	{
		gameObjects.erase(o->GetChildren()[i]->GetID());
	}

	gameObjects.erase(o->GetID());
}

void GameObjectManager::Awake()
{
	for (std::map<int, GameObject*>::iterator i = gameObjects.begin(); i != gameObjects.end(); ++i) 
	{
		(i->second)->Awake();
	}
}

void GameObjectManager::Start()
{
	for (std::map<int, GameObject*>::iterator i = gameObjects.begin(); i != gameObjects.end(); ++i)
	{
		(i->second)->Start();
	}
}

void GameObjectManager::Update(sf::Time msec)
{
	for (std::map<int, GameObject*>::iterator i = gameObjects.begin(); i != gameObjects.end(); ++i) 
	{
		(i->second)->Update(msec);
	}
}

void GameObjectManager::LateUpdate(sf::Time msec)
{
	for (std::map<int, GameObject*>::iterator i = gameObjects.begin(); i != gameObjects.end(); ++i) 
	{
		(i->second)->LateUpdate(msec);
	}
}

std::vector<GameObject*> GameObjectManager::DrawableObjects()
{
	std::vector<GameObject*> drawableObjects;
	for (const auto& p : gameObjects)
	{
		if (p.second->GetComponent<RenderComponent*>() != nullptr)
		{
			drawableObjects.push_back(p.second);
		}
	}

	return drawableObjects;
}

void GameObjectManager::DeleteAllGameObjects()
{
	for (auto g : gameObjects)
	{
		//std::cout << "DEBUG: DELETE GAMEOBJECT ID:" << g.second->GetID() << std::endl;
		delete g.second;
	}
	//std::cout << "DEBUG: DELETE ALL GAMEOBJECTS" << std::endl;
	gameObjects.clear();
	nextObjectID = 0;
}


