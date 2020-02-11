#include <SFML/Graphics.hpp>
#include "FireSpear.h"

int main()
{
	FireSpear* engine = new FireSpear();

	engine->InitilizeSystem();

#pragma region Create Game Objects

	GameObject* sun = engine->gameObjectManager.CreateObject();
	sun->transformComponent.position = sf::Vector2f(300, 300);
	sun->AddComponent(new RenderComponent());
	sun->GetComponent<RenderComponent*>()->SetColor(sf::Color::Yellow);
	sun->GetComponent<RenderComponent*>()->SetRadius(100);
	sun->transformComponent.rotation = -90;
	sun->AddComponent(new CircleColliderComponent());

	GameObject* earth = engine->gameObjectManager.CreateObject();
	earth->SetParent(*sun);
	//sun->AddChild(earth);
	earth->transformComponent.position = sf::Vector2f(100, 200);
	earth->AddComponent(new RenderComponent());
	earth->GetComponent<RenderComponent*>()->SetColor(sf::Color::Blue);
	earth->AddComponent(new RigidbodyComponent());
	earth->GetComponent<RigidbodyComponent*>()->obeysGravity = false;
	earth->GetComponent<RigidbodyComponent*>()->velecity = sf::Vector2f(2.0f, 0.0f);


	//engine->gameObjectManager.DestroyObject(earth);
	//engine->gameObjectManager.DestroyObject(sun);

#pragma endregion


	engine->Start();

	delete engine;

	return 0;
}