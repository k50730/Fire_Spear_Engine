#pragma once
#include "BaseComponent.h"
#include "SFML/Graphics.hpp"


class RenderComponent : public BaseComponent
{
public:
	RenderComponent();
	~RenderComponent();

	void Awake();
	void Start();
	void Update(sf::Time t);
	void LateUpdate();
	//get
	const sf::Vector2f GetSize() { return shape.getSize(); }
	const sf::RectangleShape GetShape() { return shape; }
	const sf::Transform GetTransform() { return transform; }
	//set
	void SetColor(sf::Color c);
	void SetTransform(sf::Transform t);
	void SetSize(sf::Vector2f);
	void DrawRectangleShape(sf::Vector2f size);
	void DrawCircleShape(float radius);

	// Change to private later
private:
	sf::RectangleShape shape;
	sf::Transform transform;
};

