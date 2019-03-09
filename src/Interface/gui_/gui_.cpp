#define _GUI_MODE_

#include "..\..\Common\H\wndws.h"
#include "..\..\Common\H\Plugins.h"
#include "commdlg.h"
#include "math.h"
#include "stdlib.h"
#include "string.h"
#include "iostream.h"
#include "fstream.h"
#include "conio.h"

#include "..\Common\H\Variables.h"
#include "..\Common\Variables.var"
#include "..\Common\H\DllsUsage.h"
#include "..\Common\H\LogFile.h"
#include "..\Common\H\PluginsUsage.h"

#include "..\Common\H\Settings.h"
#include "..\Common\H\Language.h"

#include "..\Common\H\script.h"

#include "GUI_.h"
#include "Interface\H\Corners.h"
#include "Interface\H\Dialogs.h"
#include "Interface\H\Menu.h"

//interface variables
    char         szMainTitle[]="Fractals GUI_ Window";                        //main window title
    char         szMainWindowclass[]="FractalsMainWindow";                    //main window class
    char         szPicturePanelclass[]="FractalsPicturePanel";
    char         szGraphicPanelclass[]="FractalsGraphicPanel";
    char         szSeparatorClass[]="FractalsSeparator";

//    static HMENU hMainMenu;                                                  //characteristic variable of main menu
    //static HMENU hFileMenu, hViewMenu, hHelpMenu, hPanelsPositionMenu;       //the same for other menu named as "file" etc. (toxa.su by tishka17)
    HACCEL       accel;                                                      //accelerators table
    HWND         hWnd, PicturePanel, GraphicPanel, Separator;                                                       //handle of main window
    LNG_MAIN_STRUCT Lng_Main_Struct;
    WINDOW_MENU_STRUCT MenuStruct;
    CList GlobalVariables;

    float SeparatorPosition, MainWidth, MainHeight;
    bool PictureDisabled=true;
    bool GraphicDisabled=true;
    int DrawPictureType=0;
    int GraphicsNumber=0;
    int LayersNumber=0;
    DWORD CM;
//winmain by Tishka17
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{

    char SettingsPath[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, ModulePath);
    strcpy(SettingsPath, ModulePath);
    strcat(SettingsPath,"\\Settings.ini");

    SetLogFilePath();
    GetLogFilePath(LogFilePath);
    OpenLog();
    WriteLogStarted("Interface");
    
    LoadDefaultSettings(Settings_Struct);
    LoadSettings(Settings_Struct, SettingsPath);
 
    LoadDefaultLangStruct(Lng_Main_Struct);
    LoadLangStruct(Lng_Main_Struct, Settings_Struct.Language.LngFile);

    DWORD WMessage = CM_PLUGINS_FIRST_METHOD;

    if (!LoadApproximation(Approximation, Settings_Struct.Libraries.ApproximationDll))
    {
        WriteLogError("Error while loading Approximation DLL");
    }
    else
    {
        WIN32_FIND_DATAA fData;
        HANDLE Handle;
        char str[256];
        char *c;
        strcpy(str, "Plugins\\*.dll");
        Handle = FindFirstFile(str, &fData);

        if (Handle != INVALID_HANDLE_VALUE)
        {
            CPlugIn *pl=new CPlugIn;
            SearchPath("Plugins\\", fData.cFileName, NULL, 256, pl->Name, &c);
            if (LoadPlugin(pl, WMessage))
            {
                Plugins.Add(pl);
            }

            while (FindNextFile(Handle, &fData))
            {
                CPlugIn *pl=new CPlugIn;
                SearchPath("Plugins\\", fData.cFileName, NULL, 256, pl->Name, &c);
                if (LoadPlugin(pl, WMessage))
                {
                    Plugins.Add(pl);
                }
            }

            FindClose(Handle);
        }
        
    }
   
    if (!MainRegisterClass (hInstance)) return FALSE;
    if (!PanelsRegisterClass (hInstance)) return FALSE;

//Load all DLL's
    int error=-1;
    if (!LoadGraphics_(Dlls.Graphics.InitRC, Dlls.Graphics.DestroyRC, Dlls.Graphics.ResizeRC, Dlls.Graphics.DrawGraphics, Dlls.Graphics.DrawPicture, Dlls.Graphics.DrawColorPicture, Dlls.Graphics.DrawLayers, Settings_Struct.Libraries.GraphicsDll, Dlls.Graphics.hInstance)) 
    {
        WriteLogError("Error while loading Graphics DLL");
        error = 1;
        MessageBox(NULL, "Error while loading Graphics DLL", "Error", MB_OK|MB_SYSTEMMODAL|MB_ICONSTOP);
    } else
    if (!LoadReadData(Dlls.ReadData.ReadData, Settings_Struct.Libraries.ReadDataDll, Dlls.ReadData.hInstance)) 
    {
        WriteLogError("Error while loading ReadData DLL");
        error = 2;
        MessageBox(NULL, "Error while loading ReadData DLL", "Error", MB_OK|MB_SYSTEMMODAL|MB_ICONSTOP);
    };
    if (!LoadInput(Dlls.Input.InitGUIInput, 
                   Dlls.Input.InitConsoleInput, 
                   Dlls.Input.InitFileInput, 
                   Dlls.Input.GUIInput, 
                   Dlls.Input.ConsoleInput, 
                   Dlls.Input.FileInput,
                   Settings_Struct.Libraries.InputDll,
                   Dlls.Input.hInstance)) 
    {
        WriteLogError("Error while loading Input DLL");
        error = 3;
        MessageBox(NULL, "Error while loading Input DLL", "Error", MB_OK|MB_SYSTEMMODAL|MB_ICONSTOP);
    };

    if (!InitInstance (hInstance, SW_NORMAL, hWnd)) //nCmdShow
    {
        WriteLogError("Error while initializing instance");
        error = 0;
        MessageBox(NULL, "Error while initializing instance", "Error", MB_OK|MB_SYSTEMMODAL|MB_ICONSTOP);
    }
    if (!CreatePanels (hInstance,hWnd, PicturePanel, GraphicPanel, Separator)) //nCmdShow
    {
        WriteLogError("Error while initializing instance");
        error = 0;
        MessageBox(NULL, "Error while initializing panels", "Error", MB_OK|MB_SYSTEMMODAL|MB_ICONSTOP);
    }
    if (!Dlls.Input.InitGUIInput(hInstance, hWnd))
    {
        WriteLogError("Error while initializing GUI input");
        error = 0;
        MessageBox(NULL, "Error while initializing GUI input", "Error", MB_OK|MB_SYSTEMMODAL|MB_ICONSTOP);
    }

    switch (error)
    {
        case 0:
            FreeLibrary(Dlls.Input.hInstance);
        case 3:
            FreeLibrary(Dlls.ReadData.hInstance);
        case 2:
            FreeLibrary(Dlls.Graphics.hInstance);    
        case 1:
            WriteLogFinished();
            CloseLog();
            SaveSettings(Settings_Struct, SettingsPath);
            return error+1;
        default:
            break;
    }
    CloseLog();

    Interpret(Settings_Struct.AutoScripts.OnStart, GlobalVariables, Plugins, Dlls, Picture, ColorPicture, Approximation, Graphics, Layers);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) 
    {
        TranslateMessage(&msg);
        TranslateAccelerator(hWnd,accel,&msg);
        DispatchMessage(&msg);
    }

    Interpret(Settings_Struct.AutoScripts.OnExit, GlobalVariables, Plugins, Dlls, Picture, ColorPicture, Approximation, Graphics, Layers);

    FreeLibrary(Dlls.Input.hInstance);
    FreeLibrary(Dlls.ReadData.hInstance);    
    FreeLibrary(Dlls.Graphics.hInstance);

    CListItem *C = Plugins.GetFirst();
    while (C)
    {
        FreePlugins((CPlugIn*)C);
        C = C->GetNext();
    };

    OpenLog();
    WriteLogFinished();
    CloseLog();

    //Settings_Struct.Windows.Height=(int)MainHeight;
    //Settings_Struct.Windows.Width=(int)MainWidth;
    Settings_Struct.Windows.SeparatorPosition=(int)SeparatorPosition;

    SaveSettings(Settings_Struct, SettingsPath);
    SaveLangStruct(Lng_Main_Struct, Settings_Struct.Language.LngFile);
    return msg.wParam;
}


