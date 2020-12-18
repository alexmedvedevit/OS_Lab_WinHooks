#include <windows.h>
#define EXPORT extern "C" __declspec(dllexport)

EXPORT void CALLBACK SetMouseHook(void);
EXPORT void CALLBACK UnMouseHook(void);
EXPORT void CALLBACK SetKeyBoardHook(void);
EXPORT void CALLBACK UnKeyBoardHook(void);
LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK MouseProc(int code, WPARAM wParam, LPARAM lParam);
