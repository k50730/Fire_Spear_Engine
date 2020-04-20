#include "ScriptComponent.h"

using namespace LuaPlus;

ScriptComponent::ScriptComponent(std::string _name)
{
	id = BaseComponent::ComponentID::Lua;
	mLuaState = LuaState::Create();
	scriptName = _name;
	name = "..\\..\\Assets\\Scripts\\" + _name;
	isFileAvailable = CheckLua(mLuaState->DoFile(name.c_str()));
}

ScriptComponent::~ScriptComponent()
{
	LuaState::Destroy(mLuaState);
	mLuaState = nullptr;
	delete* mLuaState;
}

void ScriptComponent::Awake()
{
	RegisterFunctions();

	if (isFileAvailable)
	{	
		mLuaState->GetGlobal_Stack("Awake");
		if (mLuaState->IsFunction(-1))
		{
			mLuaState->PCall(0, 1, 0);  //num of parameters, num of return values, error handler
		}
	}
}

void ScriptComponent::Start()
{
	if (isFileAvailable)
	{
		mLuaState->GetGlobal_Stack("Start");
		if (mLuaState->IsFunction(-1))
		{
			mLuaState->PCall(0, 1, 0);  //num of parameters, num of return values, error handler
		}
	}
}

void ScriptComponent::Update(sf::Time dt)
{
	if (isFileAvailable)
	{
		mLuaState->GetGlobal_Stack("Update");
		if (mLuaState->IsFunction(-1))
		{
			mLuaState->PushNumber(dt.asSeconds());
			mLuaState->PCall(1, 1, 0);
		}
	}
}

void ScriptComponent::LateUpdate()
{
}

bool ScriptComponent::CheckLua(int r)
{
	if (r != 0)
	{
		std::cout << ("Can't load " + name);
	}
	return true;
}

std::string ScriptComponent::getScriptName()
{
	return scriptName;
}

void ScriptComponent::RegisterFunctions()
{
	mLuaState->GetGlobals().RegisterDirect("Random", *this, &ScriptComponent::LuaRandom);
	if (owner->hasTransfromComponent)
	{
		transform = mLuaState->GetGlobals().CreateTable("transform");
		transform.SetObject(1, transform);
		transform.RegisterDirect("SetPosition", *this, &ScriptComponent::LuaSetPosition);
		transform.RegisterDirect("SetRotation", *this, &ScriptComponent::LuaSetRotation);
	}
	if (owner->hasRenderComponent)
	{
		render = mLuaState->GetGlobals().CreateTable("render");
		render.SetObject(1, render);
		render.RegisterDirect("SetColor", *this, &ScriptComponent::SetColor);
		render.RegisterDirect("SetSize", *this, &ScriptComponent::SetSize);
		render.RegisterDirect("SetScale", *this, &ScriptComponent::SetScale);
	}
	if (owner->hasRigidbodyComponent)
	{
		input = mLuaState->GetGlobals().CreateTable("input");
		input.SetObject(1, input);
		input.RegisterDirect("IsKeyDown", *this, &ScriptComponent::LuaIsKeyDown);

		rigidBody = mLuaState->GetGlobals().CreateTable("rigidBody");
		rigidBody.SetObject(1, rigidBody);
		rigidBody.RegisterDirect("AddForce", *this, &ScriptComponent::LuaAddForce);
		rigidBody.RegisterDirect("Stop", *this, &ScriptComponent::LuaStop);
		rigidBody.RegisterDirect("ObeyGravity", *this, &ScriptComponent::LuaObeyGravity);
		rigidBody.RegisterDirect("SetMass", *this, &ScriptComponent::LuaSetMass);
		rigidBody.RegisterDirect("SetBounciness", *this, &ScriptComponent::LuaSetBounciness);
	}
	// delete ?
	gameObject = mLuaState->GetGlobals().CreateTable("gameObject");
	gameObject.RegisterDirect("AddComponent", *this, &ScriptComponent::LuaAddComponent);
}


bool ScriptComponent::LuaIsKeyDown(const char* KeyName)
{
	return InputSystem::GetKeyDown(KeyName);
}

