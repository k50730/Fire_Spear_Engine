#include "PhysicEngine.h"

PhysicEngine::PhysicEngine(GameObjectManager* g)
{
    gameObjectManager = g;
}

PhysicEngine::~PhysicEngine()
{
    for (auto const& c : collisions)
    {
        delete c.first;
        delete c.second;
    }
    collisions.clear();
}

void PhysicEngine::AddRigidBody(RigidbodyComponent* rigidBody)
{
	rigidBodies.push_back(rigidBody);
}

void PhysicEngine::IntegrateBodies(sf::Time dT)
{
    for (std::map<int, GameObject*>::iterator i = gameObjectManager->gameObjects.begin(); i != gameObjectManager->gameObjects.end(); ++i)
    {
        if ((i->second)->GetComponent<RigidbodyComponent*>() != nullptr)
        {
            (i->second)->GetComponent<RigidbodyComponent*>()->Integrate(dT.asSeconds());
        }
    }

}

void PhysicEngine::IsGrounded()
{
    for (int i = 0; i < rigidBodies.size(); i++)
    {
        for (int j = 0; j < rigidBodies.size(); j++)
        {
            if (i != j)
            {
                if (rigidBodies[i]->owner->transformComponent.position.x + rigidBodies[i]->aabb.bLeft.x <rigidBodies[j]->owner->transformComponent.position.x + rigidBodies[j]->aabb.tRight.x
                    && rigidBodies[i]->owner->transformComponent.position.x + rigidBodies[i]->aabb.tRight.x > rigidBodies[j]->owner->transformComponent.position.x + rigidBodies[j]->aabb.bLeft.x
                    )
                {
                    if (rigidBodies[i]->GetMass() != 0)
                    {
                        if (std::abs(rigidBodies[j]->owner->transformComponent.position.y + rigidBodies[i]->aabb.bLeft.y - rigidBodies[j]->aabb.tRight.y - rigidBodies[i]->owner->transformComponent.position.y) < groundedTol)
                        {
                            if (std::abs(rigidBodies[i]->velocity.y) < 0.1f) rigidBodies[i]->grounded = true;
                        }
                    }
                }
            }
        }
    }
}

void PhysicEngine::Instantiate()
{
    for (std::map<int, GameObject*>::iterator i = gameObjectManager->gameObjects.begin(); i != gameObjectManager->gameObjects.end(); ++i)
    {
        if ((i->second)->GetComponent<RigidbodyComponent*>() != nullptr)
        {
            (i->second)->GetComponent<RigidbodyComponent*>()->owner = i->second;
        }
    }
}

void PhysicEngine::Awake()
{
    for (std::map<int, GameObject*>::iterator i = gameObjectManager->gameObjects.begin(); i != gameObjectManager->gameObjects.end(); ++i)
    {
        if ((i->second)->GetComponent<RigidbodyComponent*>() != nullptr)
        {
            rigidBodies.push_back((i->second)->GetComponent<RigidbodyComponent*>());
        }
    }
}

void PhysicEngine::Start()
{
}

