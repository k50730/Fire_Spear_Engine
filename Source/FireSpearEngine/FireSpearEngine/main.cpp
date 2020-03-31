#include "FireSpear.h"
#include "XMLReader.h"

int main()
{
	FireSpear* engine = new FireSpear();
	engine->InitilizeSystem();

	XMLReader* xmlManager = new XMLReader();
	xmlManager->XMLLoad("xmlTest.xml");

#pragma region Scene 1 - Child and Parent Objects

	//GameObject* sun = engine->gameObjectManager->CreateObject();
	//sun->transformComponent.position = sf::Vector2f(300, 200);
	//sun->AddComponent(new RenderComponent());
	//sun->GetComponent<RenderComponent*>()->SetColor(sf::Color::Yellow);
	//sun->GetComponent<RenderComponent*>()->SetSize(sf::Vector2f(200.0f, 200.0f));
	////sun->transformComponent.rotation = -90;

	//GameObject* earth = engine->gameObjectManager->CreateObject();
	//earth->SetParent(*sun);
	////sun->AddChild(earth);
	//earth->transformComponent.position = sf::Vector2f(100, 200);
	//earth->AddComponent(new RenderComponent());
	//earth->GetComponent<RenderComponent*>()->SetColor(sf::Color::Blue);

	////engine->gameObjectManager.DestroyObject(earth);
	////engine->gameObjectManager.DestroyObject(sun);


#pragma endregion

#pragma region Scene 2 - Physic - Collide With Gravity

	/*GameObject* sun = engine->gameObjectManager->CreateObject();
	sun->transformComponent.position = sf::Vector2f(600, 600);

	sun->AddComponent(new RenderComponent());
	sun->GetComponent<RenderComponent*>()->SetColor(sf::Color::Yellow);
	sun->GetComponent<RenderComponent*>()->SetSize(sf::Vector2f(800, 200));
	sun->AddComponent(new RigidbodyComponent());
	sun->GetComponent<RigidbodyComponent*>()->obeysGravity = false;
	sun->GetComponent<RigidbodyComponent*>()->mass = 0;

	GameObject* earth = engine->gameObjectManager->CreateObject();
	earth->transformComponent.position = sf::Vector2f(300, 200);
	earth->AddComponent(new RenderComponent());
	earth->GetComponent<RenderComponent*>()->SetColor(sf::Color::Blue);

	earth->AddComponent(new RigidbodyComponent());
	earth->GetComponent<RigidbodyComponent*>()->mass = 0.5f;
	earth->GetComponent<RigidbodyComponent*>()->obeysGravity = true;*/


	//GameObject* mars = engine->gameObjectManager->CreateObject();
	//mars->transformComponent.position = sf::Vector2f(600, 300);
	//mars->AddComponent(new RenderComponent());
	//mars->GetComponent<RenderComponent*>()->SetColor(sf::Color::Red);
	//mars->AddComponent(new RigidbodyComponent());
	//mars->GetComponent<RigidbodyComponent*>()->mass = 4;
	//mars->GetComponent<RigidbodyComponent*>()->obeysGravity = true;

#pragma endregion

#pragma region Scene 3 - Physic - Collide Without Gravity

	/*GameObject* sun = engine->gameObjectManager->CreateObject();
	sun->transformComponent.position = sf::Vector2f(1000, 200);
	sun->AddComponent(new RenderComponent());
	sun->GetComponent<RenderComponent*>()->SetColor(sf::Color::Yellow);
	sun->GetComponent<RenderComponent*>()->SetSize(sf::Vector2f(200, 200));
	sun->AddComponent(new RigidbodyComponent());
	sun->GetComponent<RigidbodyComponent*>()->obeysGravity = false;
	sun->GetComponent<RigidbodyComponent*>()->mass = 2;
	sun->GetComponent<RigidbodyComponent*>()->velecity = sf::Vector2f(-200.0f, 0.0f);

	GameObject* earth = engine->gameObjectManager->CreateObject();
	earth->transformComponent.position = sf::Vector2f(100, 200);
	earth->AddComponent(new RenderComponent());
	earth->GetComponent<RenderComponent*>()->SetColor(sf::Color::Blue);
	earth->AddComponent(new RigidbodyComponent());
	earth->GetComponent<RigidbodyComponent*>()->obeysGravity = false;
	earth->GetComponent<RigidbodyComponent*>()->velecity = sf::Vector2f(200.0f, 0.0f);*/

#pragma endregion

#pragma region Scene 4 - Audio Component

	//GameObject* sun = engine->gameObjectManager->CreateObject();
	//sun->transformComponent.position = sf::Vector2f(600, 600);

	//sun->AddComponent(new RenderComponent());
	//sun->GetComponent<RenderComponent*>()->SetColor(sf::Color::Yellow);
	//sun->GetComponent<RenderComponent*>()->SetSize(sf::Vector2f(800, 200));
	//sun->AddComponent(new RigidbodyComponent());
	//sun->GetComponent<RigidbodyComponent*>()->obeysGravity = false;
	//sun->GetComponent<RigidbodyComponent*>()->mass = 0;

	//GameObject* earth = engine->gameObjectManager->CreateObject();
	//earth->transformComponent.position = sf::Vector2f(300, 200);
	//earth->AddComponent(new RenderComponent());
	//earth->GetComponent<RenderComponent*>()->SetColor(sf::Color::Blue);

	//earth->AddComponent(new RigidbodyComponent());
	//earth->GetComponent<RigidbodyComponent*>()->mass = 0.5f;
	//earth->GetComponent<RigidbodyComponent*>()->obeysGravity = true;


	//GameObject* mars = engine->gameObjectManager->CreateObject();
	//mars->transformComponent.position = sf::Vector2f(600, 300);
	//mars->AddComponent(new RenderComponent());
	//mars->GetComponent<RenderComponent*>()->SetColor(sf::Color::Red);
	//mars->AddComponent(new RigidbodyComponent());
	//mars->GetComponent<RigidbodyComponent*>()->mass = 4;
	//mars->GetComponent<RigidbodyComponent*>()->obeysGravity = true;
	//mars->AddComponent(new AudioPlayerComponent());
	//mars->GetComponent<AudioPlayerComponent*>()->PlaySoundFromFile("../../Audio/arcade-intro-2.wav");
	//mars->GetComponent<AudioPlayerComponent*>()->SetVolume(30.f);
	//mars->GetComponent<AudioPlayerComponent*>()->IsLoop(true);
	//mars->GetComponent<AudioPlayerComponent*>()->Stop();

#pragma endregion

#pragma region Scene 5 - Script Component

	//GameObject* sun = engine->gameObjectManager->CreateObject();
	//sun->transformComponent.position = sf::Vector2f(600, 600);

	//sun->AddComponent(new RenderComponent());
	//sun->GetComponent<RenderComponent*>()->SetColor(sf::Color::Yellow);
	//sun->GetComponent<RenderComponent*>()->SetSize(sf::Vector2f(800, 200));
	//sun->AddComponent(new RigidbodyComponent());
	//sun->GetComponent<RigidbodyComponent*>()->obeysGravity = false;
	//sun->GetComponent<RigidbodyComponent*>()->mass = 0;

	//GameObject* earth = engine->gameObjectManager->CreateObject();
	//earth->transformComponent.position = sf::Vector2f(300, 200);
	//earth->AddComponent(new RenderComponent());
	//earth->GetComponent<RenderComponent*>()->SetColor(sf::Color::Blue);
	//earth->AddComponent(new RigidbodyComponent());
	//earth->GetComponent<RigidbodyComponent*>()->mass = 0.5f;
	//earth->GetComponent<RigidbodyComponent*>()->obeysGravity = true;
	//earth->AddComponent(new ScriptComponent("earth.lua"));


	//GameObject* mars = engine->gameObjectManager->CreateObject();
	//mars->transformComponent.position = sf::Vector2f(600, 300);
	//mars->AddComponent(new RenderComponent());
	//mars->GetComponent<RenderComponent*>()->SetColor(sf::Color::Red);
	//mars->AddComponent(new RigidbodyComponent());
	//mars->GetComponent<RigidbodyComponent*>()->mass = 4;
	//mars->GetComponent<RigidbodyComponent*>()->obeysGravity = true;
	//mars->AddComponent(new AudioPlayerComponent());
	//mars->GetComponent<AudioPlayerComponent*>()->PlaySoundFromFile("../../Audio/arcade-intro-2.wav");
	//mars->AddComponent(new ScriptComponent("mars.lua"));

#pragma endregion

#pragma region Scene 6 - Input System
	GameObject* sun = engine->gameObjectManager->CreateObject();
	sun->transformComponent.position = sf::Vector2f(600, 600);

	sun->AddComponent(new RenderComponent());
	sun->GetComponent<RenderComponent*>()->SetColor(sf::Color::Yellow);
	sun->GetComponent<RenderComponent*>()->SetSize(sf::Vector2f(800, 200));
	sun->AddComponent(new RigidbodyComponent());
	sun->GetComponent<RigidbodyComponent*>()->obeysGravity = false;
	sun->GetComponent<RigidbodyComponent*>()->mass = 0;

	GameObject* earth = engine->gameObjectManager->CreateObject();
	earth->transformComponent.position = sf::Vector2f(300, 200);
	earth->AddComponent(new RenderComponent());
	earth->GetComponent<RenderComponent*>()->SetColor(sf::Color::Blue);
	earth->AddComponent(new RigidbodyComponent());
	earth->GetComponent<RigidbodyComponent*>()->mass = 0;
	earth->GetComponent<RigidbodyComponent*>()->obeysGravity = false;

	GameObject* mars = engine->gameObjectManager->CreateObject();
	mars->transformComponent.position = sf::Vector2f(600, 300);
	mars->AddComponent(new RenderComponent());
	mars->GetComponent<RenderComponent*>()->SetColor(sf::Color::Red);
	mars->AddComponent(new RigidbodyComponent());
	mars->GetComponent<RigidbodyComponent*>()->mass = 4;
	mars->GetComponent<RigidbodyComponent*>()->obeysGravity = true;
	mars->AddComponent(new ScriptComponent("inputTest.lua"));
#pragma endregion

	engine->Run();
	delete engine;

	return 0;
}