#pragma once
#include "SFML\Graphics.hpp"
#include "RigidbodyComponent.h"
#include "GameObjectManager.h"
#include <unordered_map>

class PhysicEngine
{
public:

    PhysicEngine(GameObjectManager* g);

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
    std::map<CollisionPair*, CollisionInfo*> collisions;
    std::vector<RigidbodyComponent*> rigidBodies; // keep track of all PhyscsRBody are existing in the scene

public:

    void AddRigidBody(RigidbodyComponent* rigidBody);
 
    void IntegrateBodies(sf::Time);
  
    bool IsGrounded(RigidbodyComponent* rigidBody);

    void Awake();

    void Start();

    void UpdatePhysics(sf::Time);

    // Update is called once per frame
    void FixedUpdate(sf::Time);

private:

    void CheckCollisions();

    void ResolveCollisions();

    /*
    When 2 objects are interpenetrating we need to seperate them by moving them to the contact normal direction. The distance need to move is base on the inverse propotion of their mass
    */
    void PositionalCorrection(CollisionPair* c);

    GameObjectManager* gameObjectManager;
};

