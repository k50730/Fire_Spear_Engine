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
		return XML_ERROR_PARSING_ELEMENT; 
	}

	
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

XMLError XMLReader::XMLSave(const char* path, std::list<GameObject*> GameObjects)
{
	XMLDocument xmlDoc;

	XMLNode* scene = xmlDoc.NewElement("Scene");

	xmlDoc.InsertFirstChild(scene);


	for (std::list<GameObject*>::iterator it = GameObjects.begin(); it != GameObjects.end(); ++it) {
		// Add a gameobject element to xml
		XMLElement* rootElement = xmlDoc.NewElement("GameObject");

		// Adding details of gameobject
		SaveTransformProperties(*it, xmlDoc.ToDocument(), rootElement);
		SaveRenderProperties(*it, xmlDoc.ToDocument(), rootElement);
		SaveRigidbodyProperties(*it, xmlDoc.ToDocument(), rootElement);

		scene->InsertEndChild(rootElement);

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
		case * "velocity":
			float x, y;
			property->FirstChildElement("x")->QueryFloatText(&x);
			property->FirstChildElement("y")->QueryFloatText(&y);
			rid->velecity = sf::Vector2f(x, y);
			break;

		case * "mass":
			float m;
			property->QueryFloatText(&m);
			rid->mass = m;
			break;

		case * "bounciness":
			float b;
			property->QueryFloatText(&b);
			rid->bounciness = b;
			break;

		case * "obeysGravity":
			bool o;
			property->QueryBoolText(&o);
			rid->obeysGravity = o;
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

void XMLReader::SaveComponentToXML(GameObject* g, XMLElement* c) 
{
	
}

void XMLReader::SaveTransformProperties(GameObject* g, XMLDocument* xDoc, XMLElement* e)
{
	XMLElement* newTransform = xDoc->NewElement("TransformComponent");

	float px, py;
	px = g->transformComponent.position.x;
	py = g->transformComponent.position.y;

	float sx, sy;
	sx = g->transformComponent.scale.x;
	sy = g->transformComponent.scale.y;

	float a;
	a = g->transformComponent.rotation;

	XMLElement* position = xDoc->NewElement("position");
	// x position
	XMLElement* posElement = xDoc->NewElement("x");
	posElement->SetText(px);
	position->InsertEndChild(posElement);
	// y position
	posElement = xDoc->NewElement("y");
	posElement->SetText(py);
	position->InsertEndChild(posElement);
	// End Child position
	newTransform->InsertEndChild(position);

	XMLElement* scale = xDoc->NewElement("scale");
	// x scale
	XMLElement* scaleElement = xDoc->NewElement("x");
	scaleElement->SetText(sx);
	scale->InsertEndChild(scaleElement);
	// y scale
	scaleElement = xDoc->NewElement("y");
	scaleElement->SetText(sy);
	scale->InsertEndChild(scaleElement);
	// End Child scale
	newTransform->InsertEndChild(scale);

	XMLElement* rotation = xDoc->NewElement("rotation");
	rotation->SetText(a);
	newTransform->InsertEndChild(rotation);


	e->InsertEndChild(newTransform);
}

void XMLReader::SaveRenderProperties(GameObject* g, XMLDocument* xDoc, XMLElement* e)
{
	auto render = g->GetComponent<RenderComponent*>();
	if (render != nullptr) {
		XMLElement* newRender = xDoc->NewElement("RenderComponent");

		float sx, sy;
		sx = render->GetSize().x;
		sy = render->GetSize().y;

		float r, gr, b, a;
		r = render->GetColor().r;
		gr = render->GetColor().g;
		b = render->GetColor().b;
		a = render->GetColor().a;

		XMLElement* size = xDoc->NewElement("size");
		// Save size x
		XMLElement* sizeElement = xDoc->NewElement("x");
		sizeElement->SetText(sx);
		size->InsertEndChild(sizeElement);
		// Save size y
		sizeElement = xDoc->NewElement("y");
		sizeElement->SetText(sy);
		size->InsertEndChild(sizeElement);

		// Close size properties
		newRender->InsertEndChild(size);

		XMLElement* color = xDoc->NewElement("color");
		// Save Red value
		XMLElement* colorElement = xDoc->NewElement("r");
		colorElement->SetText(r);
		color->InsertEndChild(colorElement);
		// Save Green value
		colorElement = xDoc->NewElement("g");
		colorElement->SetText(gr);
		color->InsertEndChild(colorElement);
		// Save Blue value
		colorElement = xDoc->NewElement("b");
		colorElement->SetText(b);
		color->InsertEndChild(colorElement);

		// Save Alpha value 
		colorElement = xDoc->NewElement("a");
		colorElement->SetText(a);
		color->InsertEndChild(colorElement);

		newRender->InsertEndChild(color);

		e->InsertEndChild(newRender);
	}
}

void XMLReader::SaveRigidbodyProperties(GameObject* g, tinyxml2::XMLDocument* xDoc, tinyxml2::XMLElement* e)
{
	auto rb = g->GetComponent<RigidbodyComponent*>();
	if (rb != nullptr) {
		bool obey;
		obey = rb->obeysGravity;

		float m;
		m = rb->mass;
		float vx, vy;
		vx = rb->velecity.x;
		vy = rb->velecity.y;

		float bounciness;
		bounciness = rb->bounciness;

		bool isTrigger;
		isTrigger = rb->isTrigger;

		XMLElement* newRB = xDoc->NewElement("RigidbodyComponent");
		// Obey Grivity
		XMLElement* og = xDoc->NewElement("obeysGravity");
		og->SetText(obey);
		//Close obey
		newRB->InsertEndChild(og);

		// Mass
		XMLElement* mass = xDoc->NewElement("mass");
		mass->SetText(mass);
		// Close mass
		newRB->InsertEndChild(mass);

		// Velocity
		XMLElement* velocity = xDoc->NewElement("velocity");
		// Velocity x
		XMLElement* velocityElement = xDoc->NewElement("x");
		velocityElement->SetText(vx);
		velocity->InsertEndChild(velocityElement);
		// Velocity y
		velocityElement = xDoc->NewElement("y");
		velocityElement->SetText(vy);
		velocity->InsertEndChild(velocityElement);
		// Close vel
		newRB->InsertEndChild(velocity);

		// Bounciness
		XMLElement* boun = xDoc->NewElement("bounciness");
		boun->SetText(bounciness);
		// Close bounciness
		newRB->InsertEndChild(boun);

		// isTrigger
		XMLElement* isTrig = xDoc->NewElement("isTrigger");
		isTrig->SetText(isTrigger);
		// Close Trigger
		newRB->InsertEndChild(isTrig);

		e->InsertEndChild(newRB);
	}
}
