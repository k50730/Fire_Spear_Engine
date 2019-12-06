#pragma once
#include "ScriptingComponentInterface.h"
#include "LuaPlus.h"
#include <string>

using namespace std;
using namespace LuaPlus;

class LuaScriptComponent : public ScriptingComponentInterface
{
public:
	LuaScriptComponent();
	void LuaScriptCreate();
	void Start();
	void Update();
	int num;
protected:
	LuaState* state;
	LuaObject LuaTest, LuaNum;
private:
};