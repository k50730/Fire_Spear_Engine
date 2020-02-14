#include "RigidbodyComponent.h"
#include <iostream>
RigidbodyComponent::RigidbodyComponent() 
{
    id = BaseComponent::ComponentID::Rigidbody;
}

RigidbodyComponent::~RigidbodyComponent()
{
}

void RigidbodyComponent::Awake()
{
}

void RigidbodyComponent::Start()
{
    SetAABB();
}

void RigidbodyComponent::Update(sf::Time deltaTime)
{
}

void RigidbodyComponent::LateUpdate()
{
}

void RigidbodyComponent::SetAABB()
{
    RenderComponent* r = owner->GetComponent<RenderComponent*>();

    aabb.bLeft = sf::Vector2f(-r->shape.getSize().x / 2, -r->shape.getSize().y / 2); //new Vector2(bound.center.x - bound.extents.x, bound.center.y - bound.extents.y);
    aabb.tRight = sf::Vector2f(r->shape.getSize().x / 2, r->shape.getSize().y / 2); //new Vector2(bound.center.x + bound.extents.x, bound.center.y + bound.extents.y);
}

void RigidbodyComponent::AddForce(sf::Vector2f force)
{
    totalForces += force;
}

void RigidbodyComponent::Stop()
{
    velecity = sf::Vector2f(0.0f, 0.0f);
    totalForces = sf::Vector2f(0.0f, 0.0f);
}

void RigidbodyComponent::Integrate(float dT)
{
    sf::Vector2f acceleration;
    if (obeysGravity && !grounded)
    {
        acceleration = gravity;
    }
    else
    {
        if (std::abs(velecity.y) < 2.0f) velecity.y = 0;
    }
   
    acceleration += totalForces / mass;
    if (mass == 0)
        acceleration = sf::Vector2f(0.0f, 0.0f);

    velecity += acceleration * dT;

    sf::Vector2f temp = owner->transformComponent.position;
    
    temp += velecity * dT;
    owner->transformComponent.position = temp;
    
    SetAABB();

    totalForces = sf::Vector2f(0.0f, 0.0f);
}
