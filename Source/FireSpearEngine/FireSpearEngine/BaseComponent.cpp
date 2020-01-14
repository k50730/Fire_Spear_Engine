#include "BaseComponent.h"

BaseComponent::BaseComponent(){
}

const sf::Vector2f BaseComponent::GetPosition() const{
	return Position;
}

float BaseComponent::GetRotation() const{
	return Rotation;
}

const sf::Vector2f BaseComponent::GetScale() const {
	return Scale;
}

void BaseComponent::SetPosition(float x, float y) {
	Position.x = x;
	Position.y = y;
}

void BaseComponent::SetRotation(float angle) {
	Rotation = angle;
}

void BaseComponent::SetScale(float fx, float fy) {
	Scale.x = fx;
	Scale.y = fy;
}