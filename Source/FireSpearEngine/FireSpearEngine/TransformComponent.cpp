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