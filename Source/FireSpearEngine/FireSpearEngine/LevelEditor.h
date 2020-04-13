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

#pragma region Transform Component
		transformComponent = tgui::ChildWindow::create();
		transformComponent->setSize(x, 60);
		transformComponent->setTitle("Transform");

		positionXLabel = tgui::Label::create("position x");
		positionXLabel->setPosition(0, 0);
		transformComponent->add(positionXLabel);

		positionX = tgui::EditBox::create();
		positionX->setDefaultText(std::to_string(p.x));
		positionX->setPosition(positionXLabel->getSize().x, 0);
		positionX->setInputValidator(tgui::EditBox::Validator::Float);
		transformComponent->add(positionX);

		positionYLabel = tgui::Label::create("position y");
		positionYLabel->setPosition(0, positionXLabel->getSize().y);
		transformComponent->add(positionYLabel);

		positionY = tgui::EditBox::create();
		positionY->setDefaultText(std::to_string(p.y));
		positionY->setPosition(positionYLabel->getSize().x, positionXLabel->getSize().y);
		positionY->setInputValidator(tgui::EditBox::Validator::Float);
		transformComponent->add(positionY);

		editor->add(transformComponent);
#pragma endregion

#pragma region Add Component Button
		componentsBtn = tgui::MenuBar::create();
		componentsBtn->setSize(120, 20);
		componentsBtn->setPosition(0, transformComponent->getSize().y + 25);
		componentsBtn->addMenu("Add Component");
		componentsBtn->addMenuItem("Render Component");
		componentsBtn->connect("MenuItemClicked", &InspectorEditor::AddRenderComponent, this);
		componentsBtn->addMenuItem("Script Component");
		componentsBtn->addMenuItem("Rigidbody Component");
		componentsBtn->addMenuItem("Audio Component");

		editor->add(componentsBtn);
#pragma endregion

	};

	ChildWindowPtr editor;

#pragma region Transform Component
	ChildWindowPtr transformComponent;
	std::shared_ptr<tgui::Label> positionXLabel;
	std::shared_ptr<tgui::EditBox> positionX;
	std::shared_ptr<tgui::Label> positionYLabel;
	std::shared_ptr<tgui::EditBox> positionY;
#pragma endregion

#pragma region Render Component
	ChildWindowPtr renderComponent;
	std::shared_ptr<tgui::Label> sizeXLabel;
	std::shared_ptr<tgui::EditBox> sizeX;
	std::shared_ptr<tgui::Label> sizeYLabel;
	std::shared_ptr<tgui::EditBox> sizeY;

	void AddRenderComponent(std::string name)
	{
		if (name == "Render Component")
		{
			renderComponent = tgui::ChildWindow::create();
			renderComponent->setSize(transformComponent->getSize().x, 60);
			renderComponent->setTitle("Render");
			renderComponent->setPosition(0, componentsBtn->getPosition().y + componentsBtn->getSize().y + 80);

			sizeXLabel = tgui::Label::create("size x");
			sizeXLabel->setPosition(0, 0);
			renderComponent->add(sizeXLabel);

			sizeX = tgui::EditBox::create();
			sizeX->setPosition(sizeXLabel->getSize().x, 0);
			sizeX->setInputValidator(tgui::EditBox::Validator::Float);
			renderComponent->add(sizeX);

			sizeYLabel = tgui::Label::create("size y");
			sizeYLabel->setPosition(0, sizeXLabel->getSize().y);
			renderComponent->add(sizeYLabel);

			sizeY = tgui::EditBox::create();
			sizeY->setPosition(sizeYLabel->getSize().x, sizeXLabel->getSize().y);
			sizeY->setInputValidator(tgui::EditBox::Validator::Float);
			renderComponent->add(sizeY);

			editor->add(renderComponent);
		}
	}

#pragma endregion

	

	std::shared_ptr<tgui::MenuBar> componentsBtn;
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

