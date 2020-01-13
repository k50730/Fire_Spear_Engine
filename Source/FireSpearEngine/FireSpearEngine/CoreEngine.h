#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <direct.h>
#include <stdlib.h>
#include <windows.h>
#include <WinBase.h>
#include <string>
#include "LuaPlus.h"
#include "../../Actors/LuaScriptComponent.h"
#include <tchar.h> 
#include "InputInterface.h"

class CoreEngine
{
public:
	CoreEngine();
	~CoreEngine();

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
	void AddSystem();

private:
	bool IsExiting();
	
	enum GameState
	{
		Uninitialized, Initialized, ShowingSplash, Paused, ShowingMenu, Playing, Exiting
	};
	GameState _gameState;
	sf::RenderWindow _mainWindow;

};

