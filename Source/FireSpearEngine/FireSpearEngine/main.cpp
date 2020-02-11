#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "FireSpear.h"



int main()
{
	FireSpear* engine = new FireSpear();

	engine->InitilizeSystem();

#pragma region Create Game Objects

	GameObject* sun = engine->gameObjectManager.CreateObject();
	GameObject* bgmHolder = engine->gameObjectManager.CreateObject();
	sun->transformComponent.position = sf::Vector2f(300, 300);
	sun->AddComponent(new RenderComponent());
	sun->GetComponent<RenderComponent*>()->SetColor(sf::Color::Yellow);
	sun->GetComponent<RenderComponent*>()->SetRadius(100);
	sun->transformComponent.rotation = -90;

	GameObject* earth = engine->gameObjectManager.CreateObject();
	earth->SetParent(*sun);
	//sun->AddChild(earth);
	earth->transformComponent.position = sf::Vector2f(100, 200);
	earth->AddComponent(new RenderComponent());
	earth->GetComponent<RenderComponent*>()->SetColor(sf::Color::Blue);
	sun->AddComponent(new RigidbodyComponent());
	sun->GetComponent<RigidbodyComponent*>()->obeysGravity = true;

	/*bgmHolder->AddComponent(new AudioPlayerComponent());
	bgmHolder->GetComponent<AudioPlayerComponent*>()->PlaySoundFromFile("arcade-intro-2.wav");*/
	//engine->gameObjectManager.DestroyObject(earth);
	//engine->gameObjectManager.DestroyObject(sun);

#pragma endregion


	engine->Start();

	delete engine;

	return 0;
}