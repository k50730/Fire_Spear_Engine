#include "SplashScreen.h"

void SplashScreen::Show(sf::RenderWindow& renderWindow, CoreEngine::GameState gameState) {
	sf::Image backgroundImg;
	sf::Texture backgroundTex;
	if (backgroundImg.loadFromFile("Images/NeZhas_Logo.png") != true) {
		return;
	}
	backgroundTex.loadFromImage(backgroundImg);
	sf::Sprite sprite(backgroundTex);

	renderWindow.draw(sprite);
	renderWindow.display();

	sf::Event event;
	while (gameState != CoreEngine::Initialized) {
		while (renderWindow.pollEvent(event)) {
			if (event.type == sf::Event::EventType::KeyPressed
				|| event.type == sf::Event::EventType::MouseButtonPressed
				|| event.type == sf::Event::EventType::Closed) {
				return;
			}
		}
	}
}