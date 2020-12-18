#include "winhook.h"
// нопки установки хука
HWND hButSetMHook;
HWND hButSetKHook;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS WindowClass;
	//создаем окно
	WindowClass.style = CS_HREDRAW | CS_VREDRAW;
	WindowClass.cbClsExtra = 0;
	WindowClass.cbWndExtra = 0;
	WindowClass.lpszClassName = L"WindowClass";
	WindowClass.hInstance = hInstance;
	WindowClass.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	WindowClass.lpszMenuName = NULL;
	WindowClass.lpfnWndProc = WindowProc;
	WindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WindowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClass(&WindowClass);

	HWND hMainWindow;

	hMainWindow = CreateWindow(L"WindowClass", L"Hooks", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
	CW_USEDEFAULT, CW_USEDEFAULT, 560, 450,
	NULL, NULL, hInstance, NULL);

	ShowWindow(hMainWindow, nCmdShow);
	UpdateWindow(hMainWindow);

	MSG Message;
	while(GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return Message.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{//создаем кнопки
	case WM_CREATE:
		hButSetMHook = CreateWindow(L"button",L"’ук мыши", WS_VISIBLE | WS_CHILD, 25, 100, 200, 25, hwnd, (HMENU)IDB_SETMHOOK, NULL, NULL);
		CreateWindow(L"button",L"ќтключить хук мыши", WS_VISIBLE | WS_CHILD, 260, 100, 200, 25, hwnd, (HMENU)IDB_UNMHOOK, NULL, NULL);
		hButSetKHook = CreateWindow(L"button",L"’ук клавиатуры", WS_VISIBLE | WS_CHILD, 25, 200, 200, 25, hwnd, (HMENU)IDB_SETKHOOK, NULL, NULL);
		CreateWindow(L"button",L"ќтключить хук клавиатуры", WS_VISIBLE | WS_CHILD, 260, 200, 200, 25, hwnd, (HMENU)IDB_UNKHOOK, NULL, NULL);
		break;
	case WM_COMMAND:
		//если нажали на кнопку, то вызываем соотвествующие функции
		switch(LOWORD(wParam))
		{
		case IDB_SETMHOOK:
			SetMouseHook();
			EnableWindow(hButSetMHook, FALSE);
			break;
		case IDB_UNMHOOK:
			UnMouseHook();
			EnableWindow(hButSetMHook, TRUE);
			break;
			case IDB_SETKHOOK:
			SetKeyBoardHook();
			EnableWindow(hButSetKHook, FALSE);
			break;
		case IDB_UNKHOOK:
			UnKeyBoardHook();
			EnableWindow(hButSetKHook, TRUE);
			break;
		}
		break;
	case WM_DESTROY:
		UnMouseHook();
		UnKeyBoardHook();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}
