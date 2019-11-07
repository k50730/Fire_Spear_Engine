// GT_HelloWorldWin32.cpp  
// compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c  

#include <windows.h>  
#include <stdlib.h>  
#include <string.h>  
#include <tchar.h> 
#include "CoreEngine.h"
#include <windowsx.h>

// Global variables  

// The main window class name.  
static TCHAR szWindowClass[] = _T("win32app");

// The string that appears in the application's title bar.  
static TCHAR szTitle[] = _T("Win32 Guided Tour Application");

HINSTANCE hInst;

CoreEngine* engine = new CoreEngine();

// Forward declarations of functions included in this code module:  
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Win32 Guided Tour"),
			NULL);

		return 1;
	}

	hInst = hInstance; // Store instance handle in our global variable  

	// The parameters to CreateWindow explained:  
	// szWindowClass: the name of the application  
	// szTitle: the text that appears in the title bar  
	// WS_OVERLAPPEDWINDOW: the type of window to create  
	// CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)  
	// 500, 100: initial size (width, length)  
	// NULL: the parent of this window  
	// NULL: this application does not have a menu bar  
	// hInstance: the first parameter from WinMain  
	// NULL: not used in this application  

	
	

	if (engine->InitilizeSystem())
	{
		HWND hWnd = CreateWindow(
			szWindowClass,
			szTitle,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT,
			800, 800,
			NULL,
			NULL,
			hInstance,
			NULL
		);

		// The parameters to ShowWindow explained:  
	// hWnd: the value returned from CreateWindow  
	// nCmdShow: the fourth parameter from WinMain  
		ShowWindow(hWnd,
			nCmdShow);
		UpdateWindow(hWnd);


		if (!hWnd)
		{
			MessageBox(NULL,
				_T("Call to CreateWindow failed!"),
				_T("Win32 Guided Tour"),
				NULL);

			return 1;
		}
	}


	

	// Main message loop:  
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}



//  
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)  
//  
//  PURPOSE:  Processes messages for the main window.  
//  
//  WM_PAINT    - Paint the main window  
//  WM_DESTROY  - post a quit message and return  
//  
// 
void MouseMove(HWND hwnd, WPARAM wp, LPARAM lParam) {
	POINTS p;
	HDC hdc;
	p.x = GET_X_LPARAM(lParam);
	p.y = GET_Y_LPARAM(lParam);
	hdc = GetDC(hwnd);

	char text[40];
	sprintf_s(text, "Mouse Position: X= %d, Y= %d     ", p.x, p.y);
	LPCSTR textmsg = (LPCSTR)text; 
	TextOut(hdc,
		5, 80,
		textmsg, _tcslen(textmsg));
	ReleaseDC(hwnd, hdc);
}

void LeftMouseDown(HWND hwnd, WPARAM wp, LPARAM lParam) {
	POINTS p;
	HDC hdc;
	p.x = GET_X_LPARAM(lParam);
	p.y = GET_Y_LPARAM(lParam);
	hdc = GetDC(hwnd);

	char text[40];
	sprintf_s(text, "Left Mouse Down: X= %d, Y= %d     ", p.x, p.y);
	LPCSTR textmsg = (LPCSTR)text;
	TextOut(hdc,
		5, 80,
		textmsg, _tcslen(textmsg));
	ReleaseDC(hwnd, hdc);
}

void LeftMouseUp(HWND hwnd, WPARAM wp, LPARAM lParam) 
{
	POINTS p;
	HDC hdc;
	p.x = GET_X_LPARAM(lParam);
	p.y = GET_Y_LPARAM(lParam);
	hdc = GetDC(hwnd);

	char text[40];
	sprintf_s(text, "Left Mouse Up: X= %d, Y= %d     ", p.x, p.y);
	LPCSTR textmsg = (LPCSTR)text;
	TextOut(hdc,
		5, 80,
		textmsg, _tcslen(textmsg));
	ReleaseDC(hwnd, hdc);
}



void RightMouseDown(HWND hwnd, WPARAM wp, LPARAM lParam) {
	POINTS p;
	HDC hdc;
	p.x = GET_X_LPARAM(lParam);
	p.y = GET_Y_LPARAM(lParam);
	hdc = GetDC(hwnd);

	char text[40];
	sprintf_s(text, "Right Mouse Down: X= %d, Y= %d     ", p.x, p.y);
	LPCSTR textmsg = (LPCSTR)text;
	TextOut(hdc,
		5, 80,
		textmsg, _tcslen(textmsg));
	ReleaseDC(hwnd, hdc);
}

void RightMouseUp(HWND hwnd, WPARAM wp, LPARAM lParam) {
	POINTS p;
	HDC hdc;
	p.x = GET_X_LPARAM(lParam);
	p.y = GET_Y_LPARAM(lParam);
	hdc = GetDC(hwnd);

	char text[40];
	sprintf_s(text, "Right Mouse Up: X= %d, Y= %d     ", p.x, p.y);
	LPCSTR textmsg = (LPCSTR)text;
	TextOut(hdc,
		5, 80,
		textmsg, _tcslen(textmsg));
	ReleaseDC(hwnd, hdc);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR greeting[] = _T("FireSpear Engine - Made by NeZhaS");
	
	switch (message)
	{

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		// Here your application is laid out.    
		// in the top left corner.  
	
		TextOut(hdc,
			5, 5,
			greeting, _tcslen(greeting));
		
	

		TextOut(hdc,
			5, 30,
			engine->ReadCPUArchitecture(), _tcslen(engine->ReadCPUArchitecture()));


		char cpuSpeed[16];
		sprintf_s(cpuSpeed, "CPU Speed: %d", engine->ReadCPUSpeed());

		TextOut(hdc,
			5, 55,
			cpuSpeed, _tcslen(cpuSpeed));

		
		// End application-specific layout section.  
		EndPaint(hWnd, &ps);
		break;

	case WM_MOUSEMOVE:
		MouseMove(hWnd, wParam, lParam);
		break;

	case WM_LBUTTONDOWN:
		LeftMouseDown(hWnd, wParam, lParam);
		break;
	case WM_LBUTTONUP:
		LeftMouseUp(hWnd, wParam, lParam);
		break;

	case WM_RBUTTONDOWN:
		RightMouseDown(hWnd, wParam, lParam);
		break;
	case WM_RBUTTONUP:
		RightMouseUp(hWnd, wParam, lParam);
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



