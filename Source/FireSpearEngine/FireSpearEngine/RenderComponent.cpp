#include "RenderComponent.h"


RenderComponent::RenderComponent()
{
	id = BaseComponent::ComponentID::Render;
	shape = sf::RectangleShape(sf::Vector2f(100.0f, 100.0f));
	shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
	shape.setOutlineColor(sf::Color::Black);
	shape.setOutlineThickness(-2);
}

RenderComponent::~RenderComponent()
{
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

void RenderComponent::SetColor(sf::Color c)
{
	shape.setFillColor(c);
}

void RenderComponent::SetTransform(sf::Transform t)
{
	transform = t;
}

void RenderComponent::SetSize(sf::Vector2f size)
{
	shape.setSize(size);
	shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
}

void RenderComponent::SetScale(sf::Vector2f scale)
{
	SetSize(sf::Vector2f(shape.getSize().x * scale.x, shape.getSize().y * scale.y));
	
}

