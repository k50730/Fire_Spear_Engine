#include "RenderComponent.h"


RenderComponent::RenderComponent()
{
	id = BaseComponent::ComponentID::Render;
	shape = sf::CircleShape(50);
	shape.setOrigin(shape.getRadius(), shape.getRadius());
	shape.setOutlineColor(sf::Color::Black);
	shape.setOutlineThickness(-2);
}

void RenderComponent::SetColor(sf::Color c)
{
	shape.setFillColor(c);
}

void RenderComponent::SetRadius(float r)
{
	shape.setRadius(r);
	shape.setOrigin(shape.getRadius(), shape.getRadius());
}

void RenderComponent::Awake()
{
	
}

void RenderComponent::Start()
{
}

void RenderComponent::Update(sf::Time t)
{

}

void RenderComponent::LateUpdate()
{
}
