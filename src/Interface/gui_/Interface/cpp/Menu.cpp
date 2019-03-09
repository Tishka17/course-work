#ifndef __MENU_CPP__
#define __MENU_CPP__
#include "..\..\..\..\Common\H\wndws.h"
#include "..\H\Menu.h"
#include "..\..\..\Common\H\Variables.h"
//=================================================================================================================
// Function name    : CreateMenuItem
// Description      : Creates a item, which belong to a certain menu
// Return type      : BOOL 
// Argument 1       : HMENU hMenu
// Argument 2       : char *str
// Argument 3       : UINT uIns
// Argument 4       : UINT uCom
// Argument 5       : HMENU hSubMenu
// Argument 6       : BOOL flag
// Argument 7       : UINT fType
BOOL CreateMenuItem(HMENU hMenu, char *str, UINT uIns, UINT uCom, HMENU hSubMenu, BOOL flag, UINT fType)
{ 
    MENUITEMINFO mii;
    mii.cbSize     = sizeof(MENUITEMINFO);
    mii.fMask      = MIIM_STATE|MIIM_TYPE|MIIM_SUBMENU|MIIM_ID;              //type of menu item (toxa.su)
    mii.fType      = fType;
    mii.fState     = MFS_ENABLED;
    mii.dwTypeData = str;
    mii.cch        = sizeof(str);
    mii.wID        = uCom;
    mii.hSubMenu   = hSubMenu;
    return InsertMenuItem(hMenu, uIns, flag, &mii);
};

BOOL CreateMenuCheckItem(HMENU hMenu, char *str, UINT uIns, UINT uCom, BOOL flag)
{ 
    MENUITEMINFO mii;
    mii.cbSize     = sizeof(MENUITEMINFO);
    mii.fMask      = MIIM_STATE|MIIM_TYPE|MIIM_SUBMENU|MIIM_ID;              //type of menu item (toxa.su)
    mii.fType      = MFT_STRING;
//    mii.hbmpChecked= (HBITMAP)1;
    mii.fState     = MFS_ENABLED;
    mii.dwTypeData = str;
    mii.cch        = sizeof(str);
    mii.wID        = uCom;
    mii.hSubMenu   = NULL;
    return InsertMenuItem(hMenu, uIns, flag, &mii);
};

//=================================================================================================================
// Function name    : CreatePluginsMenu
// Description      : Creates a submenu for a plugin item in main menu. Addes items, using which you can call plugins methods
// Return type      : BOOL 
// Argument 1       : HMENU hMenu
// Argument 2       : CPlugIn *First
BOOL CreatePluginsMenu(HMENU hMenu, CPlugIn *First)
{
    int i=0;
    int ii=0;

    CFunction *f;// = (CFunction*)First->Functions.GetFirst();
    CPlugIn *p = First;
    while (p)
    {
        ii=0;
        p->hMenu = CreatePopupMenu();
        CreateMenuItem(hMenu, p->Caption, i++, 0, p->hMenu, FALSE, MFT_STRING);
        f = (CFunction*)p->Functions.GetFirst();
        while (f)
        {
            if (f->Type==CFunction::ftUnknown)
                CreateMenuItem(p->hMenu, f->Caption, ii, p->FirstWM+ii, 0, FALSE, MFT_SEPARATOR);
            else 
                CreateMenuItem(p->hMenu, f->Caption, ii, p->FirstWM+ii, 0, FALSE, MFT_STRING);
            ii++;
            f = (CFunction*)f->GetNext();
        }
        p = (CPlugIn*)p->GetNext();
    }
    return true;
};

