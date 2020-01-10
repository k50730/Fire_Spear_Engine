#include "LuaScriptComponent.h"
#include <iostream>


LuaScriptComponent::LuaScriptComponent()
{
	state = LuaState::Create();
}

LuaScriptComponent::~LuaScriptComponent()
{
	LuaState::Destroy(state);
	state = NULL;
}

void LuaScriptComponent::LuaScriptCreate()
{
	state->DoFile("test.lua");
	state->DoString("number = 10");
	globals = state->GetGlobals();
}

void LuaScriptComponent::Start()
{
	LuaTest = state->GetGlobal("Square");
	LuaFunction<int> LuaSquare = LuaTest;
	LuaNum = state->GetGlobal("num");
	num = LuaNum.GetInteger();
	numTest = LuaSquare(5);

	if(LuaTest.IsFunction())
	{ 
	LuaFunction<int> LuaTestF = LuaTest;
	}
	//LuaFunction<int> LuaTest = state->GetGlobal("test");
}

void LuaScriptComponent::Update()
{
	LuaTest = state->GetGlobal("update");
	LuaFunction<int> LuaSquare = LuaTest;


	num++;
	char text[40];
	sprintf_s(text, "Tick:%d " , num);
	LPCSTR textmsg = (LPCSTR)text;

}