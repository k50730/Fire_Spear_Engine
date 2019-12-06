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

void LuaScriptComponent::Update(HWND hWnd)
{
	LuaTest = state->GetGlobal("update");
	LuaFunction<int> LuaSquare = LuaTest;
	HDC hdc;
	hdc = GetDC(hWnd);

	num++;
	char text[40];
	sprintf_s(text, "Tick:%d " , num);
	LPCSTR textmsg = (LPCSTR)text;
	
	TextOut(hdc,
		25, 200,
		textmsg, 9);
	ReleaseDC(hWnd, hdc);
}