#include "ScriptComponent.h"


ScriptComponent::ScriptComponent(std::string _name)
{
	id = BaseComponent::ComponentID::Lua;
	luaState = luaL_newstate();
	name = _name;
	isFileAvailable = CheckLua(luaL_dofile(luaState, name.c_str()));
}

ScriptComponent::~ScriptComponent()
{
	lua_close(luaState);
}

void ScriptComponent::Awake()
{
}

void ScriptComponent::Start()
{
	if (isFileAvailable)
	{
		lua_getglobal(luaState, "Start");
		if (lua_isfunction(luaState, -1))
		{
			lua_pcall(luaState, 0, 1, 0);  // lua state, num of parameters, num of return values, error handler
		}
	}
}

void ScriptComponent::Update(sf::Time dt)
{
	if (isFileAvailable)
	{
		lua_getglobal(luaState, "Update");
		if (lua_isfunction(luaState, -1))
		{
			lua_pushnumber(luaState, dt.asSeconds());
			lua_pcall(luaState, 1, 1, 0);
			lua_Number t = lua_tonumber(luaState, -1);
			std::cout << "Test Lua Update " << (float)t << std::endl;
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