float ScriptComponent::LuaRandom(float min, float max)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	
	std::uniform_real_distribution<float> result(min, max);

	return result(mt);
}

void ScriptComponent::SetColor(float r, float g, float b, float a)
{
	if (owner->GetComponent<RenderComponent*>() != nullptr)
	{
		owner->GetComponent<RenderComponent*>()->SetColor(sf::Color(r, g, b, a));
	}
	
}

void ScriptComponent::SetSize(float x, float y)
{
	if (owner->GetComponent<RenderComponent*>() != nullptr)
	{
		owner->GetComponent<RenderComponent*>()->SetSize(sf::Vector2f(x,y));
	}
}

void ScriptComponent::SetScale(float x, float y)
{
	if (owner->GetComponent<RenderComponent*>() != nullptr)
	{
		owner->GetComponent<RenderComponent*>()->SetScale(sf::Vector2f(x, y));
	}
}

void ScriptComponent::LuaSetPosition(float x, float y)
{
	owner->transformComponent.position = sf::Vector2f(x, y);
}

void ScriptComponent::LuaSetRotation(float r)
{
	owner->transformComponent.rotation = r;
}

void ScriptComponent::LuaAddForce(float x, float y)
{
	if (owner->GetComponent<RigidbodyComponent*>() != nullptr)
	{
		owner->GetComponent<RigidbodyComponent*>()->AddForce(sf::Vector2f(x, y));
	}
}

void ScriptComponent::LuaStop()
{
	if (owner->GetComponent<RigidbodyComponent*>() != nullptr)
	{
		owner->GetComponent<RigidbodyComponent*>()->Stop();
	}
}

void ScriptComponent::LuaObeyGravity(bool _obeyGravity)
{
	if (owner->GetComponent<RigidbodyComponent*>() != nullptr)
	{
		owner->GetComponent<RigidbodyComponent*>()->SetObeyGravity(_obeyGravity);
	}
}

void ScriptComponent::LuaSetMass(float _mass)
{
	if (owner->GetComponent<RigidbodyComponent*>() != nullptr)
	{
		owner->GetComponent<RigidbodyComponent*>()->SetMass(_mass);
	}
}

void ScriptComponent::LuaSetBounciness(float _bounciness)
{
	if (owner->GetComponent<RigidbodyComponent*>() != nullptr)
	{
		owner->GetComponent<RigidbodyComponent*>()->SetBounciness(_bounciness);
	}
}

void ScriptComponent::LuaAddComponent(const char* ComponentName)
{
	std::string compName = ComponentName;
	std::cout << compName << "Added" << std::endl;
	if (compName == "TransformComponent")
	{
		owner->AddComponent(new TransformComponent());
	}
	else if (compName == "RenderComponent")
	{
		owner->AddComponent(new RenderComponent());
	}
	else if (compName == "RigidBodyComponent")
	{
		owner->AddComponent(new RigidbodyComponent());
	}
	else if (compName == "AudioComponent")
	{
		owner->AddComponent(new AudioPlayerComponent());
	}
}

void ScriptComponent::LuaRemoveComponent(const char* ComponentName)
{
	std::string compName = ComponentName;
	std::cout << compName << "Removed" << std::endl;
	if (compName == "TransformComponent")
	{
		owner->RemoveComponent(new TransformComponent());
		rigidBody.Unregister("SetPosition");
		rigidBody.Unregister("SetRotation");
	}
	else if (compName == "RenderComponent")
	{
		owner->RemoveComponent(new RenderComponent());
		render.Unregister("SetColor");
		render.Unregister("SetSize");
		render.Unregister("SetScale");
	}
	else if (compName == "RigidBodyComponent")
	{
		owner->RemoveComponent(new RigidbodyComponent());
		input.Unregister("IsKeyDown");
		input.Unregister("AddForce");
		input.Unregister("Stop");
		input.Unregister("ObeyGravity");
		input.Unregister("SetMass");
		input.Unregister("SetBounciness");
	}
	else if (compName == "AudioComponent")
	{
		owner->RemoveComponent(new AudioPlayerComponent());
	}	
}

sf::Vector2f ScriptComponent::LuaGetPosition() const
{
	return owner->transformComponent.position;
}