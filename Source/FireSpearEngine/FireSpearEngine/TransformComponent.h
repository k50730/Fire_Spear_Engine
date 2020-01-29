#pragma once
#include "BaseComponent.h"
#include "SFML/Graphics.hpp"
class TransformComponent : public BaseComponent
{
public:
    TransformComponent();
    void Awake() override;
    void Start() override;
    void Update(sf::Time t) override;
    void LateUpdate() override;

    sf::Vector2f position;
    float rotation;
    sf::Vector2f scale;
    sf::Transform matrix;
};

