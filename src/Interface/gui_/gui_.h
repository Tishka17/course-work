#ifndef _GUI_H_
#define _GUI_H_

//functioons
    BOOL    MainRegisterClass     (HINSTANCE hInstance);                     //registration of class for main window (Tishka17)
    BOOL    PanelsRegisterClass   (HINSTANCE hInstance);                     //registration of panels classes (Tishka17)

    BOOL    InitInstance          (HINSTANCE hInstance, int nCmdShow, HWND &hWnd);       //initialization of window/application
    BOOL    CreatePanels          (HINSTANCE hInstance, HWND &main, HWND &Picture, HWND &Graphic, HWND &Separator);//

    LRESULT CALLBACK MainWndProc  (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);//function of window for main window
    LRESULT CALLBACK PicturePanelProc  (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);//function of window for Picture panel
    LRESULT CALLBACK GraphicPanelProc  (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);//function of window for Graphic panel
    LRESULT CALLBACK SeparatorProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    HACCEL  CreateAccelTable      (void);                                    //create table of hotkeys


#endif //_GUI_H_