#include "dllhook.h"
#include "atltypes.h"

HHOOK hMouseHook;
HHOOK hKeyboardHook;
HINSTANCE hInst;


EXPORT void CALLBACK SetMouseHook(void)
{
	hMouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, hInst, 0);
}

EXPORT void CALLBACK UnMouseHook(void)
{
	UnhookWindowsHookEx(hMouseHook);
}

EXPORT void CALLBACK SetKeyBoardHook(void)
{
	hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, hInst, 0);
}

EXPORT void CALLBACK UnKeyBoardHook(void)
{
	UnhookWindowsHookEx(hKeyboardHook);
}

bool reselectAxis = true;

LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam)
{
	if (code < 0)
	{
		CallNextHookEx(hKeyboardHook, code, wParam, lParam);
		return 0;
	}
	if (wParam == WM_KEYDOWN) {
		PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)(lParam);
		LPPOINT  pt = new POINT;
		GetCursorPos(pt);
		int x = pt->x;
		int y = pt->y;
		switch (p->vkCode)
		{
		
		//Переключение привзяки к оси пробелом
		case VK_SPACE:
			if (reselectAxis)
			{
				reselectAxis = false;
			}
			else
			{
				reselectAxis = true;
			}
			break;

		default:
			break;
		}

		return CallNextHookEx(NULL, code, wParam, lParam);
	}
}
LRESULT CALLBACK MouseProc(int code, WPARAM wParam, LPARAM lParam)
{
	if (code < 0)
	{
		return 0;
	}
	if (wParam == WM_MOUSEMOVE)
	{
		//Привязка курсора к оси X или Y
		RECT desktop;
		const HWND hDesktop = GetDesktopWindow();
		GetWindowRect(hDesktop, &desktop);

		int screenWidthHalf = desktop.right/2;
		int screenHeightHalf = desktop.bottom/2;

		MOUSEHOOKSTRUCT* p = (MOUSEHOOKSTRUCT*)lParam;
		if (reselectAxis)
		{
			if (p->pt.x > screenWidthHalf || p->pt.x < screenWidthHalf)
			{
				p->pt.x = screenWidthHalf;
			}
			SetCursorPos(p->pt.x, p->pt.y);
		}
		else 
		{
			if (p->pt.y > screenHeightHalf || p->pt.y < screenHeightHalf)
			{
				p->pt.y = screenHeightHalf;
			}
			SetCursorPos(p->pt.x, p->pt.y);
		}
	}
	else
	{
		return 0;
	}

}


BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	hInst = hinstDLL;
	return TRUE;
}
