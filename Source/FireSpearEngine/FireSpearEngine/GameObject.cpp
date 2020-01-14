#include "GameObject.h"

GameObject::GameObject()
{
	parent = NULL;
}



GameObject::~GameObject() 
{
	for (unsigned int i = 0; i < children.size(); i++)
	{
		delete children[i];
	}
}

void GameObject::SetTransform(const sf::Transform t)
{
	transform = t;
}

sf::Transform GameObject::GetTransform()
{
	return transform;
}

sf::Transform GameObject::GetWorldTransform()
{
	return worldTransform;
}

void GameObject::SetParent(GameObject& p)
{
	parent = &p;
}

void GameObject::AddChild(GameObject* s)
{
	children.push_back(s);
		s->parent = this;
}


void GameObject::AddComponent(BaseComponent* c)
{
	components.push_back(c);
}


void GameObject::Update(float msec) 
{
	if (parent) 
	{ //This node has a parent...
		worldTransform = parent->worldTransform * transform;
	}
	else 
	{ //Root node, world transform is local transform!
		worldTransform = transform;
	}

	for (std::vector<GameObject*>::iterator i = children.begin(); i !=
		children.end(); ++i) {
		(*i)->Update(msec);
	}
}
