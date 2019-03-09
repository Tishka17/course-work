#ifndef __CORNERS_CPP
#define __CORNERS_CPP
#include "..\H\Corners.h"

void CutCorner(HWND hWnd)
{

    HRGN hRgn1, hRgn2;                                      // regions to create cutted corner

    RECT rc;                                                //Rectangle with window inside
    GetWindowRect(hWnd, &rc);
    OffsetRect(&rc, - rc.left, - rc.top);                   //move the co-ordinate beginning point to  the left-top corner of the window

    hRgn1 = CreateRectRgnIndirect(&rc);                     //full rectangle

    POINT corner[3];
    corner[0].x=rc.right-30;
    corner[0].y=rc.bottom;
    corner[1].x=rc.right;
    corner[1].y=rc.bottom-30;
    corner[2].x=rc.right;
    corner[2].y=rc.bottom;

    hRgn2=CreatePolygonRgn(corner, 3, ALTERNATE);           //delete corner

    CombineRgn(hRgn1, hRgn1, hRgn2, RGN_XOR);               //Union
    DeleteObject(hRgn2); 

    corner[0].x=rc.right-20;
    corner[1].y=rc.bottom-20;

    hRgn2=CreatePolygonRgn(corner, 3, ALTERNATE);           //new piece of corner

    CombineRgn(hRgn1, hRgn1, hRgn2, RGN_OR);                //Union
    DeleteObject(hRgn2); 
 
//installing the created region for window and immediate repainting of this window
    SetWindowRgn(hWnd, hRgn1, TRUE);
    DeleteObject(hRgn1);
    PaintCorner(hWnd);
}

void PaintCorner(HWND hWnd)
{
    RECT rc;                                                //Rectangle with window inside
    GetClientRect(hWnd, &rc);
    OffsetRect(&rc, - rc.left, - rc.top);                   //move the co-ordinate beginning point to  the left-top corner of the window
  
    POINT corner;
    corner.x=0;
    corner.y=0;
  
    PAINTSTRUCT ps;
    HDC hdc=BeginPaint(hWnd, &ps);                          //hdc of the window
  
    //Light side in the corner  
    HPEN pen=CreatePen(PS_INSIDEFRAME, 1, RGB (255,255,255));//pen to draw on the window
    SelectObject(hdc, pen);
    MoveToEx(hdc,rc.right-10, rc.bottom, &corner);
    LineTo(hdc, rc.right, rc.bottom-10);
    DeleteObject(pen);
  
    pen=CreatePen(PS_INSIDEFRAME, 1, RGB (220,220,220));
    SelectObject(hdc, pen);
    MoveToEx(hdc,rc.right-12, rc.bottom, &corner);
    LineTo(hdc, rc.right, rc.bottom-12);
    DeleteObject(pen);
  
    //Dark side in the corner
    pen=CreatePen(PS_INSIDEFRAME, 1, RGB (70,70,70));
    SelectObject(hdc, pen);
    MoveToEx(hdc,rc.right-25, rc.bottom, &corner);
    LineTo(hdc, rc.right, rc.bottom-25);
    DeleteObject(pen);
  
    pen=CreatePen(PS_INSIDEFRAME, 1, RGB (110,110,110));
    SelectObject(hdc, pen);
    MoveToEx(hdc,rc.right-26, rc.bottom, &corner);
    LineTo(hdc, rc.right, rc.bottom-26);
    DeleteObject(pen);

    EndPaint(hWnd, &ps);//The end.
    ReleaseDC(hWnd, hdc);

}

#endif //__CORNERS_CPP
