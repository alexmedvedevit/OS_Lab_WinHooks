#include <windows.h>
#include "dllhook.h"

#define IDB_SETMHOOK 1111
#define IDB_UNMHOOK 1112
#define IDB_SETKHOOK 1113
#define IDB_UNKHOOK 1114
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
