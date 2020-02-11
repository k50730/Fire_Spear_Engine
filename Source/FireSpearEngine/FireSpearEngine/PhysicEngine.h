#pragma once
#include "SFML\Graphics.hpp"
#include "RigidbodyComponent.h"
#include "GameObjectManager.h"

class PhysicEngine
{
public:

    //static PhysicEngine engine;
    float groundedTol = 0.1f;

    struct CollisionPair
    {
        RigidbodyComponent* rigidBodyA;
        RigidbodyComponent* rigidBodyB;
    };

    struct CollisionInfo
    {
        sf::Vector2f collisionNormal;
        float penetration;
    };

private:
    std::map<CollisionPair, CollisionPair> collisions;
    std::vector<RigidbodyComponent*> rigidBodies; // keep track of all PhyscsRBody are existing in the scene

public:

    void AddRigidBody(RigidbodyComponent* rigidBody);
 
    void IntegrateBodies(float dT);
  
    bool IsGrounded(RigidbodyComponent* rigidBody);

    void Awake();

    void Start();

private:

    void CheckCollisions();

    void ResolveCollisions();

    /*
    When 2 objects are interpenetrating we need to seperate them by moving them to the contact normal direction. The distance need to move is base on the inverse propotion of their mass
    */
    void PositionalCorrection(CollisionPair c);

    void UpdatePhysics();

    // Update is called once per frame
    void FixedUpdate();
};

