#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <direct.h>
#include <windows.h>
#include "GameObjectManager.h"
#include "PhysicEngine.h"
#include "RenderComponent.h"
#include "RigidbodyComponent.h"
#include "ScriptComponent.h"
#include <iostream>
#include "ScriptingSystem.h"
#include "InputSystem.h"
#include "SceneManager.h"

class FireSpear
{
public:
	FireSpear();
	~FireSpear();

	void InitilizeSystem(); // initilizing system and play splash screen
	void Run(); // start of every components
	void Pause();
	
	GameObjectManager* gameObjectManager;
	PhysicEngine* physicEngine;
	ScriptingSystem* scriptingSystem;
	InputSystem* inputSystem;
	SceneManager* sceneManager;

private:

	bool IsExiting();

	enum GameState
	{
		Uninitialized, Initialized, ShowingSplash, Paused, ShowingMenu, Playing, Exiting
	};
	GameState _gameState;
	sf::RenderWindow _mainWindow;
	const sf::Time FPS = sf::seconds(1.0f / 60.0f);

	void CreateEngineWindow(std::string windowTitle, int width, int height); // create engine window
	void CreateSplashScreen(sf::RenderWindow& window);//create Splash Screen

    // Checking Computer Requirement
	bool CheckStorage(const DWORDLONG diskSpaceNeeded);
	bool CheckMemory(const DWORDLONG physicalRAMNeeded, const DWORDLONG virtualRAMNeeded);
	bool IsOnlyInstance(LPCTSTR gameTitle);
	bool IsOnlyInstance(sf::RenderWindow& window);
	const char* ReadCPUArchitecture();
	DWORD ReadCPUSpeed();

	void Render();
	void ProcessEvent();
	void InstantiateSystems();
	void Tick(); // where all update functions are
	void Awake();
	void Start();
	void Update(sf::Time deltaTime); //fixed update function
	void FixUpdate();

	void KeyboardInput(sf::Keyboard::Key keyCode, bool isPressed);
};

