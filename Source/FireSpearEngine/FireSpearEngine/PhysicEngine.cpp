#include "PhysicEngine.h"

void PhysicEngine::AddRigidBody(RigidbodyComponent* rigidBody)
{
	rigidBodies.push_back(rigidBody);
}

void PhysicEngine::IntegrateBodies(float dT)
{
   /* foreach(PhysicsRBody rb in rigidBodies)
    {
        rb.Integrate(dT);
    }*/
}

bool PhysicEngine::IsGrounded(RigidbodyComponent* rigidBody)
{
    for (const auto& rb : rigidBodies)
    {
        if (rb != rigidBody)
        {
            /* if (rigidBody.aabb.bLeft.x < rb.aabb.tRight.x
                 && rigidBody.aabb.tRight.x > rb.aabb.bLeft.x
                 && Mathf.Abs(rigidBody.aabb.bLeft.y - rb.aabb.tRight.y) <= groundedTol)
             {
                 if (Mathf.Abs(rigidBody.currentVelocity.y) < groundedTol)
                     return true;
             }*/
        }
    }
    return false;
}

void PhysicEngine::Awake()
{
    
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
                //CollisionPair pair;
                //CollisionInfo colInfo;
                //pair.rigidBodyA = rigidBodies[i];
                //pair.rigidBodyB = rigidBodies[j];

                //sf::Vector2f distance = rigidBodies[j]->position - rigidBodies[i]->position;

                //sf::Vector2f halfSizeA = (bodyA.aabb.tRight - bodyA.aabb.bLeft) / 2;
                //sf::Vector2f halfSizeB = (bodyB.aabb.tRight - bodyB.aabb.bLeft) / 2;

                //sf::Vector2f gap = sf::Vector2f(Mathf.Abs(distance.x), Mathf.Abs(distance.y)) - (halfSizeA + halfSizeB);

                //// Seperating Axis Theorem test
                //if (gap.x < 0 && gap.y < 0)
                //{
                //    Debug.Log("Collided!!!");

                //    if (collisions.ContainsKey(pair))
                //    {
                //        collisions.Remove(pair);
                //    }

                //    if (gap.x > gap.y)
                //    {
                //        if (distance.x > 0)
                //        {
                //            colInfo.collisionNormal = new Vector2(1, 0); // ... Update collision normal
                //        }
                //        else
                //        {
                //            colInfo.collisionNormal = new Vector2(-1, 0); // ... Update collision normal
                //        }
                //        colInfo.penetration = gap.x;
                //    }
                //    else {
                //        if (distance.y > 0)
                //        {
                //            colInfo.collisionNormal = new Vector2(0, 1); // ... Update collision normal
                //        }
                //        else
                //        {
                //            colInfo.collisionNormal = new Vector2(0, -1); // ... Update collision normal
                //        }
                //        colInfo.penetration = gap.y;
                //    }
                //    collisions.Add(pair, colInfo);
                //}
                //else if (collisions.ContainsKey(pair))
                //{
                //    Debug.Log("removed");
                //    collisions.Remove(pair);
                //}
            }
        }
    }
}

void PhysicEngine::ResolveCollisions()
{
    //foreach(CollisionPair pair in collisions.Keys)
    //{
    //    float minBounce = Mathf.Min(pair.rigidBodyA.bounciness, pair.rigidBodyB.bounciness);


    //    float velAlongNormal = Vector2.Dot(pair.rigidBodyB.currentVelocity - pair.rigidBodyA.currentVelocity, collisions[pair].collisionNormal);

    //    if (velAlongNormal > 0) continue; // the contact is either stationary or seperating -> no impluse is needed

    //    float j = -(1 + minBounce) * velAlongNormal;

    //    float invMassA = pair.rigidBodyA.mass == 0 ? 0 : 1 / pair.rigidBodyA.mass;

    //    float invMassB = pair.rigidBodyB.mass == 0 ? 0 : 1 / pair.rigidBodyB.mass;

    //    j /= invMassA + invMassB;

    //    Vector2 impulse = j * collisions[pair].collisionNormal;

    //    // ... update velocities
    //    pair.rigidBodyA.currentVelocity = pair.rigidBodyA.currentVelocity - impulse * invMassA;
    //    pair.rigidBodyB.currentVelocity = pair.rigidBodyB.currentVelocity + impulse * invMassB;


    //    if (Mathf.Abs(collisions[pair].penetration) > 0.01f)
    //    {
    //        PositionalCorrection(pair);
    //    }
    //}
}

void PhysicEngine::PositionalCorrection(CollisionPair c)
{
    //if (collisions[c].penetration <= 0) return; // the are already seperated

    //const float percent = 0.2f; // what is this ?????

    //float invMassA = c.rigidBodyA.mass == 0 ? 0 : 1 / c.rigidBodyA.mass;
    //float invMassB = c.rigidBodyB.mass == 0 ? 0 : 1 / c.rigidBodyB.mass;


    //Vector2 correction = ((collisions[c].penetration / (invMassA + invMassB)) * percent) * -collisions[c].collisionNormal;

    //Vector2 temp = c.rigidBodyA.transform.position;
    //temp -= invMassA * correction;
    //c.rigidBodyA.transform.position = temp;

    //temp = c.rigidBodyB.transform.position;
    //temp += invMassB * correction;
    //c.rigidBodyB.transform.position = temp;
}

void PhysicEngine::UpdatePhysics()
{
    // ....
  /*  IntegrateBodies(Time.deltaTime);
    CheckCollisions();
    ResolveCollisions();*/
}

void PhysicEngine::FixedUpdate()
{
    UpdatePhysics();
}
