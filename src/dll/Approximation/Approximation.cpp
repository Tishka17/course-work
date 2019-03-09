// Approximation.cpp : Defines the entry point for the DLL application.
//

#include "..\..\Common\H\wndws.h"

#include "..\..\Common\H\Plugins.h"
#include "..\..\Common\H\Graphic.h"
#include "Approximation.h"

#include "math.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
                     )
{
    return TRUE;
};


//Least Squares function for linear polinom searches for function y=k*x+b;
int APlusBX (CGraphic* _G)
{      
    _G->Type = CGraphic::gtPolynom;
    if (_G->PointsNumber == 0)
    {
        _G->SetQuotientsNumber(0);  
        return 1;
    }
    else
    {
        _G->SetQuotientsNumber(1);  
    }
    //Need to solve sustem:
    long double u=0;                                              //   n*b + k*u = v
    long double v=0;                                              //  -u*b + k*s = r
    long double s=0;
    long double r=0;
    for (DWORD i=0; i<_G->PointsNumber; i++)
    {
        u+=_G->Points[i].X;
        v+=_G->Points[i].Y;
        s+=_G->Points[i].X*_G->Points[i].X;
        r-=_G->Points[i].X*_G->Points[i].Y;
    }
    if (u*u==s*_G->PointsNumber) 
    {
        _G->SetQuotientsNumber(0);
        return 1;                      //the line is x=const or there are no points on it
    }
    _G->Quotients[1]=((_G->PointsNumber*r+u*v)/(u*u-s*_G->PointsNumber));
    _G->Quotients[0]=v/_G->PointsNumber-_G->Quotients[1]*u/_G->PointsNumber;
    return 0;
}

long double f(long double x)
{
   return 1/x;
}

int APlusBX2 (CGraphic* _G)
{     
    _G->Type = CGraphic::gtPolynom;
    if (_G->PointsNumber == 0)
    {
        _G->SetQuotientsNumber(0);  
        return 1;
    }
    else
    {
        _G->SetQuotientsNumber(2);  
    }
    long double p=0;                                               //Need to solve sustem:
    long double u=0;                                              //   p*b + k*u = v
    long double v=0;                                              //  -u*b + k*s = r
    long double s=0;
    long double r=0;
    for (DWORD i=0; i<_G->PointsNumber; i++)
    {
       /* u-=a[i].X*a[i].X;
        v+=a[i].Y;
        s-=a[i].X*a[i].X*a[i].X*a[i].X;
        r+=a[i].X*a[i].X*a[i].Y;*/
		
		p+=1*f(_G->Points[i].X);
        u-=_G->Points[i].X*_G->Points[i].X*f(_G->Points[i].X);
        v+=_G->Points[i].Y*f(_G->Points[i].X);
        s-=_G->Points[i].X*_G->Points[i].X*_G->Points[i].X*_G->Points[i].X*f(_G->Points[i].X);
        r+=_G->Points[i].X*_G->Points[i].Y*_G->Points[i].X*f(_G->Points[i].X);
    }
    if (u*u==s*p) 
    {
        _G->SetQuotientsNumber(0);
        return 1;                      //the line is x=const or there are no points on it
    } 
    _G->Quotients[2]=-((p*r+u*v)/(u*u-s*p));
    _G->Quotients[1]=0;
    _G->Quotients[0]=v/p+_G->Quotients[2]*u/p;
    return 0;
}

