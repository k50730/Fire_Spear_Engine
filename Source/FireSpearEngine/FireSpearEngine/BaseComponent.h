#pragma once

#include "../ExternalResources/SFML/System/Vector2.hpp"

//using namespace sf;

class BaseComponent
{
private:
	sf::Vector2f Position;
	float Rotation;
	sf::Vector2f Scale;

public:
	BaseComponent();
	const sf::Vector2f GetPosition() const;
	float GetRotation() const;
	const sf::Vector2f GetScale() const;
	
	void SetPosition(float x, float y);
	void SetRotation(float angle);
	void SetScale(float fx, float fy);
};