#include "LuaComponent.h"

LuaComponent::LuaComponent()
{
	id = BaseComponent::ComponentID::Lua;
	state = LuaPlus::LuaState::Create();
}

void LuaComponent::Awake()
{
	/*LuaScriptComponent* newScript = new LuaScriptComponent();
	newScript->LuaScriptCreate();
	newScript->Start();
	newScript->Update();
	LuaState* pLuaState = LuaState::Create();

	LuaState::Destroy(pLuaState);
	pLuaState = NULL;*/
}

void LuaComponent::Start()
{
}

void LuaComponent::Update(sf::Time t)
{
}

void LuaComponent::LateUpdate()
{
}
