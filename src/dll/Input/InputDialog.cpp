#ifndef __INPUTDIALOG_CPP__
#define __INPUTDIALOG_CPP__

#include "windows.h"
#include "stdio.h"
#include "iostream.h"
#include "fstream.h"
#include "..\..\Common\H\DataDescription.h"
#include "InputDialog.h"
#include "Dialogs.h"

char InputDialogFilePath[MAX_PATH];

char InputDialogClassName[]="Input Dialog Class";
char InputDialogTitle[]="Input Data...";
DWORD  NumberElementsOnForm=5;

HWND *hInputDialogStatic, *hInputDialogEdit, hInputDialogButtonPrev, hInputDialogButtonNext, hInputDialogButtonOK, hInputDialogButtonCancel, hInputDialogButtonLFF;
HWND InputDialogParentWindow=NULL;
HWND InputDialogWindow=NULL;
DWORD InputDialogPage=0;
void *InputDialogData=NULL, *InputDialogDataBackup=NULL;
CDataDescription *InputDialogDataDescription=NULL;
DWORD InputDialogDataNumber=0;
HINSTANCE InputDialogParentInstance=0;
bool InputDialogCheckPages=false;

BOOL RegInputDialogClass(HINSTANCE hInstance)
{
    InputDialogParentInstance=hInstance;
	WNDCLASS wc;
    wc.style = wc.cbClsExtra = wc.cbWndExtra = 0;
    wc.lpfnWndProc = InputDialogWndProc;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_ASTERISK);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
    wc.lpszMenuName = (LPCTSTR)NULL;
    wc.lpszClassName = InputDialogClassName;
    return (RegisterClass(&wc) !=0);
}

bool ConsoleInputEx(void *x, CDataDescription *dd, DWORD number)
{
    cout<<"Please enter the parameters of the function.\n";
	char str[256]="\0\0\0\0";
	void *sdata=x;
	for (DWORD i=0;i<number;i++)
	{
		sdata = Search(x, dd, i);
        *((WORD*)str)=256;
        cout<<dd[i].Comment<<endl;
		cin>>str;
        if (!StrToVoid(str, dd+i, sdata))
		{ 
   		    cout<<"Error in parameter "<<i+1<<" ";
			cout<<" ("<<dd[i].Comment<<")";
			cout<<". Reenter this parameter please!\n";
            i--; 
		}		
	}
    
	return false;
}

int FileInputEx(void *x, CDataDescription *dd, DWORD number, char *path)
{
	char str[256]="\0\0\0\0";
	void *sdata=x;
    ifstream in(path, ios::in);
    if (!in.good() || in.eof())
    {
        return -2;
    }
	for (DWORD i=0;i<number;i++)
	{
        sdata = Search(x, dd, i);
		in.getline(str, 256,'\n');
        if (!StrToVoid(str, dd+i, sdata))
		{ 
			sprintf(str,"%s; i = %i",str,i);
			return i;
		}
	}
    return -1;
}

int SetEnteredData(void *data, CDataDescription *ddesc, DWORD n)
{
	char str[256]="\0\0\0\0";
	void *sdata=data;
	for (DWORD i=0;i<NumberElementsOnForm && i+NumberElementsOnForm*InputDialogPage<n;i++)
	{
		sdata = Search(data, ddesc, i+NumberElementsOnForm*InputDialogPage);
        *((WORD*)str)=256;

		SendMessage (hInputDialogEdit[i], EM_GETLINE, 0, (LPARAM)str);
        if (!StrToVoid(str, ddesc+i+NumberElementsOnForm*InputDialogPage, sdata))
		{ 
			return i;
		}		
	}
	return -1;
}

void SetDialogItems(void *data, DWORD n, CDataDescription *ddesc)
{
	char str[256];
	void *sdata=data;
	for (DWORD i=0;i<NumberElementsOnForm && i+NumberElementsOnForm*InputDialogPage<n;i++)
	{
		sdata = Search(data, ddesc, i+NumberElementsOnForm*InputDialogPage);
		VoidToStr(sdata, ddesc+i+NumberElementsOnForm*InputDialogPage, str);
		SetWindowText(hInputDialogEdit[i], str);
		SetWindowText(hInputDialogStatic[i], ddesc[i+NumberElementsOnForm*InputDialogPage].Comment);
		ShowWindow(hInputDialogEdit[i], SW_SHOW);
		ShowWindow(hInputDialogStatic[i], SW_SHOW);
	}
	for (;i<NumberElementsOnForm;i++)
	{
		ShowWindow(hInputDialogEdit[i], SW_HIDE);
		ShowWindow(hInputDialogStatic[i], SW_HIDE);
	}
}

