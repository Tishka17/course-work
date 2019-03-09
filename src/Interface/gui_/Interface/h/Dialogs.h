#ifndef _DIALOGS_H
#define _DIALOGS_H
#include "..\..\..\..\Common\H\wndws.h"

#define FDSAVEMODE 0
#define FDOPENMODE 1

bool ShowFileDialog(HWND HWndOwner, char *FileName, char *Title, 
                    char *InitialDir, char *Filter, char mode);

#endif _DIALOGS_H