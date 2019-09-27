#pragma once
#include <iostream>
#include <string>
#include <direct.h>
#include <stdlib.h>
#include <windows.h>
#include <WinBase.h>

class Initialization
{
public:
	Initialization();



	bool CheckStorage(const DWORDLONG diskSpaceNeeded);
	bool CheckMemory(const DWORDLONG physicalRAMNeeded, const DWORDLONG virtualRAMNeeded);
	bool IsOnlyInstance(LPCTSTR gameTitle);
	char* ReadCPUArchitecture();
	DWORD ReadCPUSpeed();
};

