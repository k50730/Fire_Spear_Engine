#include "BaseComponent.h"

BaseComponent::BaseComponent(){
	Origin.x = 0;
	Origin.y = 0;
	Position.x = 0;
	Position.y = 0;
	Rotation = 0;
	Scale.x = 1;
	Scale.y = 1;
}

BaseComponent::BaseComponent(float ox, float oy, float x, float y, float angle, float fx, float fy) {
	Origin.x = ox;
	Origin.y = oy;
	Position.x = x;
	Position.y = y;
	Rotation = angle;
	Scale.x = fx;
	Scale.y = fy;
}

const sf::Vector2f BaseComponent::GetOrigin() const {
	return Origin;
}

const sf::Vector2f BaseComponent::GetPosition() const {
	return Position;
}

float BaseComponent::GetRotation() const {
	return Rotation;
}

const sf::Vector2f BaseComponent::GetScale() const {
	return Scale;
}

void BaseComponent::SetOrigin(float ox, float oy) {
	Origin.x = ox;
	Origin.y = oy;
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
