#pragma once
#include "tinyxml2.h"
#include "GameObject.h"
#include <string>
#include <list>
#include <iterator>
using namespace tinyxml2;

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
	XMLError XMLLoad(const char* path);
	XMLError XMLSave(const char* path, std::list<GameObject> GameObjects);
	

	std::list<GameObject> GameObjects;
	//GameObject gameObjects[];
};



