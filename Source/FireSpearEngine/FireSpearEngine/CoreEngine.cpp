#include "CoreEngine.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 768
#define WINDOW_POSX 200
#define WINDOW_POSY 200



using namespace std;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

CoreEngine::CoreEngine()
{

}

CoreEngine::~CoreEngine() 
{
	m_hInst = NULL;
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

const char* CoreEngine::ReadCPUArchitecture()
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
	
	
	//OutputDebugString();
	//utputDebugString(CPUName);
	//OutputDebugStringW(L"\n");
	//printf("CPU ARCHITECTURE: %s\n", CPUName);
	return CPUName;
}

DWORD CoreEngine::ReadCPUSpeed()
{
	
	DWORD dwMHz;
	DWORD BufSize = sizeof(dwMHz);
	DWORD type = REG_DWORD;
	HKEY hKey;

	long lError = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",
		0, KEY_READ, &hKey);

	if (lError == ERROR_SUCCESS)
	{
		RegQueryValueEx(hKey, "~MHz", NULL, &type, (LPBYTE)& dwMHz, &BufSize);
	}
	


	//printf("CPU SPEED: %d\n", dwMHz);
	//OutputDebugString(to_string(temp).c_str());
	//OutputDebugStringW(L"\n");

	return dwMHz;
}

bool CoreEngine::InitilizeSystem()
{
	//if (IsOnlyInstance("Win32 Guided Tour Application")) // IF THE NAME IS UNIQUE
	//{

	//	if (CheckMemory(3000, 3000))
	//	{
	//		if (CheckStorage(3145))
	//		{
	//			//ReadCPUSpeed();
	//			//ReadCPUArchitecture();
	//			return true;
	//		}
	//	}
	//}
	
	if (!CreateEngineWindow("FireSpear Engine", WINDOW_POSX, WINDOW_POSY, SCREEN_WIDTH, SCREEN_HEIGHT))
	{
		return false;
	}

	return true;
}

void CoreEngine::Run()
{

	LuaScriptComponent* newScript = new LuaScriptComponent();
	newScript->LuaScriptCreate();
	newScript->Start();

	LuaState* pLuaState = LuaState::Create();

	// Main message loop:  
	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else 
		{
			// update and render function at
			newScript->Update(hWnd);
		}
	}

	LuaState::Destroy(pLuaState);
	pLuaState = NULL;

}


bool CoreEngine::CreateEngineWindow(string windowTitle, int x, int y, int width, int height)
{
	

	m_appName = windowTitle.c_str();

	wcex.cbSize			= sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= m_hInst;
	wcex.hIcon			= LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hIconSm		= wcex.hIcon;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName   = NULL;
	wcex.lpszClassName  = m_appName;
	

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			"Call to RegisterClassEx failed!",
			"Win32 Guided Tour",
			NULL);

		return false;
	}

	// Create Engine Window 
	hWnd = CreateWindow(
		m_appName,
		m_appName,
		WS_OVERLAPPEDWINDOW, // Application Style
		//CW_USEDEFAULT, CW_USEDEFAULT, // set X pos and Y pos
		x, y,
		width, height,
		NULL,
		NULL,
		m_hInst,
		NULL
	);

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	if (!hWnd)
	{
		MessageBox(NULL, "Window Creation failed", "Error", MB_OK);
		PostQuitMessage(0);

		return false;
	}

	return true;

}


void CoreEngine::UpdateSystem()
{
}

void CoreEngine::AddSystem()
{
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR greeting[] = ("FireSpear Engine - Made by NeZhaS");
	InputInterface* inputInterface = new InputInterface();

	switch (message)
	{

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		// Here your application is laid out.    
		// in the top left corner.  

		TextOut(hdc,
			5, 5,
			greeting, _tcslen(greeting));

		/*TextOut(hdc,
			5, 30,
			CoreEngine::ReadCPUArchitecture(), _tcslen(CoreEngine::ReadCPUArchitecture));

		char cpuSpeed[16];
		sprintf_s(cpuSpeed, "CPU Speed: %d", CoreEngine::ReadCPUSpeed);

		TextOut(hdc,
			5, 55,
			cpuSpeed, _tcslen(cpuSpeed));*/


		// End application-specific layout section.  
		EndPaint(hWnd, &ps);
		break;

	case WM_MOUSEMOVE:
		inputInterface->MouseMove(hWnd, wParam, lParam);
		break;

	case WM_LBUTTONDOWN:
		inputInterface->LeftMouseDown(hWnd, wParam, lParam);
		break;
	case WM_LBUTTONUP:
		inputInterface->LeftMouseUp(hWnd, wParam, lParam);
		break;

	case WM_RBUTTONDOWN:
		inputInterface->RightMouseDown(hWnd, wParam, lParam);
		break;
	case WM_RBUTTONUP:
		inputInterface->RightMouseUp(hWnd, wParam, lParam);
		break;
	case WM_KEYDOWN:
		inputInterface->KeyDown(hWnd, wParam, lParam);
		break;
	case WM_KEYUP:
		inputInterface->KeyUp(hWnd, wParam, lParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}

