#include <iostream>
#include <string>
#include <direct.h>
#include <stdlib.h>
#include <windows.h>
#include <tchar.h>
#include <WinBase.h>
#include <sstream>
#include <iomanip>

#include "CoreEngine.h"

using namespace std;

#	define GCC_NEW new(_NORMAL_BLOCK,__FILE__, __LINE__)


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

	CoreEngine* engine = new CoreEngine();


	if (engine->InitilizeSystem())
	{
		// CREATE WINDOW
		CreateWindow(CLASS_NAME, "Fire Spear",
			WS_OVERLAPPEDWINDOW | WS_VISIBLE, // WINDOW STYLE
			CW_USEDEFAULT, CW_USEDEFAULT, // WINDOW INITIAL POSITION
			800, 800, // WINDOW SIZE
			NULL, NULL, NULL, NULL);
	}
	


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