BOOL MainRegisterClass(HINSTANCE hInstance)//registration of class for main window (Tishka17)
{

    WNDCLASS wndclass;
    wndclass.style             = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wndclass.lpfnWndProc       = (WNDPROC)MainWndProc;
    wndclass.cbClsExtra        = 0;
    wndclass.cbWndExtra        = 0;
    wndclass.hInstance         = hInstance;
    wndclass.hIcon             = LoadIcon(NULL, IDI_HAND);
    wndclass.hCursor           = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground     = (HBRUSH)(COLOR_WINDOW); 
    wndclass.lpszMenuName      = 0;
    wndclass.lpszClassName     = szMainWindowclass;
    return (RegisterClass(&wndclass)!=0);
}

BOOL    PanelsRegisterClass   (HINSTANCE hInstance)
{
    WNDCLASS wndclass;
    wndclass.style             = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wndclass.lpfnWndProc       = (WNDPROC)PicturePanelProc;
    wndclass.cbClsExtra        = 0;
    wndclass.cbWndExtra        = 0;
    wndclass.hInstance         = hInstance;
    wndclass.hIcon             = LoadIcon(NULL, IDI_HAND);
    wndclass.hCursor           = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground     = (HBRUSH)(COLOR_WINDOW); 
    wndclass.lpszMenuName      = 0;
    wndclass.lpszClassName     = szPicturePanelclass;

    WNDCLASS wndclass2;
    wndclass2.style             = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wndclass2.lpfnWndProc       = (WNDPROC)GraphicPanelProc;
    wndclass2.cbClsExtra        = 0;
    wndclass2.cbWndExtra        = 0;
    wndclass2.hInstance         = hInstance;
    wndclass2.hIcon             = LoadIcon(NULL, IDI_HAND);
    wndclass2.hCursor           = LoadCursor(NULL, IDC_ARROW);
    wndclass2.hbrBackground     = (HBRUSH)(COLOR_WINDOW); 
    wndclass2.lpszMenuName      = 0;
    wndclass2.lpszClassName     = szGraphicPanelclass;

     WNDCLASS wndclass3;
    wndclass3.style             = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wndclass3.lpfnWndProc       = (WNDPROC)SeparatorProc;
    wndclass3.cbClsExtra        = 0;
    wndclass3.cbWndExtra        = 0;
    wndclass3.hInstance         = hInstance;
    wndclass3.hIcon             = LoadIcon(NULL, IDI_HAND);
    wndclass3.hCursor           = LoadCursor(NULL, IDC_SIZEWE);
    wndclass3.hbrBackground     = (HBRUSH)(COLOR_WINDOW); 
    wndclass3.lpszMenuName      = 0;
    wndclass3.lpszClassName     = szSeparatorClass;
    return (RegisterClass(&wndclass)!=0) && (RegisterClass(&wndclass2)!=0)  && (RegisterClass(&wndclass3)!=0) ;
}

