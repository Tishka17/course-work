#ifndef __APPROXIMATION_H__
#define __APPROXIMATION_H__


#define EXPORT extern "C" __declspec (dllexport)


EXPORT bool InitGUIInput(HINSTANCE, HWND);

EXPORT bool InitConsoleInput();

EXPORT bool InitFileInput();

EXPORT bool GUIInput(void *x, CDataDescription *dd, DWORD number);

EXPORT bool ConsoleInput(void *x, CDataDescription *dd, DWORD number);

EXPORT bool FileInput(void *x, CDataDescription *dd, DWORD number, char *path);


#endif //__APPROXIMATION_H__