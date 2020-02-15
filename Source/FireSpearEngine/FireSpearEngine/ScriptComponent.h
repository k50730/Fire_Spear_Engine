#pragma once
#include<string>
#include "BaseComponent.h"
#include "LuaPlus.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include "GameObject.h"


class ScriptComponent : public BaseComponent
{
public:
	ScriptComponent(std::string _name);
	~ScriptComponent();

	void Awake() override;
	void Start() override;
	void Update(sf::Time dt) override;
	void LateUpdate() override;
	GameObject* owner;

private:
	lua_State* luaState;
	std::string name;
	bool CheckLua(int r);
	bool isFileAvailable;
	
};