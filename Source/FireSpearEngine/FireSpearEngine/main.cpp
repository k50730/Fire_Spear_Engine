
#include "CoreEngine.h"


//// Global variables  
//
//// The main window class name.  
//static TCHAR szWindowClass[] = _T("win32app");
//
//// The string that appears in the application's title bar.  
//static TCHAR szTitle[] = _T("FireSpace Engine");
//
//HINSTANCE hInst;
//
//CoreEngine* engine = new CoreEngine();
//InputInterface* inputInterface = new InputInterface();
//
//// Forward declarations of functions included in this code module:  
//LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//
//using namespace LuaPlus;
//
//int CALLBACK WinMain(
//	_In_ HINSTANCE hInstance,
//	_In_ HINSTANCE hPrevInstance,
//	_In_ LPSTR     lpCmdLine,
//	_In_ int       nCmdShow
//)
//{
//	//test call Lua code in C++
//	LuaScriptComponent* newScript = new LuaScriptComponent();
//	newScript->LuaScriptCreate();
//	newScript->Start();
//
//	// This is called during the initialization of your application.
//	LuaState* pLuaState = LuaState::Create();
//	// This is done during the destruction of your application.
//	WNDCLASSEX wcex;
//
//	wcex.cbSize = sizeof(WNDCLASSEX);
//	wcex.style = CS_HREDRAW | CS_VREDRAW;
//	wcex.lpfnWndProc = WndProc;
//	wcex.cbClsExtra = 0;
//	wcex.cbWndExtra = 0;
//	wcex.hInstance = hInstance;
//	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
//	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
//	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
//	wcex.lpszMenuName = NULL;
//	wcex.lpszClassName = szWindowClass;
//	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
//
//	if (!RegisterClassEx(&wcex))
//	{
//		MessageBox(NULL,
//			_T("Call to RegisterClassEx failed!"),
//			_T("Win32 Guided Tour"),
//			NULL);
//
//		return 1;
//	}
//
//	hInst = hInstance; // Store instance handle in our global variable  
//
//	// The parameters to CreateWindow explained:  
//	// szWindowClass: the name of the application  
//	// szTitle: the text that appears in the title bar  
//	// WS_OVERLAPPEDWINDOW: the type of window to create  
//	// CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)  
//	// 500, 100: initial size (width, length)  
//	// NULL: the parent of this window  
//	// NULL: this application does not have a menu bar  
//	// hInstance: the first parameter from WinMain  
//	// NULL: not used in this application  
//
//	HWND hWnd = CreateWindow(
//		szWindowClass,
//		szTitle,
//		WS_OVERLAPPEDWINDOW,
//		CW_USEDEFAULT, CW_USEDEFAULT,
//		800, 800,
//		NULL,
//		NULL,
//		hInstance,
//		NULL
//	);
//	
//
//	if (engine->InitilizeSystem())
//	{
//	
//
//		// The parameters to ShowWindow explained:  
//	// hWnd: the value returned from CreateWindow  
//	// nCmdShow: the fourth parameter from WinMain  
//		ShowWindow(hWnd,
//			nCmdShow);
//		UpdateWindow(hWnd);
//
//
//		if (!hWnd)
//		{
//			MessageBox(NULL,
//				_T("Call to CreateWindow failed!"),
//				_T("Win32 Guided Tour"),
//				NULL);
//
//			return 1;
//		}
//	}
//
//
//	// Main message loop:  
//	MSG msg = {0};
//	while (msg.message != WM_QUIT)
//	{
//		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
//		{
//			TranslateMessage(&msg);
//			DispatchMessage(&msg);
//		}
//		
//		newScript->Update(hWnd);
//	}
//
//	LuaState::Destroy(pLuaState);
//	pLuaState = NULL;
//
//	return (int)msg.wParam;
//}
//
//
//
////  
////  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)  
////  
////  PURPOSE:  Processes messages for the main window.  
////  
////  WM_PAINT    - Paint the main window  
////  WM_DESTROY  - post a quit message and return  
////  
//// 
//
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	PAINTSTRUCT ps;
//	HDC hdc;
//	TCHAR greeting[] = _T("FireSpear Engine - Made by NeZhaS");
//
//	switch (message)
//	{
//
//	case WM_PAINT:
//		hdc = BeginPaint(hWnd, &ps);
//
//		// Here your application is laid out.    
//		// in the top left corner.  
//	
//		TextOut(hdc,
//			5, 5,
//			greeting, _tcslen(greeting));
//		
//		TextOut(hdc,
//			5, 30,
//			engine->ReadCPUArchitecture(), _tcslen(engine->ReadCPUArchitecture()));
//
//
//		char cpuSpeed[16];
//		sprintf_s(cpuSpeed, "CPU Speed: %d", engine->ReadCPUSpeed());
//
//		TextOut(hdc,
//			5, 55,
//			cpuSpeed, _tcslen(cpuSpeed));
//
//		
//		// End application-specific layout section.  
//		EndPaint(hWnd, &ps);
//		break;
//
//	case WM_MOUSEMOVE:
//		inputInterface->MouseMove(hWnd, wParam, lParam);
//		break;
//
//	case WM_LBUTTONDOWN:
//		inputInterface->LeftMouseDown(hWnd, wParam, lParam);
//		break;
//	case WM_LBUTTONUP:
//		inputInterface->LeftMouseUp(hWnd, wParam, lParam);
//		break;
//
//	case WM_RBUTTONDOWN:
//		inputInterface->RightMouseDown(hWnd, wParam, lParam);
//		break;
//	case WM_RBUTTONUP:
//		inputInterface->RightMouseUp(hWnd, wParam, lParam);
//		break;
//	case WM_KEYDOWN:
//		inputInterface->KeyDown(hWnd, wParam, lParam);
//		break;
//	case WM_KEYUP:
//		inputInterface->KeyUp(hWnd, wParam, lParam);
//		break;
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		break;
//		
//	default:
//		return DefWindowProc(hWnd, message, wParam, lParam);
//		break;
//	}
//
//	return 0;
//}



void main() 
{
	CoreEngine* engine = new CoreEngine();

	if (engine->InitilizeSystem())
	{
		engine->Run();
	}

	delete engine;
	return;
}