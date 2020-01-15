#include "TransformComponent.h"



void TransformComponent::MoveOrigin(float ox, float oy) {
	SetOrigin(ox, oy);
}

void TransformComponent::Move(float x, float y) {
	SetPosition(x, y);
}

void TransformComponent::Rotate(float angle) {
	SetRotation(angle);
}

void TransformComponent::Scaling(float fx, float fy) {
	SetScale(fx, fy);
}

void TransformComponent::setPosition(const sf::Vector2f& position)
{

}

void TransformComponent::setPosition(float x, float y)
{

}

void TransformComponent::setRotation(float angle)
{

}

void TransformComponent::setScale(float factorX, float factorY)
{

}

void TransformComponent::setScale(const sf::Vector2f& factors)
{

}

