#pragma once
#include "GameObjectManager.h"
#include "XMLReader.h"
#include "tinyxml2.h"
class SceneManager
{
public:
	SceneManager(GameObjectManager* g);
	~SceneManager();

	tinyxml2::XMLError LoadScene(const char* path);
	tinyxml2::XMLError SaveScene(const char* path);

	void SetActive(int index);
private:
	std::vector<tinyxml2::XMLDocument*> scenes;
	GameObjectManager* gameObjectManager;
	XMLReader* xmlReader;
	void DeleteScene();
};

