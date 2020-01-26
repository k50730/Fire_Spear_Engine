#pragma once
#include "BaseComponent.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "SFML/Graphics.hpp"
#include <vector>


class GameObject
{
public:
	GameObject();
	GameObject(int newID);
	~GameObject();

	void SetParent(GameObject& parent);
	void AddChild(GameObject* child);
	void AddComponent(BaseComponent* component);

	template <typename ComponentName>
	ComponentName GetComponent();

	int GetID() const;

	void Update(sf::Time msec);
	void Awake();
	void Start();
	void LateUpdate(sf::Time msec);
	void Render();
	TransformComponent transformComponent;

	sf::Transform GetWorldTransform() const;
	GameObject* GetParent() const;
	std::vector<GameObject*> GetChildren() const;
private:
	
	sf::Transform worldTransform;
	int id; // each object has an unique id
	GameObject* parent;
	std::vector<GameObject*> children;
	std::vector<BaseComponent*> components;

};