//=================================================================================================================
// Function name    : CreateMainMenu
// Description      : Creates main menu for a certain window
// Return type      : BOOL 
// Argument         : HWND hWnd
BOOL CreateMainMenu(CList &Plugins, WINDOW_MENU_STRUCT &MenuStruct, LNG_MAIN_STRUCT Lng_Main_Struct, HWND hWnd)
{
    MenuStruct.Main=CreateMenu();
    MenuStruct.File=CreatePopupMenu();
    MenuStruct.View=CreatePopupMenu();
    MenuStruct.Help=CreatePopupMenu();
    MenuStruct.Plugins=CreatePopupMenu();
    MenuStruct.GraphicPanel=CreatePopupMenu();
    MenuStruct.PicturePanel=CreatePopupMenu();
    MenuStruct.Recent=CreatePopupMenu();
    //hSquaresSizeMenu=CreatePopupMenu();

    int i=0;//main menu

    CreateMenuItem(MenuStruct.Main, Lng_Main_Struct.MainMenu.File,   i++, 0, MenuStruct.File, FALSE, MFT_STRING);
    CreateMenuItem(MenuStruct.Main, Lng_Main_Struct.MainMenu.View,   i++, 0, MenuStruct.View, FALSE, MFT_STRING);
    CreateMenuItem(MenuStruct.Main, Lng_Main_Struct.MainMenu.Plugins,i++, 0, MenuStruct.Plugins, FALSE, MFT_STRING);
    CreateMenuItem(MenuStruct.Main, Lng_Main_Struct.MainMenu.Help,   i++, 0, MenuStruct.Help, FALSE, MFT_STRING|MFT_RIGHTJUSTIFY);

    i=0;//file menu
    CreateMenuItem(MenuStruct.File, Lng_Main_Struct.FileMenu.Open,  i++, CM_FILE_OPEN,   NULL, FALSE, MFT_STRING);
    CreateMenuItem(MenuStruct.File, Lng_Main_Struct.FileMenu.Save,  i++, CM_FILE_SAVE,   NULL, FALSE, MFT_STRING);
    CreateMenuItem(MenuStruct.File, "", i++, 0, NULL, FALSE, MFT_SEPARATOR);
    CreateMenuItem(MenuStruct.File, Lng_Main_Struct.FileMenu.RunBat,i++, CM_FILE_RUNBAT, NULL, FALSE, MFT_STRING);
    CreateMenuItem(MenuStruct.File, Lng_Main_Struct.FileMenu.Recent,  i++, 0,   MenuStruct.Recent, FALSE, MFT_STRING);
    CreateMenuItem(MenuStruct.File, "", i++, 0, NULL, FALSE, MFT_SEPARATOR);
    CreateMenuItem(MenuStruct.File, Lng_Main_Struct.FileMenu.Exit,  i++, CM_FILE_EXIT,   NULL, FALSE, MFT_STRING);
    SetMenuItem(MenuStruct.File, CM_FILE_SAVE, MFS_GRAYED, FALSE);
//    i=CreateAllPanelMenu();//view menu

    CreatePicturePanelMenu(MenuStruct.PicturePanel, Lng_Main_Struct, NULL);
    CreateGraphicPanelMenu(MenuStruct.GraphicPanel, Lng_Main_Struct, NULL);
    CreateMenuItem(MenuStruct.View, Lng_Main_Struct.ViewMenu.LeftPanel,  i++, 0,  MenuStruct.PicturePanel, FALSE, MFT_STRING);  
    CreateMenuItem(MenuStruct.View, Lng_Main_Struct.ViewMenu.RightPanel,  i++, 0,  MenuStruct.GraphicPanel, FALSE, MFT_STRING);  
    CreateMenuItem(MenuStruct.View, Lng_Main_Struct.ViewMenu.ShowLogFile,  i++, CM_VIEW_SHOWLOG,  NULL, FALSE, MFT_STRING);  

    i=0;//help menu
    CreateMenuItem(MenuStruct.Help, Lng_Main_Struct.HelpMenu.Help,     i++, CM_HELP_HELP,  NULL, FALSE, MFT_STRING);
    CreateMenuItem(MenuStruct.Help, Lng_Main_Struct.HelpMenu.HotKeys,  i++, CM_HELP_HOTKEYS,  NULL, FALSE, MFT_STRING);
    CreateMenuItem(MenuStruct.Help, Lng_Main_Struct.HelpMenu.Internet, i++, CM_HELP_INTERNET,  NULL, FALSE, MFT_STRING);
    CreateMenuItem(MenuStruct.Help, " ", i++, 0, NULL, FALSE, MFT_SEPARATOR);
    CreateMenuItem(MenuStruct.Help, Lng_Main_Struct.HelpMenu.About,    i++, CM_HELP_ABOUT, NULL, FALSE, MFT_STRING);
    

    //plugins menu
    CreatePluginsMenu(MenuStruct.Plugins, (CPlugIn*)Plugins.GetFirst());

    SetMenu(hWnd,MenuStruct.Main);
    DrawMenuBar(hWnd);
    return true;
};

