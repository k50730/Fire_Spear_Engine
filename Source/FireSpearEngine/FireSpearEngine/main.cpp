#include "FireSpear.h"
#include "LevelEditor.h"

int main()
{
	FireSpear* engine = new FireSpear();
	//engine->InitilizeSystem();

	//engine->sceneManager->LoadScene("../../../Assets/Scenes/Scene1.xml");
	//engine->sceneManager->LoadScene("../../../Assets/Scenes/Scene2.xml");
	//engine->sceneManager->SetActive(0);
	////engine->sceneManager->SetActive(1);

	//engine->sceneManager->SaveScene("../../../Assets/Scenes/saveTest2.xml");

	//engine->Run();
	//delete engine;

	LevelEditor* levelEditor = new LevelEditor(engine);
	levelEditor->Run();
	delete levelEditor;

	return 0;
}
