
time = 0
 
function Awake()
end

function Start()
end

function Update(dt)

    time = time + dt

    if (time > 10) then
         render.SetColor(Random(0, 255), Random(0, 255), Random(0, 255), Random(0, 255))
         time = 0
    end
end

function  LateUpdate()
end

