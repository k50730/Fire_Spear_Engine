#include "XMLReader.h"
#include <iostream>
#include "ScriptComponent.h"
using namespace tinyxml2;

XMLError XMLReader::XMLLoad(XMLDocument* xmlDoc, GameObjectManager* gameObjectManager)
{
	// Go through the scene root node
	XMLNode* scene = xmlDoc->FirstChildElement("Scene");
	if (scene == nullptr) return XML_ERROR_FILE_READ_ERROR;
	// Go through the first element 
	XMLElement* element = scene->FirstChildElement("GameObject");
	if (element == nullptr) { 
		std::cout << "Element null" << std::endl;
		return XML_ERROR_PARSING_ELEMENT; }

	
	//int i = 0;
	// Run the while loop if there's still element
	while (element != nullptr)
	{
		GameObject* go = gameObjectManager->CreateObject();
		XMLElement* component = element->FirstChildElement();

		while (component != nullptr)
		{
			ReadComponentFromXML(go, component);
			component = component->NextSiblingElement();
		}
	
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

void XMLReader::ReadComponentFromXML(GameObject* g, XMLElement* c)
{
	std::string name = c->Name();
	if (name == "TransformComponent") ReadTransformProperties(g, c);
	else if(name == "RenderComponent") ReadRenderProperties(g, c);
	else if (name == "RigidbodyComponent") ReadRigidbodyProperties(g, c);
	else if(name == "ScriptComponent") g->AddComponent(new ScriptComponent(c->GetText()));
	else if (name == "AudioComponent") g->AddComponent(new AudioPlayerComponent());
	
}

void XMLReader::ReadTransformProperties(GameObject* g, XMLElement* c)
{
	XMLElement* property = c->FirstChildElement();

	while (property != nullptr)
	{
		switch (*property->Name())
		{
		case * "position":
			float px, py;
			property->FirstChildElement("x")->QueryFloatText(&px);
			property->FirstChildElement("y")->QueryFloatText(&py);
			g->transformComponent.position = sf::Vector2f(px, py);
			break;

		case * "scale":
			float sx, sy;
			property->FirstChildElement("x")->QueryFloatText(&sx);
			property->FirstChildElement("y")->QueryFloatText(&sy);
			g->transformComponent.scale = sf::Vector2f(sx, sy);
			break;

		case * "rotation":
			float a;
			property->QueryFloatText(&a);
			g->transformComponent.rotation = a;
			break;

		default:
			break;
		}
		property = property->NextSiblingElement();
	}
}

void XMLReader::ReadRenderProperties(GameObject* g, XMLElement* c)
{
	 g->AddComponent(new RenderComponent());
	 auto render = g->GetComponent<RenderComponent*>();

	 XMLElement* property = c->FirstChildElement();

	 while (property != nullptr)
	 {
		 switch (*property->Name())
		 {
		 case * "size":
			 float px, py;
			 property->FirstChildElement("x")->QueryFloatText(&px);
			 property->FirstChildElement("y")->QueryFloatText(&py);
			 render->SetSize(sf::Vector2f(px, py));
			 break;

		 case * "color":
			 float r, g, b, a;
			 property->FirstChildElement("r")->QueryFloatText(&r);
			 property->FirstChildElement("g")->QueryFloatText(&g);
			 property->FirstChildElement("b")->QueryFloatText(&b);
			 property->FirstChildElement("a")->QueryFloatText(&a);
			 render->SetColor(sf::Color(r, g, b, a));
			 break;

		 default:
			 break;
		 }
		 property = property->NextSiblingElement();
	 }
}

void XMLReader::ReadRigidbodyProperties(GameObject* g, tinyxml2::XMLElement* c)
{
	g->AddComponent(new RigidbodyComponent());

	auto rid = g->GetComponent<RigidbodyComponent*>();

	XMLElement* property = c->FirstChildElement();

	while (property != nullptr)
	{
		switch (*property->Name())
		{
		case * "velecity":
			float x, y;
			property->FirstChildElement("x")->QueryFloatText(&x);
			property->FirstChildElement("y")->QueryFloatText(&y);
			rid->velocity = sf::Vector2f(x, y);
			break;

		case * "mass":
			float m;
			property->QueryFloatText(&m);
			rid->SetMass(m);
			break;

		case * "bounciness":
			float b;
			property->QueryFloatText(&b);
			rid->SetBounciness(b);
			break;

		case * "obeysGravity":
			bool o;
			property->QueryBoolText(&o);
			rid->SetObeyGravity(o);
			break;

		case * "isTrigger":
			bool i;
			property->QueryBoolText(&i);
			rid->isTrigger = i;
			break;

		default:
			break;
		}
		property = property->NextSiblingElement();
	}
}
