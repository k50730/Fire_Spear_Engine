#pragma once
#include "BaseComponent.h"
#include "LuaPlus.h"

class LuaComponent : public BaseComponent
{
public:
	LuaComponent();

	void Awake() override;
	void Start() override;
	void Update(sf::Time a) override;
	void LateUpdate() override;

private:

	LuaPlus::LuaState* state;
};

