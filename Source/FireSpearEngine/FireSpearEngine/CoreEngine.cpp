#include "CoreEngine.h"


using namespace std;

CoreEngine::CoreEngine()
{
}

bool CoreEngine::CheckStorage(const DWORDLONG diskSpaceNeeded)
{
	int const drive = _getdrive();
	struct _diskfree_t diskfree;
	_getdiskfree(drive, &diskfree);

	unsigned __int64 const neededClusters = diskSpaceNeeded / ((diskfree.sectors_per_cluster) * diskfree.bytes_per_sector);
	if (diskfree.avail_clusters < neededClusters)
	{
		MessageBox(NULL,
			"CheckStorage Failure: Not enough physical storage.", // THE MESSAGE INSIDE THE WINDOW
			"Check Storage Failed", // THE MESSAGE ON THE TOP
			NULL);
		return false;
	}
	cout << "CHECK STORAGE SUCCESS" << endl;
	return true;
}

bool CoreEngine::CheckMemory(const DWORDLONG physicalRAMNeeded, const DWORDLONG virtualRAMNeeded)
{
	MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatusEx(&status);

	
	// CHECK PHYSICAL RAM
	if (status.ullTotalPhys < physicalRAMNeeded)
	{

		MessageBox(NULL,
			"Not enough physical memory!",
			"CheckMemory Failure",
			NULL);

		return false;
	}

	// CHECK VIRTUAL RAM
	if (status.ullAvailVirtual < virtualRAMNeeded)
	{

		MessageBox(NULL,
			"Not enough virtual memory!",
			"CheckMemory Failure",
			NULL);

		return false;
	}


	// CHECK CONTIGUIS MEMORY
	char* buff = new char[virtualRAMNeeded];

	if (buff) delete[] buff;
	else
	{

		MessageBox(NULL,
			"Not enough contiguous memory!",
			"CheckMemory Failure",
			NULL);

		return false;
	}
	OutputDebugString("CHECK MEMORY SUCCESS");
	OutputDebugStringW(L"\n");
	/*cout << "CHECK MEMORY SUCCESS" << endl;

	printf("Available RAM: %I64d \n", status.ullAvailPhys / 1048576);
	printf("Available Virtual Memory: %I64d \n", status.ullAvailVirtual / 1048576);*/

	
	return true;
}

bool CoreEngine::IsOnlyInstance(LPCTSTR gameTitle)
{
	HANDLE handle = CreateMutex(NULL, TRUE, gameTitle);

	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		HWND hwnd = FindWindow(gameTitle, NULL);
		if (hwnd)
		{

			MessageBox(NULL,
				"There is another instance",
				"Muti-Instances Detected",
				NULL);

			ShowWindow(hwnd, SW_SHOWNORMAL);
			SetFocus(hwnd);
			SetForegroundWindow(hwnd);
			SetActiveWindow(hwnd);
			return false;
		}
		MessageBox(NULL,
			"There is another instance",
			"Muti-Instances Detected",
			NULL);
		return false;
	}
	OutputDebugString("CHECK MUTI-INSTANCES SUCCESS");
	OutputDebugStringW(L"\n");
	//cout << "CHECK MUTI-INSTANCES SUCCESS" << endl;
	return true;
}

char* CoreEngine::ReadCPUArchitecture()
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

	OutputDebugString("CPU ARCHITECTURE: ");
	OutputDebugString(CPUName);
	OutputDebugStringW(L"\n");
	//printf("CPU ARCHITECTURE: %s\n", CPUName);
	return CPUName;
}

DWORD CoreEngine::ReadCPUSpeed()
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

	//printf("CPU SPEED: %d\n", dwMHz);
	OutputDebugString(to_string(temp).c_str());
	OutputDebugStringW(L"\n");
	return dwMHz;
}

bool CoreEngine::InitilizeSystem()
{
	if (IsOnlyInstance("MyApplication")) // IF THE NAME IS UNIQUE
	{

		if (CheckMemory(3000, 3000))
		{
			if (CheckStorage(3145))
			{
				ReadCPUSpeed();
				ReadCPUArchitecture();
				return true;
			}
		}
	}

	return false;
}

void CoreEngine::UpdateSystem()
{
}

void CoreEngine::AddSystem()
{
}
