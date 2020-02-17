#pragma once
#include "BaseComponent.h"
#include "GameObject.h"

class InputComponent : public BaseComponent
{
public:
	InputComponent();
	~InputComponent();

	void Awake() override;
	void Start() override;
	void Update(sf::Time dt) override;
	void LateUpdate() override;
	GameObject* owner;

	sf::Vector2f vel;
};