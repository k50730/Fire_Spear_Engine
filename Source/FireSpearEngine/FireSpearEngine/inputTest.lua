function Awake()
end

function Start()
end

function Update(dt)

    if(input.IsKeyDown("R")) then
        transform.SetPosition(700, 100)
    end
    if(input.IsKeyDown("W")) then
        transform.AddForce(0, -50)
    end
    if(input.IsKeyDown("S")) then
        transform.AddForce(0, 50)
    end
    if(input.IsKeyDown("A")) then
        transform.AddForce(-50, 0)
    end
    if(input.IsKeyDown("D")) then
        transform.AddForce(50, 0)
    end
end

function  LateUpdate()
end