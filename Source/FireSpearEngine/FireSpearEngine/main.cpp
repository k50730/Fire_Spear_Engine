#include "FireSpear.h"
#include "XMLReader.h"

int main()
{
	FireSpear* engine = new FireSpear();
	engine->InitilizeSystem();

	XMLReader* xmlManager = new XMLReader();
	xmlManager->XMLLoad("xmlTest.xml", engine->gameObjectManager);

	engine->Run();
	delete engine;

	return 0;
}