//=================================================================================================================
// Function name    : SetMenuItem
// Description      : Sets state of menu item, which was already created
// Return type      : BOOL 
// Argument 1       : HMENU hMenu
// Argument 2       : UINT uIns
// Argument 3       : UINT fState
// Argument 4       : BOOL flag
BOOL SetMenuItem(HMENU hMenu, UINT uIns, UINT fState, BOOL flag) 
{
    MENUITEMINFO mii;
    mii.cbSize=sizeof(MENUITEMINFO);
    mii.fMask=MIIM_STATE|MIIM_ID;
    mii.fState=fState;
    mii.wID=uIns;
    return SetMenuItemInfo (hMenu, uIns, flag, &mii);
};

//=================================================================================================================
// Function name    : GetMenuItem
// Description      : Returns state of a certain menu item
// Return type      : UINT 
// Argument 1       : HMENU hMenu
// Argument 2       : UINT uIns
// Argument 3       : BOOL flag
UINT GetMenuItem(HMENU hMenu, UINT uIns, BOOL flag)
{
    MENUITEMINFO mii;
    mii.cbSize=sizeof(MENUITEMINFO);
    mii.fMask=MIIM_STATE;
    GetMenuItemInfo( hMenu, uIns, flag, &mii);
    return mii.fState;
};



//=================================================================================================================
// Function name    : CreatePicturePanelMenu
// Description      : creates menu for picture panels
// Return type      : UINT 
UINT CreatePicturePanelMenu(HMENU hMenu, LNG_MAIN_STRUCT Lng_Main_Struct, CLayer* First, bool JustLayers)
{
    int i=0;
    if (!JustLayers)
    {
        CreateMenuItem(hMenu, Lng_Main_Struct.PanelMenu.Picture,   i++, CM_VIEW_PICTUREPANEL_PICTURE, NULL, FALSE, MFT_RADIOCHECK);
        CreateMenuItem(hMenu, Lng_Main_Struct.PanelMenu.ColorPicture, i++, CM_VIEW_PICTUREPANEL_COLORPICTURE, NULL, FALSE, MFT_RADIOCHECK);
        CreateMenuItem(hMenu, Lng_Main_Struct.PanelMenu.NoPicture, i++, CM_VIEW_PICTUREPANEL_NOPICTURE, NULL, FALSE, MFT_RADIOCHECK);
        SetMenuItem(hMenu, CM_VIEW_PICTUREPANEL_NOPICTURE, MFS_CHECKED, FALSE);

        CreateMenuItem(hMenu, NULL, i++, 0, NULL, FALSE, MFT_SEPARATOR);
        CreateMenuCheckItem(hMenu, Lng_Main_Struct.PanelMenu.Disabled, i++, CM_VIEW_PICTUREPANEL_DISABLED, FALSE);
        SetMenuItem(hMenu, CM_VIEW_PICTUREPANEL_DISABLED, MFS_CHECKED, FALSE);
        CreateMenuItem(hMenu, NULL, i++, 0, NULL, FALSE, MFT_SEPARATOR);
    }

    CLayer *el=First;
    i=6;
    while (el)
    {
        CreateMenuCheckItem(hMenu, el->Caption, i, CM_VIEW_PICTUREPANEL_FIRST+i-6,FALSE);
        if (el->Draw) SetMenuItem(hMenu, CM_VIEW_PICTUREPANEL_FIRST+i-6, MFS_CHECKED, FALSE);
        el = (CLayer*)el->GetNext();
        i++;
    }

    return 0;
}

