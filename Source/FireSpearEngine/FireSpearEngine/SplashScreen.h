#pragma once

#include "SFML/Graphics.hpp"
#include "CoreEngine.h"


class SplashScreen
{
public:
	void Show(sf::RenderWindow& windows, CoreEngine::GameState gamestate);
};