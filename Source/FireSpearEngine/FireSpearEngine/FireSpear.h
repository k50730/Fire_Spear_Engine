#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <direct.h>
#include <windows.h>
#include "LuaPlus.h"
#include "../../Actors/LuaScriptComponent.h"
#include "GameObjectManager.h"
#include "RenderComponent.h"
#include <iostream>

class FireSpear
{
public:
	FireSpear();
	~FireSpear();

	// Checking Computer Requirement
	bool CheckStorage(const DWORDLONG diskSpaceNeeded);
	bool CheckMemory(const DWORDLONG physicalRAMNeeded, const DWORDLONG virtualRAMNeeded);
	bool IsOnlyInstance(LPCTSTR gameTitle);
	const char* ReadCPUArchitecture();
	DWORD ReadCPUSpeed();


	void InitilizeSystem(); // initilizing system and play splash screen
	void Start(); // start of every components
	void CreateEngineWindow(string windowTitle, int width, int height); // create engine window
	void CreateSplashScreen(sf::RenderWindow& window);//create Splash Screen
	void Run(); // where update functions are
	void Update(sf::Time deltaTime); //fixed update function
	void Render();
	void ProcessEvent();
	static GameObjectManager gameObjectManager;

	
private:
	bool IsExiting();

	enum GameState
	{
		Uninitialized, Initialized, ShowingSplash, Paused, ShowingMenu, Playing, Exiting
	};
	GameState _gameState;
	sf::RenderWindow _mainWindow;
	const sf::Time FPS = sf::seconds(1.0f / 60.0f);

};

