#include <iostream>
#include <direct.h>
#include <stdlib.h>
#include <windows.h>


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


LRESULT CALLBACK WindowProcessMessages(HWND hwnd, UINT msg, WPARAM param, LPARAM lparam);

int WINAPI WinMain(HINSTANCE currentInstance, HINSTANCE previousInstance, PSTR cmdLine, INT cmdCount) {

	// REGISTER WINDOW CLASS
	const char* CLASS_NAME = "MyApplication";
	WNDCLASS wc{};
	wc.hInstance = currentInstance;
	wc.lpszClassName = CLASS_NAME;
	wc.hCursor = LoadCursor(NULL , IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpfnWndProc = WindowProcessMessages;
	RegisterClass(&wc);

	if (IsOnlyInstance("MyApplication")) // IF THE NAME IS UNIQUE
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
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WindowProcessMessages(HWND hwnd, UINT msg, WPARAM param, LPARAM lparam) {
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hwnd, msg, param, lparam);
	}
}