#ifndef __GRAPHIC_CPP__
#define __GRAPHIC_CPP__

#include "..\H\Graphic.h"
CGraphic::CGraphic():CListItem()
{
    PointsNumber = 0;
    Points = NULL;
    QuotientsNumber = -1;
    Quotients = NULL;
    Type = CGraphic::gtUnknown;
    Draw = false;
    DrawFunction = false;
    FunctionAdress = NULL;
};

CGraphic::~CGraphic()
{
    if (QuotientsNumber>=0)
    {
        VirtualFree( (void*)Quotients, (QuotientsNumber+1+QuotientsNumber1) * sizeof(double), MEM_DECOMMIT); 
    }
    if (PointsNumber>=0)
    {
        VirtualFree( (void*)Points, PointsNumber * sizeof(TPoint), MEM_DECOMMIT); 
    }
    PointsNumber = 0;
    Points = NULL;
    QuotientsNumber = -1;
    FunctionAdress = NULL;
    Quotients = NULL;
};
void CGraphic::SetQuotientsNumber(long _d, long _d1)
{
    if (QuotientsNumber>=0)
    {
        VirtualFree( (void*)Quotients, (QuotientsNumber+1+QuotientsNumber1) * sizeof(double), MEM_DECOMMIT); 
    }
    QuotientsNumber = _d;
    QuotientsNumber1 = (_d1>0)?_d1:0;
    Quotients = (double*) VirtualAlloc(NULL, (QuotientsNumber+1+QuotientsNumber1) * sizeof(double), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
};

void CGraphic::SetPointsNumber(DWORD _d)
{
    if (PointsNumber>=0)
    {
        VirtualFree( (void*)Points, PointsNumber * sizeof(TPoint), MEM_DECOMMIT); 
    }
    PointsNumber = _d;
    Points = (TPoint*) VirtualAlloc(NULL, PointsNumber * sizeof(TPoint), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
};

//====================================================
CLayer::CLayer():CListItem()
{
    PointsNumber = 0;
    Points = NULL;
    Type = CLayer::ltPoints;
    Draw = false;
};

CLayer::~CLayer()
{
    if (PointsNumber>=0)
    {
        VirtualFree( (void*)Points, PointsNumber * sizeof(TPoint), MEM_DECOMMIT); 
    }
    PointsNumber = 0;
    Points = NULL;
};

void CLayer::SetPointsNumber(DWORD _d)
{
    if (PointsNumber>=0)
    {
        VirtualFree( (void*)Points, PointsNumber * sizeof(TPoint), MEM_DECOMMIT); 
    }
    PointsNumber = _d;
    Points = (TPoint*) VirtualAlloc(NULL, PointsNumber * sizeof(TPoint), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
};


#endif //__GRAPHIC_CPP__