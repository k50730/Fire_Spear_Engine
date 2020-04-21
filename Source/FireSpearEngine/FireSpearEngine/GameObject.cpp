#include "GameObject.h"
#include "RigidbodyComponent.h"
#include "ScriptComponent.h"

GameObject::GameObject()
{
	compExist = false;
}

GameObject::GameObject(int newID) : id(newID), parent(nullptr)
{
	AddComponent(&transformComponent);

	if (components.empty())
	{
		hasAudioComponent = false;
		hasRenderComponent = false;
		hasScriptComponent = false;
		hasTransfromComponent = false;
		hasRigidbodyComponent = false;
	}
	else
	{
		for (auto c : components) //check hascomponent
		{
			AddHasComponent(c->GetComponentID());
		}
	}
}

GameObject::~GameObject()
{
	for (auto p : components)
	{
		if(p->GetComponentID() != BaseComponent::ComponentID::Transform) // Transform component is not a pointer
		delete p;
	}
	components.clear();
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
	for (auto it : components)
	{
		if (it->GetComponentID() == c->GetComponentID())
			compExist = true;
	}
	if (!compExist)
	{
		components.push_back(c);
		AddHasComponent(c->GetComponentID()); //gameobject tracks component it owns
	}
}

void GameObject::RemoveComponent(int CompnentID)
{
	for (auto c = components.begin(); c != components.end(); ++c)
	{
		if ((*c)->GetComponentID() == CompnentID)
		{
			//components.erase(c);
			components.pop_back();
			std::cout << (*c)->GetComponentID();
		}
	}
}

template <typename ComponentName>
ComponentName GameObject::GetComponent() 
{
	BaseComponent::ComponentID id = BaseComponent::ComponentID::None;

	if (typeid(ComponentName) == typeid(BaseComponent*))
	{
		id = BaseComponent::ComponentID::Base;
	}
	else if (typeid(ComponentName) == typeid(RenderComponent*))
	{
		id = BaseComponent::ComponentID::Render;
	}
	else if (typeid(ComponentName) == typeid(TransformComponent*))
	{
		id = BaseComponent::ComponentID::Transform;
	}
	else if (typeid(ComponentName) == typeid(ScriptComponent*))
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
	// NEVER DELETE THESE LINES
	if (this->GetComponent<RigidbodyComponent*>()) {} 
	if (this->GetComponent<ScriptComponent*>()) {}
	if (this->GetComponent<AudioPlayerComponent*>()) {}


	for (std::vector<BaseComponent*>::iterator i = components.begin(); i != components.end(); ++i) 
	{
		(*i)->Awake();
	}

	worldTransform = parent != nullptr ? parent->GetWorldTransform() * transformComponent.matrix : transformComponent.matrix;
	Render();
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
	worldTransform = parent != nullptr ? parent->GetWorldTransform() * transformComponent.matrix : transformComponent.matrix;
	
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
		GetComponent<RenderComponent*>()->SetTransform(worldTransform);
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

void GameObject::AddHasComponent(BaseComponent::ComponentID id)
{
	switch (id)
	{
	case BaseComponent::ComponentID::Base:
		hasBaseComponent = true;
		break;
	case BaseComponent::ComponentID::Transform:
		hasTransfromComponent = true;
		break;
	case BaseComponent::ComponentID::Render:
		hasRenderComponent = true;
		break;
	case BaseComponent::ComponentID::Lua:
		hasScriptComponent = true;
		break;
	case BaseComponent::ComponentID::Rigidbody:
		hasRigidbodyComponent = true;
		break;
	case BaseComponent::ComponentID::Audio:
		hasAudioComponent = true;
		break;
	default:
		break;
	}
}

void GameObject::RemoveHasComponent(BaseComponent::ComponentID id)
{
	switch (id)
	{
	case BaseComponent::ComponentID::Base:
		hasBaseComponent = false;
		break;
	case BaseComponent::ComponentID::Transform:
		hasTransfromComponent = false;
		break;
	case BaseComponent::ComponentID::Render:
		hasRenderComponent = false;
		break;
	case BaseComponent::ComponentID::Lua:
		hasScriptComponent = false;
		break;
	case BaseComponent::ComponentID::Rigidbody:
		hasRigidbodyComponent = false;
		break;
	case BaseComponent::ComponentID::Audio:
		hasAudioComponent = false;
		break;
	default:
		break;
	}
}

