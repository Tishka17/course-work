#ifndef __LANGUAGE_H__
#define __LANGUAGE_H__

#include "..\..\..\Common\H\Data.h"
#include "FileIni.h"

struct LNG_MAIN_STRUCT
{
    struct 
    {
        String File;
        String View;
        String Plugins;
        String Help;
    } MainMenu;

    struct 
    {
        String Open;
        String Save;
        String RunBat;
        String Recent;
        String Exit;
    } FileMenu;

    struct 
    {
        String LeftPanel;
        String RightPanel;
        String ShowLogFile;
    } ViewMenu;

    struct 
    {
        String Help;
        String Internet;
        String HotKeys;
        String About;
    } HelpMenu;
       
    struct
    {
        String ColorPicture;
        String Picture;
        String NoPicture;
        String Disabled;
    } PanelMenu;

    struct
    {
        String OpenDialogCaption;
        String SaveDialogCaption;
    } Dialogs;
    
    struct 
    {
        String bmp;
        String Any;
        String Filter;
    } FileFilter;

    String Author;

};

void LoadLangStruct(LNG_MAIN_STRUCT &Lng_Main_Struct, char *filename);

void LoadDefaultLangStruct(LNG_MAIN_STRUCT &Lng_Main_Struct);

void SaveLangStruct(LNG_MAIN_STRUCT &Lng_Main_Struct, char *filename);

#endif //__LANGUAGE_H__