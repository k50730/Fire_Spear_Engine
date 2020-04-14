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
		transformComponent->setSize(x, 40);
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

		componentsBtn->addMenuItem("Script Component");
		componentsBtn->addMenuItem("Rigidbody Component");
		componentsBtn->addMenuItem("Audio Component");

		editor->add(componentsBtn);
#pragma endregion

	};
	ChildWindowPtr editor;

#pragma region Transform Component
public:
	ChildWindowPtr transformComponent;
	std::shared_ptr<tgui::EditBox> positionX;
	std::shared_ptr<tgui::EditBox> positionY;
private:
	std::shared_ptr<tgui::Label> positionXLabel;
	std::shared_ptr<tgui::Label> positionYLabel;
	
#pragma endregion

#pragma region Render Component
public:
	ChildWindowPtr renderComponent;
	std::shared_ptr<tgui::EditBox> sizeX;
	std::shared_ptr<tgui::EditBox> sizeY;
	std::shared_ptr<tgui::Slider> rSlider;
	std::shared_ptr<tgui::Slider> gSlider;
	std::shared_ptr<tgui::Slider> bSlider;
	std::shared_ptr<tgui::Slider> aSlider;
private:
	std::shared_ptr<tgui::Label> sizeXLabel;
	std::shared_ptr<tgui::Label> sizeYLabel;
	std::shared_ptr<tgui::Label> rLabel;
	std::shared_ptr<tgui::Label> gLabel;
	std::shared_ptr<tgui::Label> bLabel;
	std::shared_ptr<tgui::Label> aLabel;
	
public:

	void AddRenderComponent(ChildWindowPtr gameObject)
	{
	
		gameObject->setSize(100, 100);
		gameObject->getRenderer()->setBackgroundColor(sf::Color::Red);

		renderComponent = tgui::ChildWindow::create();
		renderComponent->setSize(transformComponent->getSize().x, 150);
		renderComponent->setTitle("Render");
		renderComponent->setPosition(0, componentsBtn->getPosition().y + componentsBtn->getSize().y + 80);

		sizeXLabel = tgui::Label::create("size x");
		sizeXLabel->setPosition(0, 0);
		renderComponent->add(sizeXLabel);

		sizeX = tgui::EditBox::create();
		sizeX->setPosition(sizeXLabel->getSize().x, 0);
		sizeX->setInputValidator(tgui::EditBox::Validator::Float);
		sizeX->setDefaultText(std::to_string(gameObject->getSize().x));
		renderComponent->add(sizeX);

		sizeYLabel = tgui::Label::create("size y");
		sizeYLabel->setPosition(0, sizeXLabel->getSize().y);
		renderComponent->add(sizeYLabel);

		sizeY = tgui::EditBox::create();
		sizeY->setDefaultText(std::to_string(gameObject->getSize().y));
		sizeY->setPosition(sizeYLabel->getSize().x, sizeXLabel->getSize().y);
		sizeY->setInputValidator(tgui::EditBox::Validator::Float);
		renderComponent->add(sizeY);

		rLabel = tgui::Label::create("R");
		rLabel->setPosition(5, sizeYLabel->getSize().y + sizeYLabel->getPosition().y + 10);
		renderComponent->add(rLabel);
		rSlider = tgui::Slider::create();
		rSlider->setPosition(40, sizeYLabel->getSize().y + sizeYLabel->getPosition().y + 10);
		rSlider->setSize(160, 15);
		rSlider->setMinimum(0);
		rSlider->setMaximum(255);
		rSlider->setValue(255);
		renderComponent->add(rSlider);

		gLabel = tgui::Label::create("G");
		gLabel->setPosition(5, rSlider->getSize().y + rSlider->getPosition().y + 10);
		renderComponent->add(gLabel);
		gSlider = tgui::Slider::create();
		gSlider->setPosition(40, rSlider->getSize().y + rSlider->getPosition().y + 10);
		gSlider->setSize(160, 15);
		gSlider->setMinimum(0);
		gSlider->setMaximum(255);
		gSlider->setValue(0);
		renderComponent->add(gSlider);

		bLabel = tgui::Label::create("B");
		bLabel->setPosition(5, gSlider->getSize().y + gSlider->getPosition().y + 10);
		renderComponent->add(bLabel);
		bSlider = tgui::Slider::create();
		bSlider->setPosition(40, gSlider->getSize().y + gSlider->getPosition().y + 10);
		bSlider->setSize(160, 15);
		bSlider->setMinimum(0);
		bSlider->setMaximum(255);
		bSlider->setValue(0);
		renderComponent->add(bSlider);

		aLabel = tgui::Label::create("A");
		aLabel->setPosition(5, bSlider->getSize().y + bSlider->getPosition().y + 10);
		renderComponent->add(aLabel);
		aSlider = tgui::Slider::create();
		aSlider->setPosition(40, bSlider->getSize().y + bSlider->getPosition().y + 10);
		aSlider->setSize(160, 15);
		aSlider->setMinimum(0);
		aSlider->setMaximum(255);
		aSlider->setValue(255);
		renderComponent->add(aSlider);

		editor->add(renderComponent);
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
	bool hasRenderComponent = false;
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

