#pragma once
#include <string>
#include "BaseComponent.h"
#include "LuaPlus.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include "GameObject.h"
#include "InputSystem.h"
#include "RigidbodyComponent.h"
#include <random>

using namespace LuaPlus;

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
	std::string name;
	bool CheckLua(int r);
	bool isFileAvailable;
	LuaState* mLuaState;
	void RegisterFunctions();

#pragma region Lua Functions
	bool LuaIsKeyDown(const char* KeyName);
	float LusTest(float x);
	float LuaRandom(float, float);
	void SetColor(float r, float g, float b, float);
	void SetSize(float, float);
	void LuaSetPosition(float, float);
	void LuaSetRotation(float);
	void LuaAddForce(float x, float y);
	sf::Vector2f LuaGetPosition() const;
#pragma endregion
};