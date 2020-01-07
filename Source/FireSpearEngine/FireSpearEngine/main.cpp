
#include "CoreEngine.h"



int main() 
{
	CoreEngine* engine = new CoreEngine();

	if (engine->InitilizeSystem())
	{
		engine->CreateEngineWindow("FireSpear Engine", 200, 200, 1280, 768);
		engine->Run();
	}

	delete engine;
	return 0;
}