#pragma once
#include "ScriptingComponentInterface.h"
#include "LuaPlus.h"
#include <string>
#include <Windows.h>

using namespace std;
using namespace LuaPlus;

class LuaScriptComponent : public ScriptingComponentInterface
{
public:
	LuaScriptComponent();
	~LuaScriptComponent();
	void LuaScriptCreate();
	void Start();
	void Update();
	int num, numTest;
protected:
	LuaState* state;
	LuaObject LuaTest, LuaNum, globals;
private:
};