#pragma once
#include "BaseComponent.h"
#include "SFML//Graphics.hpp"

class RigidbodyComponent : public BaseComponent
{

public:

	RigidbodyComponent();
	~RigidbodyComponent();
	void Awake() override;
	void Start() override;
	void Update(sf::Time t) override;
	void LateUpdate() override;

	void AddForce(const sf::Vector2f& f);
	void AddImpulse(const sf::Vector2f& i);

	sf::Vector2f position;
	sf::Vector2f velecity;
	sf::Vector2f acceleration; 
	std::vector<sf::Vector2f> forces;
	std::vector<sf::Vector2f> impulse;
	float mass = 1;
	float bounciness = 1; // The bounciness factor (value between 0 and 1, 0 being no bounce, and 1 being super bouncy!)
	bool obeysGravity = true; // Whether or not this body obeys gravity
	sf::Vector2f gravity = sf::Vector2f(0, 9.8f);
};

