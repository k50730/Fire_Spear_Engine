#include "GameObject.h"
#include <iostream>

GameObject::GameObject()
{
}

GameObject::GameObject(int newID) : id(newID), parent(nullptr)
{
	AddComponent(&transformComponent);
}

GameObject::~GameObject()
{
	/*for (const auto& c : children)
	{
		delete c;
	}
	children.clear();

	for (auto& p : components)
	{
		delete p;
	}

	components.clear();*/
}

void GameObject::SetParent(GameObject& p)
{	
	if (parent == nullptr)
	{
		parent = &p;
		p.AddChild(this);
	}
	else if (parent != nullptr && parent != &p)
	{
		throw std::runtime_error("Can't add 2 parents to 1 gameobject");
	}
}

void GameObject::AddChild(GameObject* child)
{

	if (child->GetParent() == nullptr || child->GetParent() == this)
	{
		for (const auto i : children)
		{
			if (i == child) return;
		}

		children.push_back(child);
		child->SetParent(*this);
	}
	else if (child->GetParent() != nullptr && child->GetParent() != this)
	{
		throw std::runtime_error("Can't add 2 parents to 1 gameobject");
	} 

}

void GameObject::AddComponent(BaseComponent* c)
{
	components.push_back(c);
}

template <typename ComponentName>
ComponentName GameObject::GetComponent() 
{
	BaseComponent::ComponentID id = BaseComponent::ComponentID::NONE;

	if (typeid(ComponentName) == typeid(RenderComponent*))
	{
		id = BaseComponent::ComponentID::Render;
	}
	else if (typeid(ComponentName) == typeid(TransformComponent*))
	{
		id = BaseComponent::ComponentID::Transform;
	}
	else if (typeid(ComponentName) == typeid(LuaComponent*))
	{
		id = BaseComponent::ComponentID::Lua;
	}
	else if (typeid(ComponentName) == typeid(RigidbodyComponent*))
	{
		id = BaseComponent::ComponentID::Rigidbody;
	}
	else if (typeid(ComponentName) == typeid(AudioPlayerComponent*))
	{
		id = BaseComponent::ComponentID::Audio;
	}

	for (const auto& p : components)
	{ 
		if (p->GetComponentID() == id) return static_cast<ComponentName>(p);
	}

	return nullptr;
}

int GameObject::GetID() const
{
	return id;
}

void GameObject::Awake()
{
	if(this->GetComponent<AudioPlayerComponent*>()){}

	for (std::vector<BaseComponent*>::iterator i = components.begin(); i != components.end(); ++i) 
	{
		(*i)->Awake();
	}
}

void GameObject::Start()
{
	for (std::vector<BaseComponent*>::iterator i = components.begin(); i != components.end(); ++i) 
	{
		(*i)->Start();
	}
}

void GameObject::Update(sf::Time msec)
{
	if (this->GetComponent<RigidbodyComponent*>() != nullptr)
	{
		transformComponent.position += this->GetComponent<RigidbodyComponent*>()->position;
	}

	worldTransform = parent != nullptr ? parent->GetWorldTransform() *  transformComponent.matrix: transformComponent.matrix;
	
	for (std::vector<BaseComponent*>::iterator i = components.begin(); i != components.end(); ++i)
	{
		(*i)->Update(msec);
	}

	
		
	Render();
}

void GameObject::LateUpdate(sf::Time msec)
{
	for (std::vector<BaseComponent*>::iterator i = components.begin(); i != components.end(); ++i) 
	{
		(*i)->LateUpdate();
	}
}

void GameObject::Render()
{
	if (GetComponent<RenderComponent*>() != nullptr)
	{
		GetComponent<RenderComponent*>()->position = worldTransform;
	}
}

sf::Transform GameObject::GetWorldTransform() const
{
	return worldTransform;
}

GameObject* GameObject::GetParent() const
{
	return parent;
}

std::vector<GameObject*> GameObject::GetChildren() const
{
	return children;
}
