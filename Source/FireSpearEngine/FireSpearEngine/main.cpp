#include "FireSpear.h"

int main()
{
	FireSpear* engine = new FireSpear();
	engine->InitilizeSystem();

	engine->sceneManager->LoadScene("Scene1.xml");
	engine->sceneManager->LoadScene("Scene2.xml");
	engine->sceneManager->SetActive(0);

	engine->sceneManager->SaveScene("text1.xml");
	//engine->sceneManager->SetActive(1);

	engine->Run();
	delete engine;

	return 0;
}