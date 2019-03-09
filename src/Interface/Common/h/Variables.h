#ifndef __VARIABLES_H
#define __VARIABLES_H

  #include "..\..\..\Common\H\data.h"
  #include "..\..\..\Common\H\Plugins.h"
  #include "..\..\..\Common\H\Approximator.h"
  #include "stdio.h"
  
  //command messages 
       //for menu
       #define CM_FILE_OPEN                         1010
       #define CM_FILE_SAVE                         1011
       #define CM_FILE_RUNBAT                       1012
       #define CM_FILE_EXIT                         1013

       #define CM_FILE_RECENT_FIRST                  900
       #define CM_FILE_RECENT_LAST                  1000

       #define CM_VIEW_SHOWLOG                      1022
       #define CM_VIEW_DRAWSQ                       1031

       #define CM_HELP_ABOUT                        1040
       #define CM_HELP_HOTKEYS                      1041
       #define CM_HELP_INTERNET                     1042
       #define CM_HELP_HELP                         1043 

       #define CM_VIEW_PICTUREPANEL_PICTURE         1100  
       #define CM_VIEW_PICTUREPANEL_COLORPICTURE    1101
       #define CM_VIEW_PICTUREPANEL_NOPICTURE       1102
       #define CM_VIEW_PICTUREPANEL_FIRST           1103
       #define CM_VIEW_PICTUREPANEL_DISABLED        1199  

       #define CM_VIEW_GRAPHICPANEL_FIRST           1202 
       #define CM_VIEW_GRAPHICPANEL_DISABLED        1299

       #define CM_PLUGINS_FIRST_METHOD              1300
       #define CM_PLUGINS_LAST_METHOD               2000


       #define CM_VIEW_SQURES_SIZE_MIN              3000
       #define CM_VIEW_SQURES_SIZE_MAX              3020

       #define CM_PANELS_POSITION_CASCADE           3030
       #define CM_PANELS_POSITION_TILE_VERTCALLY    3031
       #define CM_PANELS_POSITION_TILE_HORISONTALLY 3032
       #define CM_PANELS_POSITION_CLOSE_ALL         3033

 
  //function types
      //for Graphics_.dll
      typedef BOOL (*FInitRC)         (HWND hWnd1, void *&hdc, void *&hrc);//initialisation drawing
      typedef void (*FDestroyRC)      (HWND hWnd,  void *&hdc, void *&hrc);//deinitialisation of drawing
      typedef void (*FResize)         (HWND hWnd1, void *&hdc, void *&hrc);//resizing of canvas
  //drawing functions:
  typedef void (*FDrawGraphics)   (HWND hWnd,  void*&hDC, void *&hRC, CGraphic *);									//draws graphic of polynom
  typedef void (*FDrawPicture)    (HWND hWnd,  void *&hDC, void *&hRC, TImage &picture, CLayer*);                            //draws black-n-white picture 
  typedef void (*FDrawColorPicture)    (HWND hWnd,  void *&hDC, void *&hRC, TColorImage &picture, CLayer*);                  //draws color picture
  typedef void (*FDrawAccLayers)    (HWND hWnd,  void *&hDC, void *&hRC, CLayer*);                  //draws color picture

//  typedef void (*FDrawWithSquaresPicture)(HWND hWnd, void*&hDC, void *&hRC, TImage &picture, CNet *);               //draws b&w picture with net of squares on it


  //for ReadData.dll
  typedef int  (*FReadData)       (const char *File_Name, TColorImage *Image, LongString str);//loading picture from file
    
  //for Input.dll
//  typedef bool (*FInitGUIInput)     (HINSTANCE, HWND);
//  typedef bool (*FInitConsoleInput) (HINSTANCE);
//  typedef bool (*FInitFileInput)    (HINSTANCE);
//  typedef bool (*FInput)         (void *x, CDataDescription *dd, DWORD number);
//  typedef bool (*FConsoleInput)     (void *x, CDataDescription *dd, DWORD number);
//  typedef bool (*FFileInput)        (void *x, CDataDescription *dd, DWORD number);

  struct SDLLs
  {
      struct 
      {
        FReadData ReadData;

        HINSTANCE hInstance;
      } ReadData;

      struct
      {
          FInitRC InitRC;
          FDestroyRC DestroyRC;
          FResize ResizeRC;

          FDrawGraphics DrawGraphics;
          FDrawPicture DrawPicture;
          FDrawColorPicture DrawColorPicture;
          FDrawAccLayers DrawLayers;

          HINSTANCE hInstance;
      } Graphics;

      struct
      {
          FInitGUIInput InitGUIInput;
          FInitConsoleInput InitConsoleInput;
          FInitFileInput InitFileInput;
          FInput ConsoleInput;
          FInput GUIInput;
          FFileInput FileInput;

          HINSTANCE hInstance;
      } Input;
  };
#endif //__VARIABLES_H
