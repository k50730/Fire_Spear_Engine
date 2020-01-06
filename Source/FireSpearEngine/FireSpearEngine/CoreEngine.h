#pragma once
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
	char* ReadCPUArchitecture();
	DWORD ReadCPUSpeed();


	bool InitilizeSystem();
	void Run();

	void UpdateSystem();
	void AddSystem();
private:


	bool CreateEngineWindow(string windowTitle, int x, int y, int width, int height);

	const char* m_appName;
	HINSTANCE m_hInst;
	HWND hWnd;
	WNDCLASSEX wcex;
};

