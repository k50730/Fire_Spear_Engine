#pragma once
#include "BaseComponent.h"
#include "SFML/Graphics.hpp"


class RenderComponent : public BaseComponent
{
public:
	RenderComponent();
	void SetColor(sf::Color c);
	void SetSize(sf::Vector2f);
	void Awake();
	void Start();
	void Update(sf::Time t);
	void LateUpdate();

	// Change to private later
	sf::RectangleShape shape;
	sf::Transform transform;
};