BOOL InitInstance(HINSTANCE hInstance, 
                  int nCmdShow, HWND &hWnd)
{
    MainWidth=(float)Settings_Struct.Windows.Width;
    SeparatorPosition=(float)Settings_Struct.Windows.SeparatorPosition;
  hWnd = CreateWindow(
              szMainWindowclass, 
              szMainTitle,
              WS_OVERLAPPEDWINDOW|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,
              CW_USEDEFAULT,                                //left
              CW_USEDEFAULT,                                //top 
              Settings_Struct.Windows.Width,                //width
              Settings_Struct.Windows.Height,               //height
              0, 
              0, 
              hInstance, 
              NULL);
  if (!hWnd) 
      return FALSE;

  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);

  return TRUE;
}

BOOL    CreatePanels(HINSTANCE hInstance, HWND &main, HWND &Picture, HWND &Graphic, HWND &Separator)
{
    Picture = CreateWindow(
              szPicturePanelclass, 
              "PICTURE",
              WS_CHILD|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,
              0,                                //left
              0,                                //top 
              Settings_Struct.Windows.SeparatorPosition-4,   //width
              Settings_Struct.Windows.Height,                                          //height
              main, 
              0, 
              hInstance, 
              NULL);
    if (!Picture) 
        return FALSE;
    Graphic = CreateWindow(
              szGraphicPanelclass, 
              "GRAPHIC",
              WS_CHILD|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,
              Settings_Struct.Windows.SeparatorPosition+4,  //left
              0,                                //top 
              Settings_Struct.Windows.Width-Settings_Struct.Windows.SeparatorPosition-6,                                          //width
              Settings_Struct.Windows.Height,                                          //height
              main, 
              0, 
              hInstance, 
              NULL);
    if (!Graphic) 
        return FALSE;
    Separator = CreateWindow(
              szSeparatorClass, 
              "GRAPHIC",
              WS_CHILD|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,
              Settings_Struct.Windows.SeparatorPosition-3,  //left
              0,                                //top 
              6,                                          //width
              Settings_Struct.Windows.Height,   //height
              main, 
              0, 
              hInstance, 
              NULL);
    if (!Separator) 
        return FALSE;
    UpdateWindow(main);
    return true;
}
LRESULT CALLBACK GraphicPanelProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static void* hDC;
    static void* hRC;
    switch (message) 
    {
        case WM_CREATE:
        {
            Dlls.Graphics.InitRC(hWnd, hDC, hRC);
            break;
        }
        case WM_DESTROY:
        {
            Dlls.Graphics.DestroyRC(hWnd, hDC, hRC);
            PostQuitMessage(0);
            break;
        }
        case WM_SIZE:
        break;
        case WM_PAINT:
        if (!Loading)
        {
            //DrawColorPicture(hWnd, hDC, hRC, ColorPicture);
        }
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

LRESULT CALLBACK PicturePanelProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static void* hDC;
    static void* hRC;
    switch (message) 
    {
        case WM_CREATE:
        {
            Dlls.Graphics.InitRC(hWnd, hDC, hRC);
            break;
        }
        case WM_DESTROY:
        {
            Dlls.Graphics.DestroyRC(hWnd, hDC, hRC);
            PostQuitMessage(0);
            break;
        }
        case WM_SIZE:
        break;
        case WM_PAINT:
        if (!Loading)
        {
            if (DrawPictureType==1) Dlls.Graphics.DrawPicture(hWnd, hDC, hRC, Picture, (CLayer*)Layers.First);
            else if (DrawPictureType==2) Dlls.Graphics.DrawColorPicture(hWnd, hDC, hRC, ColorPicture, (CLayer*)Layers.First);
			else 
            {
                Dlls.Graphics.DrawLayers(hWnd, hDC, hRC, (CLayer*)Layers.First);
            }
        }
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

LRESULT CALLBACK SeparatorProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  HDC hDC;
  PAINTSTRUCT ps;
  static int left;
  static bool down=false;
  static  int width;
  static  int height;
  static int pos=0;

  switch (message) {
    case WM_CREATE: /* начало работы программы */
      break;

    case WM_SIZE: /* изменение размеров окна */
      width = LOWORD(lParam);
      height = HIWORD(lParam);
      break;
    case WM_LBUTTONDOWN:
    {
        SetCapture(hWnd);
        down=true;
        //MessageBox(hWnd, "Separator Click!","!@!@",MB_OK);
        break;
    }
    case WM_LBUTTONUP:
    {
        ReleaseCapture();
//        int y=pos;
        int x=(pos>32767)?-(pos^65535):pos;
        SeparatorPosition+=x;
            MoveWindow(PicturePanel, 0,0, (int)SeparatorPosition-4,height, true);
            MoveWindow(Separator, (int)SeparatorPosition-3,0, 6, height, true);
            MoveWindow(GraphicPanel, (int)SeparatorPosition+4,0,(int) MainWidth-(int)SeparatorPosition-6,height,true);
        down=false;
        pos=0;
        break;
    }
     case WM_MOUSEMOVE:
    {
        if (down)
        {
            RECT rc;
            GetWindowRect(hWnd, &rc);
            left=(rc.left);
            pos=LOWORD(lParam);


            int x=(pos>32767)?-(pos^65535):pos;
            SeparatorPosition+=x;
            if (SeparatorPosition<20) SeparatorPosition = 20;
            if (SeparatorPosition+20>MainWidth) SeparatorPosition=(float)MainWidth-20;
            MoveWindow(PicturePanel, 0,0, (int)SeparatorPosition-4,height,true);
            MoveWindow(Separator, (int)SeparatorPosition-3,0, 6,height,true);
            MoveWindow(GraphicPanel, (int)SeparatorPosition+4,0,(int) MainWidth-(int)SeparatorPosition-6,height,true);
            pos=0;
        }
        break;
    }

    case WM_PAINT: /* перерисовка рабочей области */
    {
          hDC = BeginPaint(hWnd, &ps);
          /* рисуем фигуру */
          HPEN light=CreatePen(PS_SOLID,1,RGB(255,255,255));
          HPEN dark=CreatePen(PS_SOLID,1,RGB(60,60,60));
          SelectObject(hDC, dark);
          MoveToEx(hDC, width-1, 0, NULL);
          LineTo(hDC, 0, 0);
          LineTo(hDC, 0, height-1);
          SelectObject(hDC, light);
          LineTo(hDC, width-1, height-1);
          LineTo(hDC, width-1, 0);

           SelectObject(hDC, light);
          MoveToEx(hDC, width-3, 2, NULL);
          LineTo(hDC, 2, 2);
          LineTo(hDC, 2, height-3);
          SelectObject(hDC, dark);
          LineTo(hDC, width-3, height-3);
          LineTo(hDC, width-3, 2);
          //Rectangle(hDC, 2,2,width-2,height-2);
          DeleteObject(light);
          DeleteObject(dark);
          EndPaint(hWnd, &ps);
          break;
    }
    case WM_DESTROY: /* завершение программы */
      PostQuitMessage(0);
      break;

    default: /* обработка всех остальный сообщений */
      return DefWindowProc(hWnd, message, wParam, lParam);
  }
  return 0;

}

LRESULT CALLBACK MainWndProc(HWND hWnd, 
                             UINT message, 
                             WPARAM wParam, 
                             LPARAM lParam)                           //window function for main window
{
    static  int width;
    static  int height;

    switch (message) 
    {
    /*case WM_GETMINMAXINFO:
        {
            MINMAXINFO *mm=(MINMAXINFO*)&lParam;
            mm->ptMinTrackSize.x=500;
            mm->ptMinTrackSize.y=500;
        }
        break;*/
    case WM_CREATE:
    {
            CreateMainMenu(Plugins, MenuStruct, Lng_Main_Struct, hWnd);
            CreateRecentMenu(MenuStruct.Recent, Settings_Struct);
            accel=CreateAccelTable();
            //SetMenuItem(hFileMenu, CM_FILE_SAVE, MFS_GRAYED, FALSE);
            break;
    }

    case WM_COMMAND:
            switch LOWORD(wParam) 
            {
                case CM_FILE_EXIT:
                    {
                        DestroyWindow(hWnd);
                        return 0;        
                    }
                case CM_FILE_OPEN:
                    { 
                        Loading = TRUE;
                        ResetMenu(MenuStruct.Recent, Settings_Struct.Recent.Number);                        
                        if (ShowFileDialog(hWnd, 
                            FileName,                                 //name of file
                            Lng_Main_Struct.Dialogs.OpenDialogCaption,//caption of window
                            "\0", 
                            Lng_Main_Struct.FileFilter.Filter,        //filter 
                            FDOPENMODE))                              //mode = open file
                        { 

                            bool find=false;
                            for (int i=0;i<Settings_Struct.Recent.Number;i++)
                            {
                                if (!strcmp(Settings_Struct.Recent.File[i], FileName))
                                {
                                    find=true;
                                    strcpy(Settings_Struct.Recent.File[i], Settings_Struct.Recent.File[0]);
                                    strcpy(Settings_Struct.Recent.File[0], FileName);
                                }
                            }
                            if (!find)
                            {
                                for (int i=Settings_Struct.Recent.Number;i>0;i--)
                                {
                                     strcpy(Settings_Struct.Recent.File[i], Settings_Struct.Recent.File[i-1]);
                                }
                                strcpy(Settings_Struct.Recent.File[0], FileName);
                                if (Settings_Struct.Recent.Number<Settings_Struct.Recent.MaxNumber) Settings_Struct.Recent.Number++;
                            }
                            OpenLog();
                            //char function[500]="ReadData";
                            //strcat(function, FileName);
                            //strcat(function, "\", &Picture)");
                            WriteLogFunctionCall("ReadData.dll", "ReadData");
                            LPSYSTEMTIME Time1 = new _SYSTEMTIME;
                            LPSYSTEMTIME Time2 = new _SYSTEMTIME;
                            GetLocalTime(Time1);
                            LongString str="";
                            int a = Dlls.ReadData.ReadData(FileName, &ColorPicture, str); 
                            GetLocalTime(Time2);
                            WriteLogFunctionCallTime(Time1, Time2);
                            WriteLog(a);
                            WriteLogFunctionCallEnd();
                            WriteLogFunctionString(str);
                            CloseLog();
                            Interpret(Settings_Struct.AutoScripts.OnOpenImage, GlobalVariables, Plugins, Dlls, Picture, ColorPicture, Approximation, Graphics, Layers);
                            //disable squares drawing
//                            SetMenuItem(hViewMenu, CM_VIEW_DRAWSQ, MFS_UNCHECKED, FALSE);
//                            DrawSquares = false;
                            //show panels as they were before hiding
//                            RightPanel.Restore();
//                            LeftPanel.Restore();
                        } 
                        CreateRecentMenu(MenuStruct.Recent, Settings_Struct);
                        Loading = FALSE;
                        return 0;
                    } 
                case CM_FILE_RUNBAT:
                    {
                        if (ShowFileDialog(hWnd, 
                            FileName,                                 //name of file
                            Lng_Main_Struct.Dialogs.OpenDialogCaption,//caption of window
                            "\0", 
                            "Batch files (*.bat, *.fbat)\0*.bat;*.fbat\0All files (*.*)\0*.*\0",        //filter 
                            FDOPENMODE))                              //mode = open file
                        { 
                            //char s[MAX_PATH+50];
                            //strcpy(s,"-l __fractals_console.log.html -f ");
                            //strcat(s, FileName);
                            //ShellExecute(hWnd, "open", "Console.exe", s, ModulePath, SW_RESTORE);
                            Loading = TRUE;
                            Interpret(FileName, GlobalVariables, Plugins, Dlls, Picture, ColorPicture, Approximation, Graphics, Layers);
                            Loading = TRUE;
                        } 
                        return 0;
                    }
                case CM_FILE_SAVE:
                    { 
                        Loading = TRUE;
                        //hide panels
//                        LeftPanel.TempHide();
//                        RightPanel.TempHide();                
                        if (ShowFileDialog(hWnd, 
                            FileName,                                 //name of file
                            Lng_Main_Struct.Dialogs.SaveDialogCaption,//caption of window
                            "\0", 
                            Lng_Main_Struct.FileFilter.Filter,        //filter
                            FDSAVEMODE))                              //mode = save file
                        { 
                            MessageBox(hWnd, FileName, "You have chosen: ", MB_OK); 
                        } 
                        Loading = FALSE;
                        //show panels as they were before hiding
//                        RightPanel.Restore();
//                        LeftPanel.Restore();
                        return 0;
                    } 
                case CM_HELP_ABOUT:
                    {
                        //hide panels
//                        LeftPanel.ChangeStatus(LeftPanel.cmDisable, NULL);
//                        RightPanel.ChangeStatus(RightPanel.cmDisable, NULL);
                        MessageBox(hWnd, "\n         FRACTALS ANALYSER "
                                        
                                       "\n\n  Version: 01.04.2007 "
                                         
                                       "\n\n  Created by _NSFGroup:"
                                       
                                       "\n\n    Ftvkun (hardcore debugging, fileworks, filters, sleeping),"
                                         "\n    Tishka17 (hardcore debugging, alhorythms, gui_, console, scripts, logs, plugins, methods of calculation, "
                                         "\n               generators, drawing, filters, ini, lng files, dialogs, source correction),"
                                         "\n    heil0 (drawing of graphics, internet searching, permanent bugs && debugging), "
                                         "\n    Waller (old helpfile, entusiasme, reports && several ideas)"
                                       "\n\n Build by MS Visual C++ 6.0"
                                         "\n Packed by UPX 2.0", 
                                       "About", MB_RTLREADING|MB_ICONWARNING| MB_ABORTRETRYIGNORE);

                        SendMessage(hWnd, WM_PAINT, 0, 0);
                        return 0;
                    }
                case CM_VIEW_SHOWLOG:
                    {
                        ShellExecute(hWnd, "open", ::LogFilePath, NULL, NULL, SW_RESTORE);
                        break;
                    }
                case CM_HELP_HELP:
                    {
                        ShellExecute(0, "open", Settings_Struct.Language.HlpFile, "", ModulePath, SW_MAXIMIZE);
                        break;
                    }
                case CM_HELP_HOTKEYS:
                    {
                        ShellExecute(0, "open", Settings_Struct.Language.HotKeysFile, "", ModulePath, SW_MAXIMIZE);
                        break;
                    }
                case CM_HELP_INTERNET:
                    {
                        ShellExecute(0, "open", "http://tishka-17.narod.ru", "", "", SW_MAXIMIZE);
                        break;
                    }
                case CM_VIEW_PICTUREPANEL_PICTURE:
                    {
                        if (DrawPictureType==1) break;
                        DrawPictureType=1;
                        SetMenuItem(MenuStruct.View, CM_VIEW_PICTUREPANEL_PICTURE, MFS_CHECKED, FALSE);
                        SetMenuItem(MenuStruct.View, CM_VIEW_PICTUREPANEL_COLORPICTURE, MFS_UNCHECKED, FALSE);
                        SetMenuItem(MenuStruct.View, CM_VIEW_PICTUREPANEL_NOPICTURE, MFS_UNCHECKED, FALSE);
                        UpdateWindow(PicturePanel);
                        break;
                    }
                case CM_VIEW_PICTUREPANEL_COLORPICTURE:
                    {
                        if (DrawPictureType==2) break;
                        DrawPictureType=2;
                        SetMenuItem(MenuStruct.View, CM_VIEW_PICTUREPANEL_PICTURE, MFS_UNCHECKED, FALSE);
                        SetMenuItem(MenuStruct.View, CM_VIEW_PICTUREPANEL_COLORPICTURE, MFS_CHECKED, FALSE);
                        SetMenuItem(MenuStruct.View, CM_VIEW_PICTUREPANEL_NOPICTURE, MFS_UNCHECKED, FALSE);
                        UpdateWindow(PicturePanel);
                        break;
                    }
                case CM_VIEW_PICTUREPANEL_NOPICTURE:
                    {
                        if (DrawPictureType==0) break;
                        DrawPictureType=0;
                        SetMenuItem(MenuStruct.View, CM_VIEW_PICTUREPANEL_PICTURE, MFS_UNCHECKED, FALSE);
                        SetMenuItem(MenuStruct.View, CM_VIEW_PICTUREPANEL_COLORPICTURE, MFS_UNCHECKED, FALSE);
                        SetMenuItem(MenuStruct.View, CM_VIEW_PICTUREPANEL_NOPICTURE, MFS_CHECKED, FALSE);
                        UpdateWindow(PicturePanel);
                        break;
                    }
                case CM_VIEW_PICTUREPANEL_DISABLED:
                    {
                        if (PictureDisabled && !GraphicDisabled)
                        {
                            ShowWindow(PicturePanel, SW_SHOW);
                            ShowWindow(Separator, SW_SHOW);
                            MoveWindow(PicturePanel, 0,0, (int)SeparatorPosition-4,height,true);
                            MoveWindow(Separator, (int)SeparatorPosition-3,0, 6,height,true);
                            MoveWindow(GraphicPanel, (int)SeparatorPosition+4,0,(int) MainWidth-(int)SeparatorPosition-6,height,true);
                            PictureDisabled=false;
                            SetMenuItem(MenuStruct.View, CM_VIEW_PICTUREPANEL_DISABLED, MFS_UNCHECKED, FALSE);
                        }
                        else if (PictureDisabled)
                        {
                            ShowWindow(PicturePanel, SW_SHOW);
                            MoveWindow(PicturePanel, 0,0, (int)MainWidth,height,true);
                            PictureDisabled=false;
                            SetMenuItem(MenuStruct.View, CM_VIEW_PICTUREPANEL_DISABLED, MFS_UNCHECKED, FALSE);
                        }
                        else if (!GraphicDisabled)
                        {
                            ShowWindow(PicturePanel, SW_HIDE);
                            ShowWindow(Separator, SW_HIDE);
                            MoveWindow(GraphicPanel, 0,0, (int)MainWidth,height,true);
                            PictureDisabled=true;
                            SetMenuItem(MenuStruct.View, CM_VIEW_PICTUREPANEL_DISABLED, MFS_CHECKED, FALSE);
                        }
                        else
                        {
                            ShowWindow(PicturePanel, SW_HIDE);
                            PictureDisabled=true;
                            SetMenuItem(MenuStruct.View, CM_VIEW_PICTUREPANEL_DISABLED, MFS_CHECKED, FALSE);
                        }
                        break;
                    }
                case CM_VIEW_GRAPHICPANEL_DISABLED:
                    {
                        if (!PictureDisabled && GraphicDisabled)
                        {
                            ShowWindow(GraphicPanel, SW_SHOW);
                            ShowWindow(Separator, SW_SHOW);
                            MoveWindow(PicturePanel, 0,0, (int)SeparatorPosition-4,height,true);
                            MoveWindow(Separator, (int)SeparatorPosition-3,0, 6,height,true);
                            MoveWindow(GraphicPanel, (int)SeparatorPosition+4,0,(int) MainWidth-(int)SeparatorPosition-6,height,true);
                            GraphicDisabled=false;
                            SetMenuItem(MenuStruct.View, CM_VIEW_GRAPHICPANEL_DISABLED, MFS_UNCHECKED, FALSE);
                        }
                        else if (GraphicDisabled)
                        {
                            ShowWindow(GraphicPanel, SW_SHOW);
                            MoveWindow(GraphicPanel, 0,0, (int)MainWidth,height,true);
                            GraphicDisabled=false;
                            SetMenuItem(MenuStruct.View, CM_VIEW_GRAPHICPANEL_DISABLED, MFS_UNCHECKED, FALSE);
                        }
                        else if (!PictureDisabled)
                        {
                            ShowWindow(GraphicPanel, SW_HIDE);
                            ShowWindow(Separator, SW_HIDE);
                            MoveWindow(PicturePanel, 0,0, (int)MainWidth,height,true);
                            GraphicDisabled=true;
                            SetMenuItem(MenuStruct.View, CM_VIEW_GRAPHICPANEL_DISABLED, MFS_CHECKED, FALSE);
                        }
                        else
                        {
                            ShowWindow(GraphicPanel, SW_HIDE);
                            GraphicDisabled=true;
                            SetMenuItem(MenuStruct.View, CM_VIEW_GRAPHICPANEL_DISABLED, MFS_CHECKED, FALSE);
                        }
                        break;
                    }               
                default:
                    if (LOWORD(wParam)>=CM_PLUGINS_FIRST_METHOD && LOWORD(wParam)<=CM_PLUGINS_LAST_METHOD)
                    {
                        Loading=true;
                        GraphicsNumber=Graphics.GetNumber();
                        LayersNumber=Layers.GetNumber();
						CM = LOWORD(wParam);
                        RunFunctionByCM(LOWORD(wParam), (CPlugIn*)Plugins.GetFirst(), &Approximation, &Picture, &ColorPicture, &Graphics, &Layers, Dlls.Input.GUIInput,true);
                        ResetMenu(MenuStruct.PicturePanel, LayersNumber,6);
                        CreatePicturePanelMenu(MenuStruct.PicturePanel, Lng_Main_Struct, (CLayer*)Layers.GetFirst(), true);
                        ResetMenu(MenuStruct.GraphicPanel, GraphicsNumber+2);
                        CreateGraphicPanelMenu(MenuStruct.GraphicPanel, Lng_Main_Struct, (CGraphic*)Graphics.GetFirst());
                        Loading=false;
                    }
                    else if (LOWORD(wParam)>=CM_VIEW_PICTUREPANEL_FIRST && LOWORD(wParam)<=CM_VIEW_PICTUREPANEL_DISABLED)
                    {
                        int x=LOWORD(wParam)-CM_VIEW_PICTUREPANEL_FIRST ;
                        int i=0;
                        CLayer *gr=(CLayer*)Layers.GetFirst();
                        while(gr!=NULL)
                        {
                            if (i==x) 
                            {
                                gr->Draw=!gr->Draw;
                                SetMenuItem(MenuStruct.PicturePanel, CM_VIEW_PICTUREPANEL_FIRST+i, ((gr->Draw)?MFS_CHECKED:MFS_UNCHECKED), FALSE); 
                                break;
                            }
                            gr=(CLayer*)gr->GetNext();
                            i++;
                        }
                        break;
                    }
                    else if (LOWORD(wParam)>=CM_VIEW_GRAPHICPANEL_FIRST && LOWORD(wParam)<=CM_VIEW_GRAPHICPANEL_DISABLED)
                    {
                        int x=LOWORD(wParam)-CM_VIEW_GRAPHICPANEL_FIRST;
                        int i=0;
                        CGraphic *gr=(CGraphic*)Graphics.GetFirst();
                        while(gr!=NULL)
                        {
                            if (i==x) 
                            {
                                gr->Draw=!gr->Draw;
                                SetMenuItem(MenuStruct.GraphicPanel, CM_VIEW_GRAPHICPANEL_FIRST+i, ((gr->Draw)?MFS_CHECKED:MFS_UNCHECKED), FALSE); 
                                break;
                            }
                            gr=(CGraphic*)gr->GetNext();
                            i++;
                        }
                        break;
                    }
                    else if (LOWORD(wParam)>=CM_FILE_RECENT_FIRST && LOWORD(wParam)<=CM_FILE_RECENT_LAST)//recent file
                    {
                        Loading = TRUE;
                        ResetMenu(MenuStruct.Recent, Settings_Struct.Recent.Number);
                        bool find=false;
                        int i=LOWORD(wParam)-CM_FILE_RECENT_FIRST;
                        strcpy(FileName, Settings_Struct.Recent.File[i]);
                        strcpy(Settings_Struct.Recent.File[i], Settings_Struct.Recent.File[0]);
                        strcpy(Settings_Struct.Recent.File[0], FileName);
                        ResetMenu(MenuStruct.Recent, Settings_Struct.Recent.Number);
                        CreateRecentMenu(MenuStruct.Recent, Settings_Struct);
                        OpenLog();
                        //char function[500]="ReadData";
                        //strcat(function, FileName);
                        //strcat(function, "\", &Picture)");
                        WriteLogFunctionCall("ReadData.dll", "ReadData");
                        LPSYSTEMTIME Time1 = new _SYSTEMTIME;
                        LPSYSTEMTIME Time2 = new _SYSTEMTIME;
                        GetLocalTime(Time1);
                        LongString str="";
                        int a = Dlls.ReadData.ReadData(FileName, &ColorPicture, str); 
                        GetLocalTime(Time2);
                        WriteLogFunctionCallTime(Time1, Time2);
                        WriteLog(a);
                        WriteLogFunctionCallEnd();
                        WriteLogFunctionString(str);
                        CloseLog();
                        Interpret(Settings_Struct.AutoScripts.OnOpenImage, GlobalVariables, Plugins, Dlls, Picture, ColorPicture, Approximation, Graphics, Layers);
                        Loading = FALSE;
                        return 0;
                    }
            };
            break;
    case WM_DESTROY:
        {
            DestroyAcceleratorTable(accel);
            PostQuitMessage(0);
            break;
        }
    case WM_SIZE:
            width = LOWORD(lParam);
            height = HIWORD(lParam);
            if (width<10)break;
            {SeparatorPosition=(float)SeparatorPosition*width/MainWidth;}
            if (SeparatorPosition<20) SeparatorPosition = 20;
            if (SeparatorPosition+20>width) SeparatorPosition=(float)width-20;
            MainWidth=(float)width;
            MainHeight=(float)height;
            RECT rc;
            GetWindowRect(hWnd, &rc);
            Settings_Struct.Windows.Width=rc.right-rc.left;
            Settings_Struct.Windows.Height=rc.bottom-rc.top;
            
    case WM_MOVE:
        {
            if (width<10) break;
            if (!PictureDisabled && !GraphicDisabled)
            {
                MoveWindow(PicturePanel, 0,0, (int)SeparatorPosition-4,height,true);
                MoveWindow(Separator, (int)SeparatorPosition-3,0, 6,height,true);
                MoveWindow(GraphicPanel, (int)SeparatorPosition+4,0,(int) MainWidth-(int)SeparatorPosition-6,height,true);
            }
            else if (!PictureDisabled)
            {
                MoveWindow(PicturePanel, 0,0, (int)MainWidth,height,true);
            }
            else if (!GraphicDisabled)
            {
                MoveWindow(GraphicPanel, 0,0, (int)MainWidth,height,true);
            }
            CutCorner(hWnd);
            break;
        }
    case IM_INPUTFINISHED:
        {
            Loading=true;
            GraphicsNumber=Graphics.GetNumber();
            LayersNumber=Layers.GetNumber();
            RunFunctionByCM(CM,(CPlugIn*)Plugins.GetFirst(), &Approximation, &Picture, &ColorPicture, &Graphics, &Layers);//, Dlls.Input.GUIInput, false); 
			CM=0;
            ResetMenu(MenuStruct.PicturePanel, LayersNumber,6);
            CreatePicturePanelMenu(MenuStruct.PicturePanel, Lng_Main_Struct, (CLayer*)Layers.GetFirst(),true);
            ResetMenu(MenuStruct.GraphicPanel, GraphicsNumber+2);
            CreateGraphicPanelMenu(MenuStruct.GraphicPanel, Lng_Main_Struct, (CGraphic*)Graphics.GetFirst());
            Loading=false;
        }
    case WM_PAINT:
        if (!Loading)
        {
            //SendMessage(PicturePanel,WM_PAINT, 0, 0);
            if (!PictureDisabled && !GraphicDisabled) UpdateWindow(Separator);
            if (!GraphicDisabled) UpdateWindow(GraphicPanel);
            if (!PictureDisabled) UpdateWindow(PicturePanel);
//            SendMessage(RightPanel.hWnd,WM_PAINT, 0, 0);
        }
        PaintCorner(hWnd);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

HACCEL CreateAccelTable (void)                                        //create table of hotkeys
{
    ACCEL accel[10];
    
    //File menu
    accel[0].fVirt=FVIRTKEY|FCONTROL;
    accel[0].key=0x4f;                                                //Ctrl+O
    accel[0].cmd=CM_FILE_OPEN;                                        //file/open

    accel[1].fVirt=FVIRTKEY|FCONTROL;
    accel[1].key=0x53;                                                //Ctrl+S
    accel[1].cmd=CM_FILE_SAVE;                                        //file/save

    accel[2].fVirt=FVIRTKEY|FALT;
    accel[2].key=0x58;                                                //Alt+X 
    accel[2].cmd=CM_FILE_EXIT;                                        //file/exit

    accel[3].fVirt=FVIRTKEY|FCONTROL;
    accel[3].key=0x51;                                                //Ctrl+Q
    accel[3].cmd=CM_FILE_EXIT;                                        //file/exit

    //view menu
    accel[4].fVirt=FVIRTKEY|FALT;
    accel[4].key=0x50;                                                //Alt+P
    accel[4].cmd=CM_VIEW_PICTUREPANEL_NOPICTURE;                                //view/Left/Disable
    accel[5].fVirt=FVIRTKEY|FALT;
    accel[5].key=0x47;                                                //Alt+G
    accel[5].cmd=0;//CM_VIEW_RIGHT_DISABLE;                                //view/Right/Disable

    accel[6].fVirt=FVIRTKEY|FALT;
    accel[6].key=0x4c;                                                //Alt+L
    accel[6].cmd=CM_VIEW_SHOWLOG;                                     //view/ShowLog

    accel[7].fVirt=FVIRTKEY|FCONTROL;
    accel[7].key=0x75;                                                //Ctrl+F6
    accel[7].cmd=CM_VIEW_DRAWSQ;                                      //calculate/draw squares

    //help menu
    accel[8].fVirt=FVIRTKEY;
    accel[8].key=0x70;                                                //F1
    accel[8].cmd=CM_HELP_HELP;                                        //help/help
     
    accel[9].fVirt=FVIRTKEY|FCONTROL;
    accel[9].key=0x70;                                                //Ctrl+F1    
    accel[9].cmd=CM_HELP_ABOUT;                                       //help/about program

    return CreateAcceleratorTable((LPACCEL)accel,10);
}
