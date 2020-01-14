#pragma once
#include <SFML/Graphics/Transform.hpp>
#include "BaseComponent.h"


class TransformComponent : public BaseComponent
{
public:
	TransformComponent();
	~TransformComponent();
	void setPosition(const sf::Vector2f& position);
	void setPosition(float x, float y);

	void setRotation(float angle);

	void setScale(float factorX, float factorY);
	void setScale(const sf::Vector2f& factors);
};

