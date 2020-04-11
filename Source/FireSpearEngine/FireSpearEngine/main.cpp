#include "FireSpear.h"
#include "LevelEditor.h"

int main()
{
	FireSpear* engine = new FireSpear();
	engine->InitilizeSystem();

	engine->sceneManager->LoadScene("../../../Assets/Scenes/Scene1.xml");
	engine->sceneManager->LoadScene("../../../Assets/Scenes/Scene2.xml");
	engine->sceneManager->SetActive(0);
	//engine->sceneManager->SetActive(1);

	engine->Run();
	delete engine;

	/*LevelEditor* levelEditor = new LevelEditor();
	levelEditor->run();
	delete levelEditor;*/

	return 0;
}
