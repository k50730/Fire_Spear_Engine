#include "RenderComponent.h"


RenderComponent::RenderComponent()
{
	id = BaseComponent::ComponentID::Render;
	shape = sf::RectangleShape(sf::Vector2f(100.0f, 100.0f));
	shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
	shape.setOutlineColor(sf::Color::Black);
	shape.setOutlineThickness(-2);
}

void RenderComponent::SetColor(sf::Color c)
{
	shape.setFillColor(c);
}

void RenderComponent::SetSize(sf::Vector2f s)
{
	shape.setSize(s);
    shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
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
