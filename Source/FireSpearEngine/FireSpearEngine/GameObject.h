#pragma once
#include <SFML/Graphics/Transform.hpp>
#include <vector>
#include "BaseComponent.h"


class GameObject
{
public:
	GameObject();
	~GameObject();
	void SetTransform(const sf::Transform t);
	sf::Transform GetTransform();
	sf::Transform GetWorldTransform();

	void SetParent(GameObject& p);
	void AddChild(GameObject* s);

	void AddComponent(BaseComponent* s);

	virtual void Update(float msec);

protected:
	GameObject* parent;
	sf::Transform worldTransform;
	sf::Transform transform;
	std::vector<GameObject*> children;
	std::vector<BaseComponent*> components;
};