//=================================================================================================================
// Function name    : CreateGraphicsPanelMenu
// Description      : creates menu for grpahics panels
// Return type      : UINT 
UINT CreateGraphicPanelMenu(HMENU hMenu, LNG_MAIN_STRUCT Lng_Main_Struct, CGraphic* First)
{
    int i=0;

    CGraphic *el=First;

    while (el)
    {
        CreateMenuCheckItem(hMenu, el->Caption, i, CM_VIEW_GRAPHICPANEL_FIRST+i, FALSE);
        if (el->Draw) SetMenuItem(hMenu, CM_VIEW_GRAPHICPANEL_FIRST+i, MFS_CHECKED, FALSE); 
        i++;
        el = (CGraphic*)el->GetNext();
    }
    CreateMenuItem(hMenu, NULL, i++, 0, NULL, FALSE, MFT_SEPARATOR);
    CreateMenuCheckItem(hMenu, Lng_Main_Struct.PanelMenu.Disabled, i++, CM_VIEW_GRAPHICPANEL_DISABLED, FALSE);
    SetMenuItem(hMenu, CM_VIEW_GRAPHICPANEL_DISABLED, MFS_CHECKED, FALSE);

    return 0;
}

BOOL ResetMenu(HMENU hMenu, int Number, int Start)
{
    for (int i=0;i<Number;i++)
    {
        DeleteMenu(hMenu, Start, MF_BYPOSITION);
    }
    return true;
}

UINT CreateRecentMenu(HMENU hMenu, SETTINGS_MAIN_STRUCT Settings_Struct)
{
    for (int i=0;i<Settings_Struct.Recent.Number;i++)
    {
        CreateMenuItem(hMenu, Settings_Struct.Recent.File[i], i, CM_FILE_RECENT_FIRST+i, NULL, FALSE, MFT_STRING);
    }
    return 0;
}
//=====================================================================================================
// Function name    : CreateAllPanelMenu
// Description      : creates all menus for both of panels
// Return type      : UINT 
/*UINT CreateAllPanelMenu()
{
    LeftPanel.MakeMenu((CPlugIn*)Plugins.GetFirst());
    RightPanel.MakeMenu((CPlugIn*)Plugins.GetFirst());
    UINT i=0;
    CreateMenuItem(hViewMenu, Lng_Main_Struct.ViewMenu.LeftPanel, i++, 0, LeftPanel.hMenu, TRUE, MFT_STRING);
    CreateMenuItem(hViewMenu, Lng_Main_Struct.ViewMenu.RightPanel, i++, 0, RightPanel.hMenu, TRUE, MFT_STRING);
    return 2;
}
*
//=================================================================================================================
// Function name    : ResetAllPanelMenu
// Description      : rebuilds panels' menus
// Return type      : UINT 
UINT ResetAllPanelMenu()
{
    
    DeleteMenu(hViewMenu, 0, MF_BYPOSITION);
    DeleteMenu(hViewMenu, 0, MF_BYPOSITION);
    
    CreateAllPanelMenu();
    return 2;
}

//=================================================================================================================
// Function name    : DisableDrawSquares
// Description      : disbles squares drawing
// Return type      : void 
void DisableDrawSquares()
{
    SetMenuItem(hSquaresSizeMenu, ChosenSize, MFS_UNCHECKED, FALSE);
    SetMenuItem(hSquaresSizeMenu, CM_VIEW_SQURES_SIZE_MIN, MFS_CHECKED, FALSE);
    ChosenSize = CM_VIEW_SQURES_SIZE_MIN;
}*/
#endif //__MENU_CPP__