#ifndef __DLLSUSAGE_CPP__
#define __DLLSUSAGE_CPP__

#include "..\H\DLLsUsage.h"

//load functions from dlls
//for Approximation.dll
int LoadApproximation(SApproximation &Approximation, char *path)
{
    Approximation.hInstance = LoadLibrary(path);
    if (!Approximation.hInstance) {return 0;}
    Approximation.APlusBX   = (fApproximator)          (::GetProcAddress(Approximation.hInstance, "APlusBX"));
    if (!Approximation.APlusBX) 
    {
        FreeLibrary(Approximation.hInstance);
        return 0;
    }
    Approximation.APlusBX2  = (fApproximator)          (::GetProcAddress(Approximation.hInstance, "APlusBX2"));
    if (!Approximation.APlusBX2)  
    {
        FreeLibrary(Approximation.hInstance);
        return 0;
    }
    return 1;
}  


//for Graphics_.dll
int LoadGraphics_(  FInitRC &InitRC,
                    FDestroyRC &DestroyRC,
                    FResize &Resize,
                    FDrawGraphics &DrawGraphics,
                    FDrawPicture &DrawPicture,
                    FDrawColorPicture &DrawColorPicture,
					FDrawAccLayers &DrawLayers,
//                    FDrawWithSquaresPicture &DrawWithSquaresPicture,
                    char *path,
                    HINSTANCE &DLL)
{   
    DLL = LoadLibrary(path);
    if (!DLL) {return 0;}
    InitRC                   = (FInitRC)          (::GetProcAddress(DLL, "InitRC"));
    if (!InitRC) {return 0;}
    DestroyRC                = (FDestroyRC)       (::GetProcAddress(DLL, "DestroyRC"));
    if (!DestroyRC) {return 0;}
    DrawGraphics             = (FDrawGraphics)    (::GetProcAddress(DLL, "DrawGraphics"));
    if (!DrawGraphics) {return 0;}
    DrawPicture              = (FDrawPicture)     (::GetProcAddress(DLL, "DrawAccPicture"));
    if (!DrawPicture) {return 0;}
    DrawColorPicture              = (FDrawColorPicture)   (::GetProcAddress(DLL, "DrawAccColorPicture"));
    if (!DrawColorPicture) {return 0;}
     DrawLayers              = (FDrawAccLayers)   (::GetProcAddress(DLL, "DrawAccLayers"));
    if (!DrawLayers) {return 0;}



//    DrawWithSquaresPicture   = (FDrawWithSquaresPicture)  (::GetProcAddress(DLL, "DrawWithSquaresPicture"));
//    if (!DrawWithSquaresPicture) {return 0;}
    return 1;
}


//for ReadData.dll
int LoadReadData( FReadData &ReadData,
                  char *path,
                  HINSTANCE &DLL)
{
    DLL = LoadLibrary(path);
    if (!DLL) {return 0;}
    ReadData                 = (FReadData)         (::GetProcAddress(DLL, "ReadData"));
    if (!ReadData) {return 0;}
    return 1;
}

//for Input.dll
int LoadInput( FInitGUIInput &InitGUIInput,
                    FInitConsoleInput &InitConsoleInput ,
                    FInitFileInput &InitFileInput,
                    FInput &GUIInput,
                    FInput &ConsoleInput,
					FFileInput &FileInput,
                    char *path,
                    HINSTANCE &DLL)
{   
    DLL = LoadLibrary(path);
    if (!DLL) {return 0;}
    InitGUIInput          = (FInitGUIInput)     (::GetProcAddress(DLL, "InitGUIInput"));
    if (!InitGUIInput) {return 0;}
    GUIInput              = (FInput)         (::GetProcAddress(DLL, "GUIInput"));
    if (!GUIInput) {return 0;}
    InitConsoleInput          = (FInitConsoleInput) (::GetProcAddress(DLL, "InitConsoleInput"));
    if (!InitConsoleInput) {return 0;}
    InitFileInput             = (FInitFileInput)    (::GetProcAddress(DLL, "InitFileInput"));
    if (!InitFileInput) {return 0;}
    ConsoleInput              = (FInput)     (::GetProcAddress(DLL, "ConsoleInput"));
	if (!ConsoleInput) {return 0;}
    FileInput              = (FFileInput)     (::GetProcAddress(DLL, "FileInput"));
    if (!FileInput) {return 0;}
    return 1;
}


#endif //__DLLSUSAGE_CPP__