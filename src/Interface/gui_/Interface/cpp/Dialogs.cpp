#ifndef _DIALOGS_CPP
#define _DIALOGS_CPP
#include "..\H\Dialogs.h"

bool ShowFileDialog(HWND HWndOwner, char *FileName, char *Title, 
                    char *InitialDir, char *Filter, char mode) 
{ 
    OPENFILENAME ofn; 
    ZeroMemory(&ofn, sizeof(OPENFILENAME)); //fill with zeros

    char szFile[MAX_PATH]; 
    ZeroMemory(szFile, MAX_PATH); //fill with zeros

    // initialize OPENFILENAME 
    ofn.lStructSize = sizeof(OPENFILENAME); 
    ofn.hwndOwner = HWndOwner; //owner window
    ofn.lpstrFile = szFile;    
    ofn.nMaxFile = MAX_PATH; 
    ofn.lpstrFilter = Filter; 
    ofn.nFilterIndex = 0; 
    ofn.lpstrTitle = Title; 
    ofn.lpstrInitialDir = InitialDir; 
    ofn.Flags = OFN_EXPLORER | ((mode)?OFN_FILEMUSTEXIST:0); 

    // Show the Open dialog window. 
    if ((mode)?GetOpenFileName(&ofn):GetSaveFileName(&ofn)) 
    { 
        strcpy(FileName, ofn.lpstrFile); 
        return true; 
    } 
    return false; 
}

#endif _DIALOGS_CPP