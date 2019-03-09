#ifndef __MENU_H__
#define __MENU_H__
#include "..\..\..\..\Common\H\wndws.h"
#include "..\..\..\..\Common\H\Plugins.h"
#include "..\..\..\Common\H\Settings.h"
#include "..\..\..\Common\H\Language.h"

struct WINDOW_MENU_STRUCT
{
    HMENU Main;
    HMENU File;
    HMENU View;
    HMENU Plugins;
    HMENU Help;
    HMENU PicturePanel;
    HMENU GraphicPanel;
    HMENU Recent;
};

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
BOOL CreateMenuItem(HMENU hMenu, char *str, UINT uIns, UINT uCom, HMENU hSubMenu, BOOL flag, UINT fType);

BOOL CreateMenuCheckItem(HMENU hMenu, char *str, UINT uIns, UINT uCom, BOOL flag);

//=================================================================================================================
// Function name    : CreatePluginsMenu
// Description      : Creates a submenu for a plugin item in main menu. Addes items, using which you can call plugins methods
// Return type      : BOOL 
// Argument 1       : HMENU hMenu
// Argument 2       : CPlugIn *First
BOOL CreatePluginsMenu(HMENU hMenu, CPlugIn *First);

//=================================================================================================================
// Function name    : CreateMainMenu
// Description      : Creates main menu for a certain window
// Return type      : BOOL 
// Argument         : HWND hWnd
BOOL CreateMainMenu(CList &Plugins, WINDOW_MENU_STRUCT &MenuStruct, LNG_MAIN_STRUCT Lng_Main_Struct, HWND hWnd);

//=================================================================================================================
// Function name    : SetMenuItem
// Description      : Sets state of menu item, which was already created
// Return type      : BOOL 
// Argument 1       : HMENU hMenu
// Argument 2       : UINT uIns
// Argument 3       : UINT fState
// Argument 4       : BOOL flag
BOOL SetMenuItem(HMENU hMenu, UINT uIns, UINT fState, BOOL flag);

//=================================================================================================================
// Function name    : GetMenuItem
// Description      : Returns state of a certain menu item
// Return type      : UINT 
// Argument 1       : HMENU hMenu
// Argument 2       : UINT uIns
// Argument 3       : BOOL flag
UINT GetMenuItem(HMENU hMenu, UINT uIns, BOOL flag);

//=================================================================================================================
// Function name    : CreatePicturePanelMenu
// Description      : creates menu for picture panels
// Return type      : UINT 
UINT CreatePicturePanelMenu(HMENU hMenu, LNG_MAIN_STRUCT Lng_Main_Struct, CLayer* First, bool JustLayers=false);

//=================================================================================================================
// Function name    : CreateGraphicsPanelMenu
// Description      : creates menu for grpahics panels
// Return type      : UINT 
UINT CreateGraphicPanelMenu(HMENU hMenu, LNG_MAIN_STRUCT Lng_Main_Struct, CGraphic* First);

BOOL ResetMenu(HMENU, int,int=0);

UINT CreateRecentMenu(HMENU hMenu, SETTINGS_MAIN_STRUCT Settings_Struct);
#endif //__MENU_H__