void PhysicEngine::CheckCollisions()
{
    for (int i = 0; i < rigidBodies.size(); i++)
    {
        for (int j = 0; j < rigidBodies.size(); j++)
        {
            if (j != i)
            {
                CollisionPair* pair = new CollisionPair();
                CollisionInfo* colInfo = new CollisionInfo();

                pair->rigidBodyA = rigidBodies[i];
                pair->rigidBodyB = rigidBodies[j];

                sf::Vector2f distance = rigidBodies[j]->owner->transformComponent.position - rigidBodies[i]->owner->transformComponent.position;

                sf::Vector2f halfSizeA = sf::Vector2f((rigidBodies[i]->aabb.tRight - rigidBodies[i]->aabb.bLeft).x/ 2, (rigidBodies[i]->aabb.tRight - rigidBodies[i]->aabb.bLeft).y / 2);
                sf::Vector2f halfSizeB = sf::Vector2f((rigidBodies[j]->aabb.tRight - rigidBodies[j]->aabb.bLeft).x / 2, (rigidBodies[j]->aabb.tRight - rigidBodies[j]->aabb.bLeft).y / 2);

                sf::Vector2f gap = sf::Vector2f(std::abs(distance.x), std::abs(distance.y)) - (halfSizeA + halfSizeB);

              
                // Seperating Axis Theorem test
                if (gap.x < 0 && gap.y < 0)
                {
                    //std::cout << "Collide" << std::endl;

                    for (auto c : collisions)
                    {
                        if (c.first->rigidBodyA == pair->rigidBodyA && c.first->rigidBodyB == pair->rigidBodyB)
                        {
                            clearCollisions = true;
                            break;
                        }
                    }
                    if (clearCollisions)
                    {
                        collisions.clear();
                        clearCollisions = false;
                        return;
                    }
                    
                    if (gap.x > gap.y)
                    {
                        colInfo->collisionNormal = distance.x > 0 ? sf::Vector2f(1.0f, 0.0f) : sf::Vector2f(-1.0f, 0.0f); // Update collision normal
                        colInfo->penetration = gap.x;
                    }
                    else
                    {
                        colInfo->collisionNormal = distance.y > 0 ? sf::Vector2f(0.0f, 1.0f) : sf::Vector2f(0.0f, -1.0f); // Update collision normal
                        colInfo->penetration = gap.y;
                    }

                    collisions[pair] = colInfo;
                }
                else
                {
                    for (auto c : collisions)
                    {
                        if (c.first->rigidBodyA == pair->rigidBodyA && c.first->rigidBodyB == pair->rigidBodyB)
                        {
                            clearCollisions = true;
                            break;
                        }
                    }
                    if (clearCollisions)
                    {
                        collisions.clear();
                        clearCollisions = false;
                    }

                    delete pair;
                    delete colInfo;
                }

            }
        }
    }
}

void PhysicEngine::ResolveCollisions()
{
    for (auto const& c : collisions)
    {
        if (c.second != nullptr)
        {
            float minBounce = std::min(c.first->rigidBodyA->GetBounciness(), c.first->rigidBodyB->GetBounciness());

            // dot product of relativeVelocity and collisionNormal
            float velAlongNormal = ((c.first->rigidBodyB->velocity - c.first->rigidBodyA->velocity).x * collisions[c.first]->collisionNormal.x) + ((c.first->rigidBodyB->velocity - c.first->rigidBodyA->velocity).y * collisions[c.first]->collisionNormal.y);

            if (velAlongNormal > 0) continue; // the contact is either stationary or seperating -> no impluse is needed

            float j = -(1 + minBounce) * velAlongNormal;

            float invMassA = c.first->rigidBodyA->GetMass() == 0 ? 0 : 1 / c.first->rigidBodyA->GetMass();

            float invMassB = c.first->rigidBodyB->GetMass() == 0 ? 0 : 1 / c.first->rigidBodyB->GetMass();

            j /= invMassA + invMassB;

            sf::Vector2f impulse = j * collisions[c.first]->collisionNormal;

            // update velocities
            c.first->rigidBodyA->velocity = c.first->rigidBodyA->velocity - impulse * invMassA;
            c.first->rigidBodyB->velocity = c.first->rigidBodyB->velocity + impulse * invMassB;

            if (std::abs(collisions[c.first]->penetration) > 0.01f)
            {
                PositionalCorrection(c.first);
            }
        }
        
    }
}

void PhysicEngine::PositionalCorrection(CollisionPair* c)
{
    if (collisions[c]->penetration <= 0) return;

    const float percent = 0.2f; // what is this ?????

    float invMassA = c->rigidBodyA->GetMass() == 0 ? 0 : 1 / c->rigidBodyA->GetMass();
    float invMassB = c->rigidBodyB->GetMass() == 0 ? 0 : 1 / c->rigidBodyB->GetMass();

    sf::Vector2f correction = ((collisions[c]->penetration / (invMassA + invMassB)) * percent) * -collisions[c]->collisionNormal;

    sf::Vector2f temp = c->rigidBodyA->owner->transformComponent.position;
    temp -= invMassA * correction;
    c->rigidBodyA->owner->transformComponent.position = temp;

    temp = c->rigidBodyB->owner->transformComponent.position;
    temp += invMassB * correction;
    c->rigidBodyB->owner->transformComponent.position = temp;
}

void PhysicEngine::UpdatePhysics(sf::Time t)
{
    IsGrounded();
    IntegrateBodies(t);
    CheckCollisions();
    ResolveCollisions();
}

void PhysicEngine::FixedUpdate(sf::Time t)
{
    UpdatePhysics(t);
}
