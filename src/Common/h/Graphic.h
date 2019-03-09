#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__
#include "_LIST.h"
#include "data.h"


typedef double (gFunction)(double *,long,long=0);

class CGraphic:public CListItem
{
    protected:
    public:
    enum cgType{ //constants to declare type of function to be drawn on graphic
                      gtUnknown,//Unknown function type
                      gtExternal,//used call of the externall function (look FunctionAdress)
                      gtPolynom,//simple polynom
                      gtTrigonometricPolynom//
                    };

        ShortString   Caption;//caption of graphic

        DWORD         PointsNumber;//number of points in graphic
        TPoint       *Points;
        long          QuotientsNumber;//number of quotents (==0 when only 1 quotent)
        long          QuotientsNumber1;//used when needed two types of quotents (>=0)
        double       *Quotients;//
        bool Draw;//visibility
        bool DrawFunction;//draw line of approximating function
        cgType Type;//type of approximation function
        gFunction *FunctionAdress;//pointer to external approximating function [if need]
        
        CGraphic();
       ~CGraphic();
        void SetQuotientsNumber(long _d, long _d1=0);
        void SetPointsNumber(DWORD _d);
};

class CLayer:public CListItem
{
    protected:
    public:
    enum clType{ //constants to declare type of function to be drawn on graphic
                      ltUnknown,//Unknown function type
                      ltPoints,//just points
                      ltPolygon,//simple polygom
                      ltSpline,//Spline
                      ltRectangles,//
                      ltEllipses//
                    };

        ShortString   Caption;//caption of graphic

        DWORD         PointsNumber;//number of points in graphic
        TPoint       *Points;
        
        double Size1, Size2;//just two doubles
        bool Draw;
        clType Type;
        
        CLayer();
       ~CLayer();
        void SetPointsNumber(DWORD _d);
};
#endif //__GRAPHIC_H__