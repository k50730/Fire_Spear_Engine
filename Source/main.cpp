#include <iostream>
#include <string>
#include <direct.h>
#include <stdlib.h>
#include <windows.h>
#include <tchar.h>

using namespace std;

#	define GCC_NEW new(_NORMAL_BLOCK,__FILE__, __LINE__)


DWORD ReadCPUSpeed()
{
	DWORD BufSize = sizeof(DWORD);
	DWORD dwMHz = 0;
	DWORD type = REG_DWORD;
	HKEY hKey;

	long lError = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",
		0, KEY_READ, &hKey);

	if (lError == ERROR_SUCCESS)
	{
		RegQueryValueEx(hKey, "~MHz", NULL, &type, (LPBYTE)& dwMHz, &BufSize);
	}
	int temp = (int)dwMHz;
	char* s = new char[10];
	sprintf_s(s, 10, "%d", temp);
	MessageBox(NULL,
		_T(s),
		_T("CPU Speed"),
		NULL);

	return dwMHz;
}
string ReadCPUArchitecture()
{
	char CPUName[255];
	DWORD BufSize2 = sizeof(CPUName);
	DWORD type2 = REG_SZ;
	HKEY hKey2;

	long lError2 = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",
		0, KEY_READ, &hKey2);

	if (lError2 == ERROR_SUCCESS)
	{
		RegQueryValueEx(hKey2, "ProcessorNameString", NULL, &type2, (LPBYTE)& CPUName, &BufSize2);
	}
	MessageBox(NULL,
		_T(CPUName),
		_T("CPU Architecture"),
		NULL);
	return CPUName;
}

// CHECK FOR INSTANCE
bool IsOnlyInstance(LPCTSTR gameTitle)
{
	HANDLE handle = CreateMutex(NULL, TRUE, gameTitle);

	if (GetLastError() != ERROR_SUCCESS)
	{
		HWND hwnd = FindWindow(gameTitle, NULL);
		if (hwnd)
		{
			ShowWindow(hwnd, SW_SHOWNORMAL);
			SetFocus(hwnd);
			SetForegroundWindow(hwnd);
			SetActiveWindow(hwnd);
			return false;
		}
	}

	return true;
}


bool CheckStorage(const DWORDLONG diskSpaceNeeded)
{
	int const drive = _getdrive();
	struct _diskfree_t diskfree;
	_getdiskfree(drive, &diskfree);

	unsigned __int64 const neededClusters = diskSpaceNeeded / ((diskfree.sectors_per_cluster) * diskfree.bytes_per_sector);
	if (diskfree.avail_clusters < neededClusters) 
	{
		MessageBox(NULL,
			_T("CheckStorage Failure: Not enough physical storage."), // THE MESSAGE INSIDE THE WINDOW
			_T("Check Storage Failed"), // THE MESSAGE ON THE TOP
			NULL);
		return false;
	}
	MessageBox(NULL,
		_T("CheckStorage Success"), // THE MESSAGE INSIDE THE WINDOW
		_T("Check Storage Successful"), // THE MESSAGE ON THE TOP
		NULL);
	return true;
}



bool CheckMemory(const DWORDLONG physicalRAMNeeded, const DWORDLONG virtualRAMNeeded)
{

	MEMORYSTATUSEX status;
	GlobalMemoryStatusEx(&status);

	// CHECK PHYSICAL RAM
	if (status.ullTotalPhys < physicalRAMNeeded)
	{

		MessageBox(NULL,
			_T("Not enough physical memory!"),
			_T("CheckMemory Failure"),
			NULL);

		return false;
	}

	// CHECK VIRTUAL RAM
	if (status.ullAvailVirtual < virtualRAMNeeded)
	{

		MessageBox(NULL,
			_T("Not enough virtual memory!"),
			_T("CheckMemory Failure"),
			NULL);

		return false;
	}


	// CHECK CONTIGUIS MEMORY
	char* buff = GCC_NEW char[virtualRAMNeeded];

	if (buff) delete[] buff;
	else
	{

		MessageBox(NULL,
			_T("Not enough contiguous memory!"),
			_T("CheckMemory Failure"),
			NULL);

		return false;
	}
	MessageBox(NULL,
		_T("Enough memory!"),
		_T("CheckMemory Success"),
		NULL);
	return true;
}


LRESULT CALLBACK WindowProcessMessages(HWND hwnd, UINT msg, WPARAM param, LPARAM lparam);

int WINAPI WinMain(HINSTANCE currentInstance, HINSTANCE previousInstance, PSTR cmdLine, INT cmdCount)
{

	// REGISTER WINDOW CLASS
	const char* CLASS_NAME = "MyApplication";
	WNDCLASS wc{};
	wc.hInstance = currentInstance;
	wc.lpszClassName = CLASS_NAME;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpfnWndProc = WindowProcessMessages;
	RegisterClass(&wc);

	if (IsOnlyInstance("MyApplication")) // IF THE NAME IS UNIQUE
	{

		if (CheckMemory(3000, 3000))
		{
			if (CheckStorage(314572800))
			{

				// CREATE WINDOW
				CreateWindow(CLASS_NAME, "Fire Spear",
					WS_OVERLAPPEDWINDOW | WS_VISIBLE, // WINDOW STYLE
					CW_USEDEFAULT, CW_USEDEFAULT, // WINDOW INITIAL POSITION
					800, 800, // WINDOW SIZE
					NULL, NULL, NULL, NULL);
			}
		}

	}

	ReadCPUSpeed();
	ReadCPUArchitecture();


	// WINDOW LOOP
	MSG msg{};
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WindowProcessMessages(HWND hwnd, UINT msg, WPARAM param, LPARAM lparam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	default:
		return DefWindowProc(hwnd, msg, param, lparam);
	}
}


