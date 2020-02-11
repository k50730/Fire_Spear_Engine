#pragma once
#include "BaseComponent.h"
class CircleColliderComponent : public BaseComponent
{
public:
	CircleColliderComponent();
	void Awake() override;
	void Start() override;
	void Update(sf::Time deltatIme) override;
	void LateUpdate() override;
};

