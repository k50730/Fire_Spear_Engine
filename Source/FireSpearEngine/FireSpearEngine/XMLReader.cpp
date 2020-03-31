#include "XMLReader.h"
#include <iostream>

XMLError XMLReader::XMLLoad(const char* path) 
{
	XMLDocument xmlDoc;

	// Check if the file load correctly
	XMLError eResult = xmlDoc.LoadFile(path);
	XMLCheckResult(eResult);
	// Go through the scene root node
	XMLNode* scene = xmlDoc.FirstChildElement("Scene");
	if (scene == nullptr) return XML_ERROR_FILE_READ_ERROR;
	// Go through the first element 
	XMLElement* element = scene->FirstChildElement("GameObject");
	if (element == nullptr) { 
		std::cout << "Element null" << std::endl;
		return XML_ERROR_PARSING_ELEMENT; }
	//int xml_count;
	//eResult = element->QueryIntText(&xml_count);
	//XMLCheckResult(eResult);

	// Create empty game object
	GameObject go;
	//int i = 0;

	while (element != nullptr)
	{
		// Check the id of the gameobject element and store it
		XMLElement* item = element->FirstChildElement("ID");
		int id;
		eResult = item->QueryIntText(&id);
		XMLCheckResult(eResult);
		// Same thing for the position
		item = element->FirstChildElement("position")->FirstChildElement("x");
		float px;
		eResult = item->QueryFloatText(&px);

		float py;
		eResult = item->QueryFloatText(&py);
		// Create a gameobject with the id
		go = GameObject(id);
		std::cout << "Gameobject with id: " << go.GetID() << " found in xml" << std::endl;
		// Set it's position
		//go.GetComponent<TransformComponent>().position = sf::Vector2f(px, py);
		// Add the gameobject to the list
		GameObjects.push_back(go);
		// Go for the next gameobject
		element = element->NextSiblingElement("GameObject");
	}
}

XMLError XMLReader::XMLSave(const char* path, std::list<GameObject> GameObjects)
{
	XMLDocument xmlDoc;

	XMLNode* scene = xmlDoc.NewElement("Scene");

	xmlDoc.InsertFirstChild(scene);


	for (std::list<GameObject>::iterator it = GameObjects.begin(); it != GameObjects.end(); ++it) {
		// Add a gameobject element to xml
		XMLElement* rootElement = xmlDoc.NewElement("GameObject");

		// Adding details of gameobject
		// Adding id element
		XMLElement* goElement = xmlDoc.NewElement("ID");
		goElement->SetText(it->GetID());

		// Close the id element
		scene->InsertEndChild(goElement);

		// Adding position element
		goElement = xmlDoc.NewElement("position");

		// Adding x and y position under position element
		XMLElement* posElement = xmlDoc.NewElement("x");
		posElement->SetText(200);
		//posElement->SetText(it->GetComponent<TransformComponent>().position.x);
		goElement->InsertEndChild(posElement);
		// add y
		posElement = xmlDoc.NewElement("y");
		posElement->SetText(200);
		//posElement->SetText(it->GetComponent<TransformComponent>().position.y);
		goElement->InsertEndChild(posElement);
		// closing Position element
		scene->InsertEndChild(goElement);

	}
	XMLError eResult = xmlDoc.SaveFile(path);
	XMLCheckResult(eResult);
}