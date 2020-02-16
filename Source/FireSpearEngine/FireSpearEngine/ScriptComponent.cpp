#include "ScriptComponent.h"

using namespace LuaPlus;

ScriptComponent::ScriptComponent(std::string _name)
{
	id = BaseComponent::ComponentID::Lua;
	mLuaState = LuaState::Create();
	name = _name;
	isFileAvailable = CheckLua(mLuaState->DoFile(name.c_str()));
}

ScriptComponent::~ScriptComponent()
{
	LuaState::Destroy(mLuaState);
	mLuaState = nullptr;
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

void ScriptComponent::RegisterFunctions()
{
	mLuaState->GetGlobals().RegisterDirect("Random", *this, &ScriptComponent::LuaRandom);

	LuaObject transform = mLuaState->GetGlobals().CreateTable("transform");
	transform.SetObject(1, transform);
	transform.RegisterDirect("SetPosition", *this, &ScriptComponent::LuaSetPosition);
	transform.RegisterDirect("SetRotation", *this, &ScriptComponent::LuaSetRotation);
	

	LuaObject render = mLuaState->GetGlobals().CreateTable("render");
	render.SetObject(1, transform);
	render.RegisterDirect("SetColor", *this, &ScriptComponent::SetColor);
	render.RegisterDirect("SetSize", *this, &ScriptComponent::SetSize);
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

void ScriptComponent::LuaSetPosition(float x, float y)
{
	owner->transformComponent.position = sf::Vector2f(x, y);
}

void ScriptComponent::LuaSetRotation(float r)
{
	owner->transformComponent.rotation = r;
}

sf::Vector2f ScriptComponent::LuaGetPosition() const
{
	return owner->transformComponent.position;
}