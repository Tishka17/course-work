// Dimension.cpp : Defines the entry point for the DLL application.
//

#include "..\..\Common\H\wndws.h"
#include "..\..\Common\H\data.h"
#include "..\..\Common\H\_List.h"
#include "math.h"
#include "..\..\Common\H\Plugins.h"
#include "..\..\Common\H\Graphic.h"
#include "Dimension.h"


BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
                     )
{
    return TRUE;
}


void LoadContents(CPlugIn *Plugin)
{
	if (Plugin==NULL) MessageBox(NULL,"!@!@","!@!@", MB_OK);
    Plugin->Functions.Clear();

    strcpy(Plugin->Caption, "Dimension calculator");
    //MessageBox(NULL, Plugin->Caption, "", MB_OK);
    Plugin->Functions.ElementSize = sizeof(CFunction);
    CFunction *f = (CFunction*)VirtualAlloc(NULL, sizeof(CFunction), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    f->SetAll("Minkovsky", "Minkovsky dimension: NULL method", CFunction::ftBWSimple);
    Plugin->Functions.Add(f);

    f = (CFunction*)VirtualAlloc(NULL, sizeof(CFunction), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    f->SetAll("Minkovsky1", "Minkovsky dimension: modified NULL method", CFunction::ftBWSimple);
    Plugin->Functions.Add(f);

    f = (CFunction*)VirtualAlloc(NULL, sizeof(CFunction), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    f->SetAll("Hausdorf", "Hausdorf dimension: NULL method", CFunction::ftBWSimple);
    Plugin->Functions.Add(f);

    f = (CFunction*)VirtualAlloc(NULL, sizeof(CFunction), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    f->SetAll("Hausdorf1", "Hausdorf dimension: modified NULL method", CFunction::ftBWSimple);
    Plugin->Functions.Add(f);

//    Plugin->Graphics.Clear();

};


//Function counts number of squares with elements of fractal in them
DWORD CountNull(TImage *pict,                               //Picture with fractal
                 DWORD size)                                 //size of square
{
    DWORD n=0;                                               //number of squares
    DWORD i;                                                 //number of current row of squares
    DWORD j;                                                 //horisontal position in row
    DWORD k;                                                 //vertical position in row
    for (i=0;i<=pict->Height()/size;i++)                      //i is number of the row
    {                                                  
        for (j=0; j<=pict->Width();j++)                       //horizontal position
        {
            for (k=0; k<=size; k++)                          //vertical position in row
            {
                if (k+i*size>=pict->Height()) break;            
                if (j>=pict->Width()) break;
                if (pict->Pixel(i*size+k,j)>0)                //square is not empty
                {
                    n++;                                     //increment number
                    j=j-j%size+size;                         // move to the next square
                    k=-1;
                }
            }
        }
    }
    return n;
};


//Function counts number of squares with elements of fractal in them
DWORD CountTishka(TImage *pict,                              //Picture with fractal
                   DWORD size)                               //size of square
{
    DWORD n=0;                                               //number of squares
    DWORD i;                                                 //number of current row of squares
    DWORD j;                                                 //horisontal position in row
    DWORD k;                                                 //vertical position in row
    for (i=0;i<=pict->Height()/size;i++)                      //i is number of the row
    {                                                 
        for (j=0; j<=pict->Width();j++)                       //horizontal position
        {
            for (k=0; k<=size; k++)                          //vertical position in row
            {
                if (k+i*size>=pict->Height()) break;            
                if (j>=pict->Width()) break;
                if (pict->Pixel(i*size+k,j)>0)                //square is not empty
                {
                    n++;                                     //increment number
                    j+=size;                                 // move to the next square
                    k=-1;
                }
            }
        }
    }
    return n;
};


     
//=================================================================================================================
// Function name    : GetCountArray   
// Description        : This finction calculates number of squares for different sizes, using NULL method
// Return type        : void 
// Argument 1       : TImage *pict
// Argument 2       : DWORD minsize
// Argument 3       : DWORD maxsize
// Argument 4       : DWORD _count
// Argument 5       : CGraphic *_G
void GetCountArray(TImage *pict,                            //picture with fractal
                             DWORD minsize,                  //minimal size of square
                             DWORD maxsize,                  //maximal size of square
                             DWORD _count,                   //number of iterations
                             CGraphic *_G)
{
    if (pict->Width()<10 || pict->Height()<10) //picture is too small
    {
        _G->SetQuotientsNumber(-1);
        _G->SetPointsNumber(0);
        return;
    }
    if (minsize<3) 
    {
        minsize = 3;
    };
    double CurSize = minsize;
    double step      = 1;
    step  = exp(log(maxsize/double(minsize))/_count);
    if (step<1.1) 
    {
        step  = 1.1;
        _count = int (log(maxsize/double(minsize))/step);
    };
    _G->SetPointsNumber(_count);
    TPoint *last = _G->Points + _count;                                  //pointer to the end of points array
    for (TPoint *i=_G->Points; i<last; i++)
    {
        i->X = log(DWORD(CurSize));
        i->Y = log(CountNull(pict, DWORD(CurSize)));
        CurSize *= step;
    };
    return;
};

//=================================================================================================================
// Function name    : GetCountArrayTishka   
// Description        : This finction calculates number of squares for different sizes, using modified NULL method
// Return type        : void 
// Argument 1       : TImage *pict
// Argument 2       : DWORD minsize
// Argument 3       : DWORD maxsize
// Argument 4       : DWORD _count
// Argument 5       : CGraphic *_G
void GetCountArrayTishka(TImage *pict,                      //picture with fractal
                             DWORD minsize,                  //minimal size of square
                             DWORD maxsize,                  //maximal size of square
                             DWORD _count,                   //number of iterations
                             CGraphic *_G)
{
    if (pict->Width()<10 || pict->Height()<10) //picture is too small
    {
        _G->SetQuotientsNumber(-1);
        _G->SetPointsNumber(0);
        return;
    }
    if (minsize<3) 
    {
        minsize = 3;
    };
    double CurSize = minsize;
    double step      = 1;
    step  = exp(log(maxsize/double(minsize))/_count);
    if (step<1.1) 
    {
        step  = 1.1;
        _count = int (log(maxsize/double(minsize))/step);
    };
    _G->SetPointsNumber(_count);
    TPoint *last = _G->Points + _count;                                  //pointer to the end of points array
    for (TPoint *i=_G->Points; i<last; i++)
    {
        i->X = log(DWORD(CurSize));
        i->Y = log(CountTishka(pict, DWORD(CurSize)));
        CurSize *= step;
    };
    return;
};



//=================================================================================================================
// Function name    : GetPoints
// Description        : Stores points into CGraphic object
// Return type        : void 
// Argument 1       : CGraphic *_G
// Argument 2       : DWORD _count
// Argument 3       : DWORD *_size
// Argument 4       : DWORD *_number
void GetPoints(CGraphic *_G, 
               DWORD _count, 
               DWORD *_size, 
               DWORD *_number)                                        //create array of points from two arrays
{
    _G->SetPointsNumber(_count);
    
    TPoint *last = _G->Points + _count;                                  //pointer to the end of points array
    DWORD *s = _size;                                                 //current size
    DWORD *n = _number;                                               //current number

    for (TPoint *i=_G->Points; i<last; i++)
    {
        i->X = log(*s);
        i->Y = log(*n);
        s++;
        n++;
    }
}

double Minkovsky(TImage* Picture, CList* Graphics, CList *, LongString str, SApproximation* Approximation)
{
    CGraphic *_G = (CGraphic*)Graphics->GetFirst();
    Graphics->ElementSize = sizeof(CGraphic);
    while (_G && strcmp(_G->Caption, "Minkovsky function: square sizes"))
    {
        _G = (CGraphic*)_G->GetNext();
    }
    if (!_G)
    {
        _G = (CGraphic*)VirtualAlloc(NULL, sizeof(CGraphic), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
        strcpy(_G->Caption, "Minkovsky function: square sizes");
        Graphics->Add(_G);
    };

    GetCountArray(Picture, 3, (Picture->Height()>Picture->Width())?Picture->Width()/4:Picture->Height()/4, 30, _G);
    Approximation->APlusBX(_G);
    return (_G->QuotientsNumber>0)?-_G->Quotients[1]:-1;
}

double Minkovsky1(TImage* Picture, CList* Graphics, CList *, LongString str, SApproximation* Approximation)
{
    CGraphic *_G = (CGraphic*)Graphics->GetFirst();
    Graphics->ElementSize = sizeof(CGraphic);
    while (_G && strcmp(_G->Caption, "Minkovsky edited function: square sizes"))
    {
        _G = (CGraphic*)_G->GetNext();
    }
    if (!_G)
    {
        _G = (CGraphic*)VirtualAlloc(NULL, sizeof(CGraphic), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
        strcpy(_G->Caption, "Minkovsky edited function: square sizes");
        Graphics->Add(_G);
    };
    GetCountArrayTishka(Picture, 3, (Picture->Height()>Picture->Width())?Picture->Width()/4:Picture->Height()/4, 30, _G);
    Approximation->APlusBX(_G);
    return (_G->QuotientsNumber>0)?-_G->Quotients[1]:-1;
};


double Hausdorf1(TImage* Picture, CList* Graphics, CList *, LongString str, SApproximation* Approximation)
{
    DWORD j;
    CGraphic *_G = (CGraphic*)Graphics->GetFirst();
    Graphics->ElementSize = sizeof(CGraphic);
    while (_G && strcmp(_G->Caption, "Minkovsky edited function: square sizes"))
    {
        _G = (CGraphic*)_G->GetNext();
    }
    if (!_G)
    {
        _G = (CGraphic*)VirtualAlloc(NULL, sizeof(CGraphic), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
        strcpy(_G->Caption, "Minkovsky edited function: square sizes");
        Graphics->Add(_G);
        GetCountArrayTishka(Picture, 3, (Picture->Height()>Picture->Width())?Picture->Width()/4:Picture->Height()/4, 30, _G);
        Approximation->APlusBX(_G);
    };
    CGraphic *_P = (CGraphic*)Graphics->GetFirst();
    Graphics->ElementSize = sizeof(CGraphic);
    while (_P && strcmp(_P->Caption, "Hausdorf edited function: extrapolation of dimension"))
    {
        _P = (CGraphic*)_P->GetNext();
    }
    if (!_P)
    {
        _P = (CGraphic*)VirtualAlloc(NULL, sizeof(CGraphic), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
        strcpy(_P->Caption, "Hausdorf edited function: extrapolation of dimension");
        Graphics->Add(_P);    
    };
    if (_G->PointsNumber<12) return -1;
    _P->SetPointsNumber(_G->PointsNumber-10);

    CGraphic TG;
    TG.SetPointsNumber(10);

    for (DWORD i=0;i<_P->PointsNumber;i++)
    {
        for (j=0;j<10;j++)
        {
            TG.Points[j].X = _G->Points[i+j].X;
            TG.Points[j].Y = _G->Points[i+j].Y;
        }
        Approximation->APlusBX(&TG);
        _P->Points[i].X = exp(TG.Points[0].X);
        _P->Points[i].Y = (TG.QuotientsNumber>0)?-TG.Quotients[1]:0;
    }

    Approximation->APlusBX2(_P);
    return _P->Quotients[0];
};

double Hausdorf(TImage* Picture, CList* Graphics, CList *, LongString str, SApproximation* Approximation)
{
    DWORD j;
    CGraphic *_G = (CGraphic*)Graphics->GetFirst();
    Graphics->ElementSize = sizeof(CGraphic);
    while (_G && strcmp(_G->Caption, "Minkovsky function: square sizes"))
    {
        _G = (CGraphic*)_G->GetNext();
    }
    if (!_G)
    {
        _G = (CGraphic*)VirtualAlloc(NULL, sizeof(CGraphic), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
        strcpy(_G->Caption, "Minkovsky function: square sizes");
        Graphics->Add(_G);
        GetCountArray(Picture, 3, (Picture->Height()>Picture->Width())?Picture->Width()/4:Picture->Height()/4, 30, _G);
        Approximation->APlusBX(_G);
    };
    CGraphic *_P = (CGraphic*)Graphics->GetFirst();
    Graphics->ElementSize = sizeof(CGraphic);
    while (_P && strcmp(_P->Caption, "Hausdorf function: extrapolation of dimension"))
    {
        _P = (CGraphic*)_P->GetNext();
    }
    if (!_P)
    {
        _P = (CGraphic*)VirtualAlloc(NULL, sizeof(CGraphic), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
        strcpy(_P->Caption, "Hausdorf function: extrapolation of dimension");
        Graphics->Add(_P);    
    };
    if (_G->PointsNumber<12) return -1;
    _P->SetPointsNumber(_G->PointsNumber-10);

    CGraphic TG;
    TG.SetPointsNumber(10);

    for (DWORD i=0;i<_P->PointsNumber;i++)
    {
        for (j=0;j<10;j++)
        {
            TG.Points[j].X = _G->Points[i+j].X;
            TG.Points[j].Y = _G->Points[i+j].Y;
        }
        Approximation->APlusBX(&TG);
        _P->Points[i].X = exp(TG.Points[0].X);
        _P->Points[i].Y = (TG.QuotientsNumber>0)?-TG.Quotients[1]:0;
    }

    Approximation->APlusBX2(_P);
    return _P->Quotients[0];
};
