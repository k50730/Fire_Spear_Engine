#pragma once
#include "CoreEngine.h"

class InputInterface {
public:
	virtual void MouseMove(HWND hwnd, WPARAM wp, LPARAM lParam)
	{
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
	virtual void LeftMouseDown(HWND hwnd, WPARAM wp, LPARAM lParam)
	{
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
	virtual void LeftMouseUp(HWND hwnd, WPARAM wp, LPARAM lParam)
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
	virtual void RightMouseDown(HWND hwnd, WPARAM wp, LPARAM lParam)
	{
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
	virtual void RightMouseUp(HWND hwnd, WPARAM wp, LPARAM lParam)
	{
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
	virtual void KeyDown(HWND hwnd, WPARAM wp, LPARAM lParam)
	{
		HDC hdc;
		hdc = GetDC(hwnd);
		char text[40];
		sprintf_s(text, "KeyDown Code: %d", wp);
		LPCSTR textmsg = (LPCSTR)text;
		TextOut(hdc,
			5, 105,
			textmsg, _tcslen(textmsg));


		ReleaseDC(hwnd, hdc);
	}
	virtual void KeyUp(HWND hwnd, WPARAM wp, LPARAM lParam)
	{
		HDC hdc;
		hdc = GetDC(hwnd);
		char text[40];
		sprintf_s(text, "KeyUp Code: %d", wp);
		LPCSTR textmsg = (LPCSTR)text;
		TextOut(hdc,
			5, 130,
			textmsg, _tcslen(textmsg));


		ReleaseDC(hwnd, hdc);
	}
};
