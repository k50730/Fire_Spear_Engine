#pragma once
#include "GameObjectManager.h"
#include "XMLReader.h"

class SceneManager
{
public:
	SceneManager(GameObjectManager* g);
	~SceneManager();

	void LoadScene();
private:
	GameObjectManager* gameObjectManager;
};

