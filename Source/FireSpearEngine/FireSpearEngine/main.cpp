#include <SFML/Graphics.hpp>
#include "FireSpear.h"

int main()
{
	FireSpear* engine = new FireSpear();
	engine->InitilizeSystem();

#pragma region Scene 1 - Child and Parent Objects

	//GameObject* sun = engine->gameObjectManager.CreateObject();
	//sun->transformComponent.position = sf::Vector2f(100, 600);
	//sun->AddComponent(new RenderComponent());
	//sun->GetComponent<RenderComponent*>()->SetColor(sf::Color::Yellow);
	//sun->GetComponent<RenderComponent*>()->SetRadius(100);
	//sun->transformComponent.rotation = -90;

	//GameObject* earth = engine->gameObjectManager.CreateObject();
	//earth->SetParent(*sun);
	////sun->AddChild(earth);
	//earth->transformComponent.position = sf::Vector2f(100, 200);
	//earth->AddComponent(new RenderComponent());
	//earth->GetComponent<RenderComponent*>()->SetColor(sf::Color::Blue);

	////engine->gameObjectManager.DestroyObject(earth);
	////engine->gameObjectManager.DestroyObject(sun);

#pragma endregion

#pragma region Scene 2 - Physic

	GameObject* sun = engine->gameObjectManager.CreateObject();
	sun->transformComponent.position = sf::Vector2f(100, 600);
	sun->AddComponent(new RenderComponent());
	sun->GetComponent<RenderComponent*>()->SetColor(sf::Color::Yellow);
	sun->GetComponent<RenderComponent*>()->SetRadius(100);
	sun->AddComponent(new RigidbodyComponent());
	sun->GetComponent<RigidbodyComponent*>()->obeysGravity = false;
	sun->GetComponent<RigidbodyComponent*>()->mass = 0;
	//sun->GetComponent<RigidbodyComponent*>()->velecity = sf::Vector2f(-200.0f, 0.0f);

	GameObject* earth = engine->gameObjectManager.CreateObject();
	earth->transformComponent.position = sf::Vector2f(100, 200);
	earth->AddComponent(new RenderComponent());
	earth->GetComponent<RenderComponent*>()->SetColor(sf::Color::Blue);
	earth->AddComponent(new RigidbodyComponent());
	earth->GetComponent<RigidbodyComponent*>()->obeysGravity = true;
	//earth->GetComponent<RigidbodyComponent*>()->velecity = sf::Vector2f(200.0f, 0.0f);

#pragma endregion

	engine->Start();
	delete engine;

	return 0;
}