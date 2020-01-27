#pragma once
class BaseComponent
{
public:
    enum ComponentID
    {
        NONE,
        Transform,
        Render,
        Lua
    };
    virtual void Awake() = 0;
    virtual void Start() = 0;
    virtual void Update() = 0;
    virtual void LateUpdate() = 0;
    ComponentID GetComponentID() const
    {
        return id;
    };
    
protected:
    ComponentID id;
};

