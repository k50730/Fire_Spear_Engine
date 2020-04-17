#pragma once
#include "tinyxml2.h"
#include "GameObject.h"
#include <string>
#include <list>
#include <iterator>
#include "GameObjectManager.h"

#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif

struct ObjectsReader 
{
	float positionX;
	float positionY;
	int ObjectID;
	float rotation;
	float colorR;
	float colorG;
	float colorB;
};

class XMLReader
{
public:
	tinyxml2::XMLError XMLLoad(tinyxml2::XMLDocument* xmlDoc, GameObjectManager* gameObjectManager);
	tinyxml2::XMLError XMLSave(const char* path, GameObjectManager* GameObjectManager);
	
	std::list<GameObject*> GameObjects;

private:
	void ReadComponentFromXML(GameObject* g, tinyxml2::XMLElement* c);
	void ReadTransformProperties(GameObject* g, tinyxml2::XMLElement* c);
	void ReadRenderProperties(GameObject* g, tinyxml2::XMLElement* c);
	void ReadRigidbodyProperties(GameObject* g, tinyxml2::XMLElement* c);

	void SaveComponentToXML(GameObject* g, tinyxml2::XMLElement* e);
	void SaveTransformProperties(GameObject* g, tinyxml2::XMLDocument* xDoc, tinyxml2::XMLElement* e);
	void SaveRenderProperties(GameObject* g, tinyxml2::XMLDocument* xDoc, tinyxml2::XMLElement* e);
	void SaveRigidbodyProperties(GameObject* g, tinyxml2::XMLDocument* xDoc, tinyxml2::XMLElement* e);
};



