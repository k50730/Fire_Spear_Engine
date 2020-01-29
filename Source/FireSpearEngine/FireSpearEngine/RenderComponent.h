#pragma once
#include "BaseComponent.h"
#include "SFML/Graphics.hpp"


class RenderComponent : public BaseComponent
{
public:
	RenderComponent();
	void SetColor(sf::Color c);
	void SetRadius(float r);
	void Awake();
	void Start();
	void Update(sf::Time t);
	void LateUpdate();

	// Change to private later
	sf::CircleShape shape;
	sf::Transform position;
};

