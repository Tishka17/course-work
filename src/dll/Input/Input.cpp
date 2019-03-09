// Approximation.cpp : Defines the entry point for the DLL application.
//

#include "..\..\Common\H\wndws.h"
#include "..\..\Common\H\data.h"
#include "..\..\Common\H\Plugins.h"
#include "InputDialog.h"
#include "Input.h"
#include "math.h"



BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
                     )
{
    return TRUE;
};



bool InitGUIInput(HINSTANCE hInst, HWND hWnd)
{
    InitInputDialog(hInst,hWnd);
    return true;
}

bool InitConsoleInput()
{
    return true;
}

bool InitFileInput()
{
    return false;
}

bool GUIInput(void *x, CDataDescription *dd, DWORD number)
{
    ShowInputDialog(x, dd, number, true);
    return false;
}

bool ConsoleInput(void *x, CDataDescription *dd, DWORD number)
{
	return ConsoleInputEx(x,dd,number);
}


//Prototype by Tishka17 - commented by Waller

bool FileInput(void *x, CDataDescription *dd, DWORD number, char *path)
{
    return (FileInputEx(x,dd,number,path)==-1);
}

