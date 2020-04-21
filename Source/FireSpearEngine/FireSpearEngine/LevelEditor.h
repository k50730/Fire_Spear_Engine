#pragma once
#include "TGUI/TGUI.hpp"
#include <iostream>
#include "FireSpear.h"
#include <sstream>
#include <string>
#define ChildWindowPtr std::shared_ptr<tgui::ChildWindow>



class InspectorEditor
{
public:
	InspectorEditor(float x, float y, sf::Vector2f p)
	{
		editor = tgui::ChildWindow::create();
		editor->setSize(x, y);
		editor->getRenderer()->setBackgroundColor(sf::Color(255, 230, 171, 255));
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
		positionX->setInputValidator(tgui::EditBox::Validator::UInt);
		transformComponent->add(positionX);

		positionYLabel = tgui::Label::create("position y");
		positionYLabel->setPosition(0, positionXLabel->getSize().y);
		transformComponent->add(positionYLabel);

		positionY = tgui::EditBox::create();
		positionY->setDefaultText(std::to_string(p.y));
		positionY->setPosition(positionYLabel->getSize().x, positionXLabel->getSize().y);
		positionY->setInputValidator(tgui::EditBox::Validator::UInt);
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
		lastItem = componentsBtn->getPosition().y + componentsBtn->getSize().y;
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
		renderComponent->setPosition(0, lastItem + 10);

		sizeXLabel = tgui::Label::create("size x");
		sizeXLabel->setPosition(0, 0);
		renderComponent->add(sizeXLabel);

		sizeX = tgui::EditBox::create();
		sizeX->setPosition(sizeXLabel->getSize().x, 0);
		sizeX->setInputValidator(tgui::EditBox::Validator::UInt);
		sizeX->setDefaultText(std::to_string(gameObject->getSize().x));
		renderComponent->add(sizeX);

		sizeYLabel = tgui::Label::create("size y");
		sizeYLabel->setPosition(0, sizeXLabel->getSize().y);
		renderComponent->add(sizeYLabel);

		sizeY = tgui::EditBox::create();
		sizeY->setDefaultText(std::to_string(gameObject->getSize().y));
		sizeY->setPosition(sizeYLabel->getSize().x, sizeXLabel->getSize().y);
		sizeY->setInputValidator(tgui::EditBox::Validator::UInt);
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

		lastItem = renderComponent->getPosition().y + renderComponent->getSize().y + 20;
		editor->add(renderComponent);

	}

#pragma endregion

#pragma region Rigidbody Component
	public:
		ChildWindowPtr rigidbodyComponent;
		std::shared_ptr<tgui::EditBox> velocityX;
		std::shared_ptr<tgui::EditBox> velocityY;
		std::shared_ptr<tgui::EditBox> mass;
		std::shared_ptr<tgui::CheckBox> checkbox;

		void AddRigidbodyComponent()
		{
			rigidbodyComponent = tgui::ChildWindow::create();
			rigidbodyComponent->setSize(transformComponent->getSize().x, 70);
			rigidbodyComponent->setTitle("Rigidbody");
			rigidbodyComponent->setPosition(0, lastItem + 10);

			velocityLabel = tgui::Label::create("Velocity");
			velocityLabel->setPosition(5, 10);
			rigidbodyComponent->add(velocityLabel);

			velocityX = tgui::EditBox::create();
			velocityX->setDefaultText("0");
			velocityX->setSize(20, 20);
			velocityX->setPosition(70, 5);
			velocityX->setInputValidator(tgui::EditBox::Validator::Float);
			rigidbodyComponent->add(velocityX);

			velocityY = tgui::EditBox::create();
			velocityY->setDefaultText("0");
			velocityY->setSize(20, 20);
			velocityY->setPosition(100, 5);
			velocityY->setInputValidator(tgui::EditBox::Validator::Float);
			rigidbodyComponent->add(velocityY);

			checkbox = tgui::CheckBox::create();
			checkbox->setText("Obbey Gravity");
			checkbox->setChecked(true);
			checkbox->setPosition(150, 5);
			rigidbodyComponent->add(checkbox);

			massLabel = tgui::Label::create("Mass");
			massLabel->setPosition(5, 40);
			rigidbodyComponent->add(massLabel);

			mass = tgui::EditBox::create();
			mass->setDefaultText("1");
			mass->setSize(20, 20);
			mass->setPosition(70, 40);
			mass->setInputValidator(tgui::EditBox::Validator::UInt);
			rigidbodyComponent->add(mass);

			lastItem = rigidbodyComponent->getPosition().y + rigidbodyComponent->getSize().y + 20;
			editor->add(rigidbodyComponent);
		}
private:
	std::shared_ptr<tgui::Label> velocityLabel;
	std::shared_ptr<tgui::Label> massLabel;
#pragma endregion

#pragma region  Script Componet

public:

	ChildWindowPtr scriptComponent;
	void AddScriptComponent(std::string path)
	{
		scriptComponent = tgui::ChildWindow::create();
		scriptComponent->setSize(transformComponent->getSize().x, 25);
		scriptComponent->setTitle("Script");
		scriptComponent->setPosition(0, lastItem + 10);

		scriptName = tgui::Label::create(path);
		scriptComponent->add(scriptName);

		lastItem = scriptComponent->getPosition().y + scriptComponent->getSize().y + 20;
		editor->add(scriptComponent);

	}

private:
	std::shared_ptr<tgui::Label> scriptName;
#pragma endregion

#pragma region Audio Component
public:
	ChildWindowPtr audioComponent;
	void AddAudioComponent(std::string path, GameObject* gameObject)
	{
		audioComponent = tgui::ChildWindow::create();
		audioComponent->setSize(transformComponent->getSize().x, 10);
		audioComponent->setTitle("Audio");
		audioComponent->setPosition(0, lastItem + 10);

		audioComponent = tgui::ChildWindow::create();
		gameObject->AddComponent(new AudioPlayerComponent(path));
		gameObject->hasAudioComponent = true;

		audioCompnentName = tgui::Label::create(path);
		audioComponent->add(audioCompnentName);

		lastItem = audioComponent->getPosition().y + audioComponent->getSize().y + 20;
		editor->add(audioComponent);
	}

private:
	std::shared_ptr<tgui::Label> audioCompnentName;
#pragma endregion

	

public:
	std::shared_ptr<tgui::MenuBar> componentsBtn;

	private:
		float lastItem; // y position of the last item in the inspector list
};

struct GameObjectEditor
{
	ChildWindowPtr container;
	std::shared_ptr<tgui::EditBox> hierarchyTab;
	InspectorEditor* inspectorTab;
	int id;
	bool hasRenderComponent = false;
	bool hasRigidbodyComponent = false;
};

class LevelEditor
{ 
private:
	sf::RenderWindow window;

	ChildWindowPtr editor;
	ChildWindowPtr inspector;
	ChildWindowPtr hierarchy;
	void StartEngine(); // Call when press RUN button
	
	void ClickToolBar(std::string name);
	std::vector<GameObjectEditor*> gameObjects; // game objects in editor
	FireSpear* engine;
	int gameObjectId = 0;
	bool changedMass = false;
	bool changedVelocityX = false;
	bool changedVelocityY = false;
	bool changedObbeyGravity = false;

	std::string OpenFileExplorer(HWND hWnd);
	std::string SaveFileExplorer(HWND hWnd);
	std::shared_ptr<tgui::Button> runBtn;
public:
	LevelEditor(FireSpear* e);
	~LevelEditor();
	int Run();
};


