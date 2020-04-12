#pragma once
#include "TGUI/TGUI.hpp"
#include <iostream>
#include "FireSpear.h"
#define ChildWindowPtr std::shared_ptr<tgui::ChildWindow>
class LevelEditor
{ 
private:
	FireSpear* engine;
	ChildWindowPtr editor;
	ChildWindowPtr inspector;
	ChildWindowPtr hierarchy;
	void StartEngine();

	void CreateGameObject(std::string name);

	int gameObjectId = 0;
public:
	LevelEditor();
	~LevelEditor();
	int Run();
};

