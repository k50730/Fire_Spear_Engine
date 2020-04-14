#pragma once
#include "SFML/Graphics.hpp"

class BaseComponent
{
public:
    enum ComponentID
    {
        None,
        Base,
        Transform,
        Render,
        Lua,
        Rigidbody,
        Audio
    };
    virtual void Awake() = 0;
    virtual void Start() = 0;
    virtual void Update(sf::Time deltaTime) = 0;
    virtual void LateUpdate() = 0;
    ComponentID GetComponentID() const
    {
        return id;
    };
    
protected:
    ComponentID id;
};

