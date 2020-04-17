#include "SceneManager.h"

SceneManager::SceneManager(GameObjectManager* g)
{
	xmlReader = new XMLReader();
	gameObjectManager = g;
}

SceneManager::~SceneManager()
{
	for (auto s : scenes)
	{
		delete s;
	}

	scenes.clear();
}

tinyxml2::XMLError SceneManager::LoadScene(const char* path)
{
	tinyxml2::XMLDocument* xmlDoc = new tinyxml2::XMLDocument();

	// Check if the file load correctly
	tinyxml2::XMLError eResult = xmlDoc->LoadFile(path);

	if (eResult != tinyxml2::XML_SUCCESS)
	{
		printf("Fail to load file: %s\n", path);
		throw std::runtime_error("Fail to load file");
	}

	scenes.push_back(xmlDoc);
}

tinyxml2::XMLError SceneManager::SaveScene(const char* path)
{
	return xmlReader->XMLSave(path, gameObjectManager);
}
void SceneManager::SetActive(int index)
{
	DeleteScene();

	if(index < scenes.size())
	xmlReader->XMLLoad(scenes[index], gameObjectManager);
	else
	{
		printf("Fail to load scene at index: %s\n", index);
		throw std::runtime_error("Fail to load scene");
	}
}

void SceneManager::DeleteScene()
{
	gameObjectManager->DeleteAllGameObjects();
}

