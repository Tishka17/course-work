#if !defined(_GRAPHICS_H)
#define _GRAPHICS_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>

#define EXPORT extern "C" __declspec (dllexport)


#include "..\..\Common\H\data.h"                                    //header for picture bitmap
//#include "..\..\Common\H\Squares.h"                             //header for drawing Net of swimming squares          
#include "..\..\Common\H\Plugins.h"

BOOL bSetupPixelFormat(HDC &hdc);


EXPORT BOOL InitRC(HWND hWnd1, void *&hdc, void *&hrc);         //initialization of RC
EXPORT void DestroyRC(HWND hWnd, void *&hdc, void *&hrc);       //destroy RC    
EXPORT void Resize(HWND hWnd1, void *&hdc, void *&hrc);         //resize scene    
//EXPORT void DrawLine(HWND hWnd, void*&hDC, void *&hRC, float k, float b, TPoint *points,DWORD count);   //drawing function
EXPORT void DrawPicture(HWND hWnd, void*&hDC, void *&hRC, TImage &picture);                             //drawing function
EXPORT void DrawColorPicture(HWND hWnd, void*&hDC, void *&hRC, TColorImage &picture);                   //drawing function for color picture
EXPORT void DrawGraphics(HWND hWnd, void*&hDC, void *&hRC, CGraphic *);									//drawing function
//EXPORT void DrawWithSquaresPicture(HWND hWnd, void*&hDC, void *&hRC, TImage &picture, CNet *);          //drawing squares function

EXPORT void DrawAccPicture(HWND hWnd,void*&hDC, void *&hRC, TImage &picture, CLayer *First);
EXPORT void DrawAccColorPicture(HWND hWnd, void*&hDC, void *&hRC, TColorImage &picture, CLayer *);                   //drawing function for color picture
EXPORT void DrawAccGraphics(HWND hWnd, void*&hDC, void *&hRC, CGraphic *);									//drawing function
EXPORT void DrawAccLayers(HWND hWnd, void*&hDC, void *&hRC, CLayer *);									//drawing function
void DrawLayers(HWND hWnd, void*&hDC, void *&hRC, CLayer *First);
#endif
