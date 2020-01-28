#include "TransformComponent.h"
#include <cmath>
#include <iostream>
TransformComponent::TransformComponent() : position(0,0), rotation(0), scale(1, 1)
{
	id = BaseComponent::ComponentID::Transform;
	matrix = sf::Transform::Identity;
}

void TransformComponent::Awake()
{
	sf::Transform translate
	(1.0f, 0.0f, position.x,
		0.0f, 1.0f, position.y,
		0.0f, 0.0f, 1.f);

	sf::Transform rotation
	(cos(rotation), -sin(rotation), 0.0f,
		sin(rotation), cos(rotation), 0.0f,
		0.0f, 0.0f, 1.0f);

	sf::Transform scale
	(scale.x, 0.0f, 0.0f,
		0.0f, scale.y, 0.0f,
		0.0f, 0.0f, 1.0f);

	matrix = sf::Transform::Identity * translate * rotation * scale;
}

void TransformComponent::Start()
{

}

void TransformComponent::Update(sf::Time t)
{
	sf::Transform translate
	   (1.0f, 0.0f, position.x,
		0.0f, 1.0f, position.y,
		0.0f, 0.0f, 1.f);

	sf::Transform rotation
	   (cos(rotation), -sin(rotation), 0.0f,
		sin(rotation), cos(rotation), 0.0f,
		0.0f, 0.0f, 1.0f);

	sf::Transform scale
	   (scale.x, 0.0f, 0.0f,
		0.0f, scale.y, 0.0f,
		0.0f, 0.0f, 1.0f);

	matrix = sf::Transform::Identity * translate * rotation * scale;
}

void TransformComponent::LateUpdate()
{

}
