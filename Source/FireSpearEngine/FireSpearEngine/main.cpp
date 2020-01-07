#include <SFML/Graphics.hpp>
#include "CoreEngine.h"



int main() 
{
	/*CoreEngine* engine = new CoreEngine();

	if (engine->InitilizeSystem())
	{
		engine->CreateEngineWindow("FireSpear Engine", 200, 200, 1280, 768);
		engine->Run();
	}

	delete engine;
	return 0;*/

    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}