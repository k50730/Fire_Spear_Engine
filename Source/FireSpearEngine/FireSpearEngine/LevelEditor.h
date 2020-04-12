#pragma once
#include "TGUI/TGUI.hpp"
#include <iostream>
#include "FireSpear.h"
#define ChildWindowPtr std::shared_ptr<tgui::ChildWindow>

struct GameObjectEditor
{
	ChildWindowPtr container;
	std::shared_ptr<tgui::EditBox> hierarchyTab;
	int id;
};


struct InspectorEditor
{
	ChildWindowPtr container;
	int id;
};

class LevelEditor
{ 
private:
	FireSpear* engine;
	ChildWindowPtr editor;
	ChildWindowPtr inspector;
	ChildWindowPtr hierarchy;
	void StartEngine();

	void CreateGameObject(std::string name);
	std::vector<GameObjectEditor*> gameObjects;
	int gameObjectId = 0;
public:
	LevelEditor();
	~LevelEditor();
	int Run();
};

