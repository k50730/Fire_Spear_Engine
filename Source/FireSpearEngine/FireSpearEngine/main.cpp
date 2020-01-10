#include <SFML/Graphics.hpp>
#include "CoreEngine.h"



int main() 
{
	CoreEngine* engine = new CoreEngine();

	engine->InitilizeSystem();
	engine->Start();
	delete engine;
	
    return 0;
}