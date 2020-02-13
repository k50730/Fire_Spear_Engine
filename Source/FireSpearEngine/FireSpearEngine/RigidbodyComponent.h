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

	sf::Vector2f velecity;
	float mass = 1;
	float bounciness = 0.8f; // The bounciness factor (value between 0 and 1, 0 being no bounce, and 1 being super bouncy!)
	bool obeysGravity = true; // Whether or not this body obeys gravity
	sf::Vector2f gravity = sf::Vector2f(0, 98.0f);	
	bool grounded = false;
	
	struct AABB
	{
		sf::Vector2f bLeft;
		sf::Vector2f tRight;
	};

	void AddForce(sf::Vector2f force);
	void Stop();
	void Integrate(float);

	AABB aabb;
	GameObject* owner;
private:
	void SetAABB();
	sf::Vector2f totalForces;
};

