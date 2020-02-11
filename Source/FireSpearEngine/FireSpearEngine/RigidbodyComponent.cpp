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
}

void RigidbodyComponent::Start()
{
}

void RigidbodyComponent::Update(sf::Time deltaTime)
{
 
    //// check for obeyGravity, and add or remove gravity at run time
    //if (obeysGravity && !isHavingWeight) // if this object is changed to obeysGravity and there is not gravity is applied yet, add gravity to the forces
    //{
    //    forces.insert(forces.begin(), gravity);
    //    isHavingWeight = true;
    //}
    //else if(!obeysGravity && isHavingWeight)
    //{
    //    forces.erase(forces.begin());
    //    isHavingWeight = false;
    //}

    //if (mass == 0) return; // this object is static

    //sf::Vector2f newForce = sf::Vector2f(0, 0);

    //for (const auto& f : forces)
    //{
    //    newForce += f;
    //}

    // // Also add all the impulses, and then clear the list
    //for (const auto& i : impulse)
    //{
    //    newForce += i;
    //}

    //impulse.clear();

    //acceleration = newForce / mass;
    //velecity += sf::Vector2f(acceleration.x * deltaTime.asSeconds(), acceleration.y * deltaTime.asSeconds());
    //position += sf::Vector2f(velecity.x * deltaTime.asSeconds(), velecity.y * deltaTime.asSeconds());

    //transformMatrix = sf::Transform(
    //    1.0f, 0.0f, position.x,
    //    0.0f, 1.0f, position.y,
    //    0.0f, 0.0f, 1.f);
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

void RigidbodyComponent::Integrate(float dT, GameObject owner)
{

    sf::Vector2f acceleration;
    
  
    if (obeysGravity)
    {
        acceleration = gravity;
    }
    else
    {
        if (std::abs(velecity.y) < 0.05f) velecity.y = 0;
    }
   
    
    acceleration += totalForces / mass;
    if (mass == 0)
        acceleration = sf::Vector2f(0.0f, 0.0f);
    
    velecity += acceleration * dT;
    
    sf::Vector2f temp = owner.transformComponent.position;
    temp += velecity * dT;
    owner.transformComponent.position = temp;
   // SetAABB();
    
    totalForces = sf::Vector2f(0.0f, 0.0f);
}
