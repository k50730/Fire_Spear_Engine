#include "RigidbodyComponent.h"

RigidbodyComponent::RigidbodyComponent() 
{
    id = BaseComponent::ComponentID::Rigidbody;
    acceleration = obeysGravity ? gravity : sf::Vector2f(0, 0);
}

RigidbodyComponent::~RigidbodyComponent()
{
}

void RigidbodyComponent::Awake()
{
    forces.push_back(gravity);
}

void RigidbodyComponent::Start()
{
}

void RigidbodyComponent::Update(sf::Time deltaTime)
{
    if (mass == 0) return; // this object is static

    sf::Vector2f newForce = sf::Vector2f(0, 0);

    for (const auto& f : forces)
    {
        newForce += f;
    }

     // Also add all the impulses, and then clear the list
    for (const auto& i : impulse)
    {
        newForce += i;
    }
    impulse.clear();

    acceleration = newForce / mass;
    velecity += sf::Vector2f(acceleration.x * deltaTime.asSeconds(), acceleration.y * deltaTime.asSeconds());
    position += sf::Vector2f(velecity.x * deltaTime.asSeconds(), velecity.y * deltaTime.asSeconds());
}

void RigidbodyComponent::LateUpdate()
{
}

void RigidbodyComponent::AddForce(const sf::Vector2f& f)
{
}

void RigidbodyComponent::AddImpulse(const sf::Vector2f& i)
{
}
