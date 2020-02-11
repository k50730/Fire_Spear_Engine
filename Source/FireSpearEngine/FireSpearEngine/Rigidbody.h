//#pragma once
//class Rigidbody
//{
//public:
//    float mass = 1f;                             // Mass of the RigidBody
//    float bounciness = 1;                        // The bounciness factor (value between 0 and 1, 0 being no bounce, and 1 being super bouncy!)
//    bool obeysGravity = true;                    // Whether or not this body obeys gravity
//    Vector2 gravity = new Vector2(0, -9.8f);     // The gravity vector applied to this body
//
//     Vector2 currentVelocity;                     // The current velocity the body is moving at
//    Vector2 maxVelocity = new Vector2(10f, 10f); // The maximum allowed velocity for this object
//
//    public bool grounded;
//
//    private Vector2 totalForces;
//    private PhysicsEngine engine;
//
//    public
//
//    public 
//
//
//    public void AddForce(Vector2 force)
//    {
//        totalForces += force;
//    }
//
//    public void Stop()
//    {
//        currentVelocity = Vector2.zero;
//        totalForces = Vector2.zero;
//    }
//
//    public bool IsGrounded()
//    {
//        grounded = engine.IsGrounded(this);
//        return grounded;
//    }
//
//    /*
//     * Create a bounding box
//     */
//    void SetAABB()
//    {
//        Bounds bound = new Bounds(new Vector2(0, 0), new Vector2(1, 1));
//        Renderer renderer = GetComponent<Renderer>();
//
//        if (renderer)
//        {
//            bound = renderer.bounds;
//        }
//
//        aabb.bLeft = new Vector2(bound.center.x - bound.extents.x, bound.center.y - bound.extents.y);
//        aabb.tRight = new Vector2(bound.center.x + bound.extents.x, bound.center.y + bound.extents.y);
//    }
//
//    void Start() {
//        SetAABB();
//        engine = GameObject.FindWithTag("PhysicsEngine").GetComponent<PhysicsEngine>();
//
//        engine.AddRigidBody(this);
//    }
//
//    /*
//     * update acceleration. velocity, and position every dT seconds
//     */
//    public void Integrate(float dT)
//    {
//        Vector2 acceleration = new Vector2();
//
//        /// 
//        /// ______________ What is the purpose of this part of code?
//        /// 
//        if (obeysGravity && !IsGrounded())
//        {
//            acceleration = gravity;
//        }
//        else
//        {
//            if (Mathf.Abs(currentVelocity.y) < 0.05f) currentVelocity.y = 0;
//        }
//        ///
//        ///
//        ///
//
//        acceleration += totalForces / mass;
//        if (mass == 0)
//            acceleration = Vector2.zero;
//
//        currentVelocity += acceleration * dT;
//
//        Vector2 temp = transform.position;
//        temp += currentVelocity * dT;
//        transform.position = temp;
//        SetAABB();
//
//        totalForces = Vector2.zero;
//    }
//};
//
