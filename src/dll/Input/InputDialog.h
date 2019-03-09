#ifndef __INPUTDIALOG_H__
#define __INPUTDIALOG_H__

#include "..\..\Common\H\DataDescription.h"

#define INPUT_DIALOG_EDIT 	  6660
#define INPUT_DIALOG_OK       6650
#define INPUT_DIALOG_NEXT     6651
#define INPUT_DIALOG_PREVIOUS 6652
#define INPUT_DIALOG_CANCEL   6653
#define INPUT_DIALOG_LFF      6654


//=================================================================================================================
// Function name	: RegInputDialogClass
// Description	    : registers class of dialog
// Return type		: BOOL 
// Argument         : HINSTANCE hInstance
BOOL RegInputDialogClass(HINSTANCE hInstance);

//=================================================================================================================
// Function name	: InputDialogWndProc
// Description	    : window procedure of dialog
// Return type		: LRESULT CALLBACK 
// Argument 1       : HWND hwnd
// Argument 2       : UINT msg
// Argument 3       : WPARAM wParam
// Argument 4       : LPARAM lParam
LRESULT CALLBACK InputDialogWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

//=================================================================================================================
// Function name	: InitInputDialog
// Description	    : initializes dialog
// Return type		: bool 
// Argument         : HINSTANCE hInstance
bool InitInputDialog(HINSTANCE hInstance, HWND parent=NULL);

//=================================================================================================================
// Function name	: ShowInputDialog
// Description	    : Shows input dialog
// Return type		: void 
// Argument 1       : void *x
// Argument 2       : CDataDescription *dd
// Argument 3       : DWORD number
// Argument 4       : bool CheckPages=true
void ShowInputDialog(void *x, CDataDescription *dd, DWORD number, bool CheckPages=true);

bool ConsoleInputEx(void *x, CDataDescription *dd, DWORD number);
int FileInputEx(void *x, CDataDescription *dd, DWORD number, char *path);
#endif //__INPUTDIALOG_H__