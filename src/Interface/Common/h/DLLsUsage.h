#ifndef __DLLSUSAGE_H__
#define __DLLSUSAGE_H__

#include "..\..\..\Common\H\Approximator.h"
#include "Variables.h"
int LoadApproximation(SApproximation &Approximation, 
                      char *path
                     );

int LoadGraphics_(  FInitRC &InitRC,
                    FDestroyRC &DestroyRC,
                    FResize &Resize,
                    FDrawGraphics &DrawGraphics,
                    FDrawPicture &DrawPicture,
                    FDrawColorPicture &DrawColorPicture,
					FDrawAccLayers &DrawLayers,
//                    FDrawWithSquaresPicture &DrawWithSquaresPicture,
                    char *path,
                    HINSTANCE &DLL
                );

int LoadReadData(   FReadData &ReadData,
                    char *path,
                    HINSTANCE &DLL
                );
                  
int LoadInput   ( FInitGUIInput &InitGUIInput,
                    FInitConsoleInput &InitConsoleInput,
                    FInitFileInput &InitFileInput,
                    FInput &GUIInput,
                    FInput &ConsoleInput,
					FFileInput &FileInput,
                    char *path,
                    HINSTANCE &DLL
                );

#endif //__DLLSUSAGE_H__