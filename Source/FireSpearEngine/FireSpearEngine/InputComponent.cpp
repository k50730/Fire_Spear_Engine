#include "InputComponent.h"

InputComponent::InputComponent()
{
	id = BaseComponent::ComponentID::Input;
}

InputComponent::~InputComponent()
{

}

void InputComponent::Awake()
{
}

void InputComponent::Start()
{
}

void InputComponent::Update(sf::Time t)
{
	float dt = t.asSeconds();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		vel = sf::Vector2f(0, -5.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		vel = sf::Vector2f(0, 5.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		vel = sf::Vector2f(-5.f, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		vel = sf::Vector2f(5.f, 0);
	}
	else if (sf::Keyboard::Unknown)
	{
		vel = sf::Vector2f(0, 0);
	}
	owner->transformComponent.position += vel * dt;
}

void InputComponent::LateUpdate()
{
}