LRESULT CALLBACK InputDialogWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    int shift = 0;
	
    switch(msg)
    {
        case WM_CREATE:
        {
			hInputDialogEdit = new HWND[NumberElementsOnForm];
			hInputDialogStatic = new HWND[NumberElementsOnForm];
			for (DWORD i=0;i<NumberElementsOnForm;i++)
			{
	            hInputDialogStatic[i] = CreateWindow("static",
 	                                    NULL,
	                                    WS_CHILD | SS_LEFT,
	                                    0,                      //left
	                                    i*42,                   //top
	                                    288,                    //width
	                                    20,                     //height
	                                    hwnd,
	                                    (HMENU)0,
	                                    InputDialogParentInstance,
	                                    NULL);
				hInputDialogEdit[i] = CreateWindow("edit",
										NULL,
										WS_CHILD | WS_VISIBLE| WS_BORDER | ES_LEFT,
		                                2,                        //left 
		                                21 + i*42,                //top
		                                288,                      //width
		                                20,                       //height
		                                hwnd,
		                                (HMENU)(INPUT_DIALOG_EDIT+i),
		                                InputDialogParentInstance,
		                                NULL);
			}
            
            hInputDialogButtonPrev = CreateWindow("button",
                                   "<< Previous",
                                   WS_CHILD | BS_PUSHBUTTON,
                                   0,                      //left
                                   NumberElementsOnForm*42,//top
                                   144,                    //width
                                   25,                     //height
                                   hwnd,
                                   (HMENU)INPUT_DIALOG_PREVIOUS,
                                   InputDialogParentInstance,
                                   NULL);
            hInputDialogButtonNext = CreateWindow("button",
                                   "Next >>",
                                   WS_CHILD | BS_PUSHBUTTON,
                                   146,                    //left
                                   NumberElementsOnForm*42,//top
                                   144,                    //width
                                   25,                     //height
                                   hwnd,
                                   (HMENU)INPUT_DIALOG_NEXT,
                                   InputDialogParentInstance,
                                   NULL);     
            hInputDialogButtonOK = CreateWindow("button",
                                   "OK",
                                   WS_CHILD | WS_VISIBLE| BS_PUSHBUTTON,
                                   0,                         //left
                                   NumberElementsOnForm*42+27,//top
                                   144,                       //width
                                   25,                        //height
                                   hwnd,
                                   (HMENU)INPUT_DIALOG_OK,
                                   InputDialogParentInstance,
                                   NULL);
			hInputDialogButtonCancel= CreateWindow("button",
                                   "Cancel",
                                   WS_CHILD | WS_VISIBLE| BS_PUSHBUTTON,
                                   146,                       //left
                                   NumberElementsOnForm*42+27,//top
                                   144,                       //width
                                   25,                        //height
                                   hwnd,
                                   (HMENU)INPUT_DIALOG_CANCEL,
                                   InputDialogParentInstance,
                                   NULL);
            hInputDialogButtonLFF= CreateWindow("button",
                                   "Load Data From File",
                                   WS_CHILD | WS_VISIBLE| BS_PUSHBUTTON,
                                   73,                        //left
                                   NumberElementsOnForm*42+52,//top
                                   144,                       //width
                                   25,                        //height
                                   hwnd,
                                   (HMENU)INPUT_DIALOG_LFF,
                                   InputDialogParentInstance,
                                   NULL);
            return 0;
        }
         case WM_COMMAND:
        {
            switch(LOWORD(wParam))
            {
				case INPUT_DIALOG_PREVIOUS:
				{
					int n=SetEnteredData(InputDialogData, InputDialogDataDescription, InputDialogDataNumber);
                    if (n!=-1) 
                    {
                        MessageBox(hwnd, "Cannot load data", "Check Error", MB_OK);
                        SetFocus(hInputDialogEdit[n]);
                        return 0;
                    }
                    InputDialogPage--;
                    SetDialogItems(InputDialogData, InputDialogDataNumber, InputDialogDataDescription);
                    if (InputDialogPage<1) ShowWindow(hInputDialogButtonPrev, SW_HIDE);
                    ShowWindow(hInputDialogButtonNext, SW_SHOW);
					break;
				}
				case INPUT_DIALOG_NEXT:
				{
                    int n=SetEnteredData(InputDialogData, InputDialogDataDescription, InputDialogDataNumber);
                    if (n!=-1) 
                    {
                        MessageBox(hwnd, "Cannot load data", "Check Error", MB_OK);
                        SetFocus(hInputDialogEdit[n]);
                        return 0;
                    }
                    InputDialogPage++;
                    SetDialogItems(InputDialogData, InputDialogDataNumber, InputDialogDataDescription);
                    if (InputDialogPage>InputDialogDataNumber/NumberElementsOnForm) ShowWindow(hInputDialogButtonNext, SW_HIDE);
                    ShowWindow(hInputDialogButtonPrev, SW_SHOW);
					
					break;
				}
				case INPUT_DIALOG_OK:
				{
                    int n=SetEnteredData(InputDialogData, InputDialogDataDescription, InputDialogDataNumber);
                    if (n!=-1) 
                    {
                        MessageBox(hwnd, "Cannot load data", "Check Error", MB_OK);
                        SetFocus(hInputDialogEdit[n]);
                        return 0;
                    }
                    SendMessage(InputDialogParentWindow, IM_INPUTFINISHED,0,0);
                    ShowWindow(InputDialogParentWindow, SW_SHOW);
                    ShowWindow(hwnd, SW_HIDE);
					break;
				}
				case INPUT_DIALOG_CANCEL:
				{
                    ShowWindow(InputDialogParentWindow, SW_SHOW);
                    ShowWindow(hwnd, SW_HIDE);
					break;
				}
                case INPUT_DIALOG_LFF:
                {
					if (ShowFileDialog(hwnd, 
                            InputDialogFilePath,                                 //name of file
                            "Opening file to load data from...",//caption of window
                            "\0", 
                            "Any file (*.*)\0*.*",        //filter 
                            FDOPENMODE))     
					{
						int res;
						char err_buf[4];
						res = FileInputEx(InputDialogData, InputDialogDataDescription, InputDialogDataNumber, InputDialogFilePath); 
						if (res==-2)
						{
							MessageBox(hwnd, "A file with such name doesn't exist!", "Opening File Error", MB_OK); 
						}
						else if (res > -1)
						{
							itoa(res, err_buf,2);
							MessageBox(hwnd, err_buf, "Pointer adding error", MB_OK);
						}
						else 
						{
							SetDialogItems(InputDialogData, InputDialogDataNumber, InputDialogDataDescription);
						}
					}
				}
                default:
				{
					return 0;
				}
            }
            return 0;
        }
        case WM_CLOSE:
        {
            ShowWindow(InputDialogParentWindow, SW_SHOW);
            ShowWindow(hwnd, SW_HIDE);
            return 0;
        }
        case WM_DESTROY:
        {
			delete []hInputDialogEdit;
			delete []hInputDialogStatic;
			delete []InputDialogDataBackup;
            PostQuitMessage(0);
            return 0;
        }
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

bool InitInputDialog(HINSTANCE hInstance, HWND parent)
{
	InputDialogParentWindow = parent;
	if (!RegInputDialogClass(hInstance))
    {
        return FALSE;
    }
    if (!(InputDialogWindow = CreateWindow(InputDialogClassName,
                              InputDialogTitle,
                              WS_OVERLAPPEDWINDOW|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,
                              CW_USEDEFAULT,               //left    
                              CW_USEDEFAULT,               //top
                              300,                         //width
                              (NumberElementsOnForm+2)*42+26,//height
                              0,
                              0,
                              hInstance, NULL)))
    {
        return FALSE;
    }
    return TRUE;
}

void ShowInputDialog(void *x, CDataDescription *dd, DWORD number, bool CheckPages)
{
	InputDialogCheckPages = CheckPages;
	InputDialogData = x;
	InputDialogDataDescription = dd;
	InputDialogDataNumber = number;

    SetDialogItems(InputDialogData, InputDialogDataNumber, InputDialogDataDescription);
	ShowWindow(InputDialogWindow, SW_SHOW);
    ShowWindow(InputDialogParentWindow, SW_HIDE);
    if (number>NumberElementsOnForm) ShowWindow(hInputDialogButtonNext, SW_SHOW);
    //else SendMessage(InputDialogParentWindow, IM_INPUTFINISHED,0,0);
}




#endif //__INPUTDIALOG_CPP__