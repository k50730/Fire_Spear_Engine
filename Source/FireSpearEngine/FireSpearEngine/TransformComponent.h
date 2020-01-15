#pragma once

#include "BaseComponent.h"
#include "../ExternalResources/SFML/Graphics/Transform.hpp"
#include "../ExternalResources/SFML/Graphics/Transformable.hpp"

class TransformComponent : public BaseComponent {
	TransformComponent();

private:
	sf::Vector2f m_origin;
	sf::Vector2f m_position;
	float m_angle;
	sf::Vector2f m_scale;

public:

	void MoveOrigin(float ox, float oy);
	void Move(float x, float y);
	void Rotate(float angle);
	void Scaling(float fx, float fy);
};

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


