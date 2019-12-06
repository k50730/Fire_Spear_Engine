#include "LuaScriptComponent.h"


LuaScriptComponent::LuaScriptComponent()
{
}

void LuaScriptComponent::LuaScriptCreate()
{
	state = LuaState::Create();
	state->DoFile("test.lua");
	state->DoString("n = 1000");
	//LuaTest = state->GetGlobals();// .GetByName("test");
}

void LuaScriptComponent::Start()
{
	//auto a = LuaTest.GetByName("test");
	//LuaFunction<int> LuaTestF(a);
	//LuaFunction<int> LuaTestF(state, "test");
	LuaNum = state->GetGlobals().GetByName("n");
	LuaTest = state->GetGlobals().GetByName("testF");
	if(LuaTest.IsFunction())
	{ 
	LuaFunction<int> LuaTestF = LuaTest;
	num = LuaTestF();
	}
	//LuaFunction<int> LuaTest = state->GetGlobal("test");
}