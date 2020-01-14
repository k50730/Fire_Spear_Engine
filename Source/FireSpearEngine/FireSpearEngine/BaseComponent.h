#pragma once

#include "../ExternalResources/SFML/System/Vector2.hpp"

//using namespace sf;

class BaseComponent
{
	BaseComponent();
	BaseComponent(float ox, float oy, float x, float y, float angle, float fx, float fy);

private:
	sf::Vector2f Origin;
	sf::Vector2f Position;
	float Rotation;
	sf::Vector2f Scale;

public:
	const sf::Vector2f GetOrigin() const;
	const sf::Vector2f GetPosition() const;
	float GetRotation() const;
	const sf::Vector2f GetScale() const;

	void SetOrigin(float ox, float oy);
	void SetPosition(float x, float y);
	void SetRotation(float angle);
	void SetScale(float fx, float fy);
};