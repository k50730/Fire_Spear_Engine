function Awake()
end

function Start()
end

function Update(dt)

    if(input.IsKeyDown("R")) then
        transform.SetPosition(600, 400)
    end
    if(input.IsKeyDown("W")) then
        rigidBody.AddForce(0, -50)
    end
    if(input.IsKeyDown("S")) then
        rigidBody.AddForce(0, 50)
    end
    if(input.IsKeyDown("A")) then
        rigidBody.AddForce(-50, 0)
    end
    if(input.IsKeyDown("D")) then
        rigidBody.AddForce(50, 0)
    end
    if(input.IsKeyDown("Space")) then
        rigidBody.Stop();
    end
    if(input.IsKeyDown("G")) then
        gameObject.AddComponent("RigidBodyComponent")
    end

end

function  LateUpdate()
end