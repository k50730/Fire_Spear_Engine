#pragma once
#include "BaseComponent.h"
#include "SFML/Graphics.hpp"
#include "GameObjectManager.h"
#include <cmath> 

class RigidbodyComponent : public BaseComponent
{

public:

	RigidbodyComponent();
	~RigidbodyComponent();
	void Awake() override;
	void Start() override;
	void Update(sf::Time t) override;
	void LateUpdate() override;

	sf::Vector2f velocity;
	float mass = 1;
	float bounciness = 0.8f; // The bounciness factor (value between 0 and 1, 0 being no bounce, and 1 being super bouncy!)
	bool obeysGravity = true; // Whether or not this body obeys gravity
	sf::Vector2f gravity = sf::Vector2f(0, 98.0f);	
	bool grounded = false;
	bool isTrigger = false;

	struct AABB
	{
		sf::Vector2f bLeft;
		sf::Vector2f tRight;
	};

	void AddForce(sf::Vector2f force);
	void Stop();
	void Integrate(float);
	//Get
	const float GetMass() const { return mass; }
	//Set
	void SetObeyGravity(bool _obeyGravity) { obeysGravity = _obeyGravity; }
	void SetMass(float _mass) { mass = _mass; }
	void SetBounciness(float _bounciness) { bounciness = _bounciness; }
	void IsTrigger(bool _isTrigger) { isTrigger = _isTrigger; }

	AABB aabb;
	GameObject* owner;
private:
	void SetAABB();
	sf::Vector2f totalForces;
};

