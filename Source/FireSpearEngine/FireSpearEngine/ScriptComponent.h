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
	std::string getScriptName();
	GameObject* owner;

private:
	std::string name;
	std::string scriptName;
	bool CheckLua(int r);
	bool isFileAvailable;
	LuaState* mLuaState;
	void RegisterFunctions();


#pragma region Lua Functions
	LuaObject transform;
	LuaObject render;
	LuaObject input;
	LuaObject rigidBody;
	LuaObject gameObject;

	bool LuaIsKeyDown(const char* KeyName);
	float LuaRandom(float, float);
	//Render
	void SetColor(float r, float g, float b, float);
	void SetSize(float, float);
	void SetScale(float, float);
	//Transform
	void LuaSetPosition(float, float);
	void LuaSetRotation(float);
	//RigidBody
	void LuaAddForce(float x, float y);
	void LuaStop();
	void LuaObeyGravity(bool _obeyGravity);
	void LuaSetMass(float _mass);
	void LuaSetBounciness(float _bounciness);
	//GameObject
	void LuaAddComponent(const char* ComponentName);
	void LuaRemoveComponent(const char* ComponentName);
	sf::Vector2f LuaGetPosition() const;
#pragma endregion
};