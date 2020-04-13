#pragma once
#include "TGUI/TGUI.hpp"
#include <iostream>
#include "FireSpear.h"
#define ChildWindowPtr std::shared_ptr<tgui::ChildWindow>




class InspectorEditor
{
public:
	InspectorEditor(float x, float y, sf::Vector2f p)
	{
		editor = tgui::ChildWindow::create();
		editor->setSize(x, y);
		editor->getRenderer()->setBackgroundColor(sf::Color::Red);
		editor->setTitle("Game Object");

		transformComponent = tgui::ChildWindow::create();
		transformComponent->setSize(x, 60);
		transformComponent->setTitle("Transform");

		positionXLabel = tgui::Label::create("position x");
		positionXLabel->setPosition(0, 0);
		transformComponent->add(positionXLabel);

		positionX = tgui::EditBox::create();
		positionX->setDefaultText(std::to_string(p.x));
		positionX->setPosition(positionXLabel->getSize().x, 0);
		positionX->setInputValidator(tgui::EditBox::Validator::Int);
		transformComponent->add(positionX);

		positionYLabel = tgui::Label::create("position y");
		positionYLabel->setPosition(0, positionXLabel->getSize().y);
		transformComponent->add(positionYLabel);

		positionY = tgui::EditBox::create();
		positionY->setDefaultText(std::to_string(p.y));
		positionY->setPosition(positionYLabel->getSize().x, positionXLabel->getSize().y);
		positionY->setInputValidator(tgui::EditBox::Validator::Int);
		transformComponent->add(positionY);

		editor->add(transformComponent);
	};

	ChildWindowPtr editor;

public:
	ChildWindowPtr transformComponent;
	std::shared_ptr<tgui::Label> positionXLabel;
	std::shared_ptr<tgui::EditBox> positionX;
	std::shared_ptr<tgui::Label> positionYLabel;
	std::shared_ptr<tgui::EditBox> positionY;

};

struct GameObjectEditor
{
	ChildWindowPtr container;
	std::shared_ptr<tgui::EditBox> hierarchyTab;
	InspectorEditor* inspectorTab;
	int id;
};

class LevelEditor
{ 
private:
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

