// RandomWalk.cpp : Defines the entry point for the DLL application.
//

#include "..\..\Common\H\wndws.h"
//#include "stdlib.h"
#include "..\..\Common\H\data.h"
#include "..\..\Common\H\_List.h"
#include "math.h"
#include "..\..\Common\H\Plugins.h"
#include "..\..\Common\H\Graphic.h"
#include "RandomWalk.h"
#include "Random/NewRandom.h"
#include "string.h"
//#include "math.h"
#include "stdio.h"

#ifndef M_PI
#define M_PI 3.14159265358
#endif //M_PI
#include "time.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
};

#define HIDE_NULL
#define SectorNumber 13
struct RWParam
{
    int x;
    int y;
    int N;
    int T;
    char str[50];
};

struct LWParam
{
    int N;
    int T;
    char str[50];
    char str2[50];
};

void LoadContents(CPlugIn *Plugin)
{
    CDataDescription dd[]={{CDataDescription::dtInt,0,30000,"Start position: coordinate x"},
                           {CDataDescription::dtInt,0,30000,"Start position: coordinate y"},
                           {CDataDescription::dtInt,1,100000,"Number of points"},
                           {CDataDescription::dtInt,21,30000,"Time (Number of iterations)"},
                           {CDataDescription::dtString,2,50,"Name of Layer"}};

    CDataDescription lwdd[]={{CDataDescription::dtInt,1,100000,"Number of points"},
                           {CDataDescription::dtInt,21,30000,"Time (Number of iterations)"},
                           {CDataDescription::dtString,2,50,"Name of Layer for Front"},
                           {CDataDescription::dtString,2,50,"Name of Layer for Positions"}};

    Plugin->Functions.Clear();

    long t;
    RWParam *pp;
    InitRandom(time(&t));//initialize random generator

    strcpy(Plugin->Caption, "RandomWalk");
    Plugin->Functions.ElementSize = sizeof(CFunction);

    CFunction *f = (CFunction*)VirtualAlloc(NULL, sizeof(CFunction), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    f->SetAll("GetStatistics", "Random walk statistics", CFunction::ftBWFunction, 5, dd);
    Plugin->Functions.Add(f);
    pp=(RWParam*)f->Parameters;
    strcpy(pp->str,"Front of Random walk");

    f = (CFunction*)VirtualAlloc(NULL, sizeof(CFunction), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    f->SetAll("GetStatisticsOnFractal", "Random walk on fractal statistics", CFunction::ftBWFunction, 5, dd);
    Plugin->Functions.Add(f);
    pp=(RWParam*)f->Parameters;
    strcpy(pp->str,"Front of Random walk on fractal");

    LWParam *lpp;
    f = (CFunction*)VirtualAlloc(NULL, sizeof(CFunction), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    f->SetAll("WalkingLine", "Random walk from a line statistics", CFunction::ftBWFunction, 4, lwdd);
    Plugin->Functions.Add(f);
    lpp=(LWParam*)f->Parameters;
    strcpy(lpp->str,"Front of Random walk from line");
    strcpy(lpp->str2,"All points in Random walk from line");
	lpp->N=10000;
	lpp->T=100;

//    Plugin->Graphics.Clear();

};

double GetStatistics(void *param,TImage*Pict, CList*Graphics, CList *Layers, LongString str, SApproximation*)
{
    RWParam *p=(RWParam*)param;
    long int y0=p->y, x0=p->x;
    DWORD n=p->N, t=p->T;
    ShortString sn, st;
    LongString mathexpstr,maxlstr,maxnstr,lstr,tstr,buffer;

    sprintf(tstr,"%25s","Time");
    sprintf(lstr,"%25s","Maximal distance");
    sprintf(maxnstr,"%25s","Maximum points         ");
    sprintf(maxlstr,"%25s","Maximum points distance");
    sprintf(mathexpstr,"%25s","Mathematical expectanse");

    sprintf(sn, "\nNumber of points = %d",n);
    strcpy(str, sn);
    sprintf(st, "\nNumber of iterations = %d",t);
    strcat(str, st);

    CLayer *_L=(CLayer*)Layers->GetFirst();
	CLayer *LPoints=(CLayer*)Layers->GetFirst();
    Layers->ElementSize = sizeof(CLayer);
    while (_L && strcmp(_L->Caption, p->str))
    {
        _L = (CLayer*)_L->GetNext();
    }
    if (!_L)
    {
        _L = (CLayer*)VirtualAlloc(NULL, sizeof(CLayer), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
        strcpy(_L->Caption, p->str);
        Layers->Add(_L);
    };

    while (LPoints && strcmp(LPoints->Caption, "All points in rndwlks"))
    {
        LPoints = (CLayer*)LPoints->GetNext();
    }
    if (!LPoints)
    {
        LPoints = (CLayer*)VirtualAlloc(NULL, sizeof(CLayer), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
        strcpy(LPoints->Caption, "All points in rndwlks");
        Layers->Add(LPoints);
    };
	LPoints->Type = CLayer::ltPoints;
    CGraphic *_G = (CGraphic*)Graphics->GetFirst();
    Graphics->ElementSize = sizeof(CGraphic);
    while (_G && strcmp(_G->Caption, "Random walk statistics graphic"))
    {
        _G = (CGraphic*)_G->GetNext();
    }
    if (!_G)
    {
        _G = (CGraphic*)VirtualAlloc(NULL, sizeof(CGraphic), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
        strcpy(_G->Caption, "Random walk statistics graphic");
        Graphics->Add(_G);
    };
    
    long *x=new long[n];
    long *y=new long[n];
    DWORD i=0,j=0, step=t/20;
    int rnd;
    DWORD maxn=0, maxl=0;
    DWORD l=0;
    long double MathExp=0;

    for (i=0;i<n;i++)
    {
        x[i]=x0;
        y[i]=y0;
    }
    _G->SetPointsNumber(t+1);
    for (j=0;j<t;j++)
    {
        l=0;
        maxn=0;
        MathExp=0;
        for (i=0;i<n;i++)
        {
	        rnd=NewRandom()%4;
	        if (rnd==0)      x[i]++;
	        else if(rnd==1)  x[i]--;
	        else if(rnd==2)  y[i]++;
	        else             y[i]--;

            if (l<DWORD(abs(x[i]-x0)+abs(y[i]-y0))) l=abs(x[i]-x0)+abs(y[i]-y0);
            MathExp+=abs(x[i]-x0)+abs(y[i]-y0);
             _G->Points[abs(x[i]-x0)+abs(y[i]-y0)].Y++;
        }
        for (i=0;i<=l;i++)
        {
            if (_G->Points[i].Y>maxn) {maxn=(DWORD)_G->Points[i].Y;maxl=i;}
            _G->Points[i].Y=0;
        }
        if(j%step==0 || j==t-1)
        {
            MathExp/=(double)n;
            sprintf(buffer,"%s | %10d", tstr, j);
            strcpy(tstr,buffer);
            sprintf(buffer,"%s | %10d", lstr, l);
            strcpy(lstr,buffer);
            sprintf(buffer,"%s | %10d", maxnstr, maxn);
            strcpy(maxnstr,buffer);
            sprintf(buffer,"%s | %10d", maxlstr, maxl);
            strcpy(maxlstr,buffer);
            sprintf(buffer,"%s | %10f", mathexpstr, MathExp);
            strcpy(mathexpstr,buffer);
       }

    }

    #ifdef HIDE_NULL
        l=0;
        for (i=0;i<n;i++)
        {
            if (l<DWORD(abs(x[i]-x0)+abs(y[i]-y0))) l=abs(x[i]-x0)+abs(y[i]-y0);
        }
    #else
        l=t;
    #endif
    _G->SetPointsNumber(l+1);
    _G->SetQuotientsNumber(0);
    _G->Quotients[0]=0;

    _L->SetPointsNumber(SectorNumber);
    _L->Draw=true;
    _L->Type = CLayer::ltPolygon;
	LPoints->SetPointsNumber(n);
    for (i=0;i<SectorNumber;i++)
    {
        _L->Points[i].X = x0;
        _L->Points[i].Y = y0;
    }

    for (i=0;i<=l;i++)
    {
        _G->Points[i].Y=0;
    }
    double r;
    double t1;
	int T1;
    for (i=0;i<n;i++)
    {
		LPoints->Points[i].X=x[i];
		LPoints->Points[i].Y=y[i];
        _G->Points[abs(x[i]-x0)+abs(y[i]-y0)].Y++;
		//generating front 
        r = sqrt((x[i]-x0)*(x[i]-x0)+(y[i]-y0)*(y[i]-y0));//distance between current point and start position
        if (r<0.01) continue;
        if (x[i]<x0)//point is lying on the left side 
            t1=(SectorNumber*(M_PI - asin((y[i]-y0)/r))/(2.0*M_PI));
        else //on the right side
            t1=(SectorNumber*asin((y[i]-y0)/r)/(2.0*M_PI));
        if (t1<0) t1 = SectorNumber+t1;
		T1=(int)t1;
        if (sqrt((_L->Points[T1].X-x0)*(_L->Points[T1].X-x0)+(_L->Points[T1].Y-y0)*(_L->Points[T1].Y-y0))<r) 
        {
            _L->Points[T1].X=x[i];
            _L->Points[T1].Y=y[i];
        }
    }
    for (i=0;i<=l;i++)
    {
        if (_G->Points[i].Y>maxn) {maxn=(DWORD)_G->Points[i].Y;maxl=i;}
        _G->Points[i].X=i;
    }
    _G->Quotients[0]=maxn;
    
    sprintf(buffer,"\n %s\n %s\n %s\n %s\n %s", tstr, lstr, maxnstr, maxlstr, mathexpstr);
    strcat(str,buffer);
 
    delete []x;
    delete []y;

    return _G->Quotients[0];
}

double GetStatisticsOnFractal(void *param, TImage* pict, CList*Graphics, CList *Layers, LongString str, SApproximation*)
{
    RWParam *p=(RWParam*)param;
    long int y0=p->y, x0=p->x;
    DWORD n=p->N, t=p->T;
    ShortString sn, st;
    LongString mathexpstr,maxlstr,maxnstr,lstr,tstr,buffer;

    sprintf(tstr,"%25s","Time");
    sprintf(lstr,"%25s","Maximal distance");
    sprintf(maxnstr,"%25s","Maximum points         ");
    sprintf(maxlstr,"%25s","Maximum points distance");
    sprintf(mathexpstr,"%25s","Mathematical expectanse");

    sprintf(sn, "\nPicture size = %dx%d", pict->Width(),pict->Height());
    strcpy(str, sn);
    sprintf(sn,"\nDefault position = %dx%d", x0, y0);
    strcat(str, sn);
    sprintf(sn, "\nNumber of points = %d",n);
    strcat(str, sn);
    sprintf(st, "\nNumber of iterations = %d",t);
    strcat(str, st);
    
    CLayer *_L=(CLayer*)Layers->GetFirst();
	CLayer *LPoints =(CLayer*)Layers->GetFirst();
    Layers->ElementSize = sizeof(CLayer);
    while (_L && strcmp(_L->Caption, p->str))
    {
        _L = (CLayer*)_L->GetNext();
    }
    if (!_L)
    {
        _L = (CLayer*)VirtualAlloc(NULL, sizeof(CLayer), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
        strcpy(_L->Caption, p->str);
        Layers->Add(_L);
    };
	while (LPoints && strcmp(LPoints->Caption, "All points in rndwlks on fractal"))
    {
        LPoints = (CLayer*)LPoints->GetNext();
    }
    if (!LPoints)
    {
        LPoints = (CLayer*)VirtualAlloc(NULL, sizeof(CLayer), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
        strcpy(LPoints->Caption, "All points in rndwlks on fractal");
        Layers->Add(LPoints);
    };
	LPoints->Type = CLayer::ltPoints;
    

    CGraphic *_G = (CGraphic*)Graphics->GetFirst();
    Graphics->ElementSize = sizeof(CGraphic);
    if (!pict->Width() || !pict->Height()) return 0;
    while (_G && strcmp(_G->Caption, "Random walk on fractal statistics graphic"))
    {
        _G = (CGraphic*)_G->GetNext();
    }
    if (!_G)
    {
        _G = (CGraphic*)VirtualAlloc(NULL, sizeof(CGraphic), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
        strcpy(_G->Caption, "Random walk on fractal statistics graphic");
        Graphics->Add(_G);
    };
    
    long *x=new long[n];
    long *y=new long[n];
    DWORD i=0,j=0, step=t/20;
    DWORD maxn=0, maxl=0;
    DWORD l=0;
    long double MathExp=0;
    int rnd;//, frnd;
    for (i=0;i<n;i++)
    {
        x[i]=x0;
        y[i]=y0;
    }
    _G->SetPointsNumber(t+1);
    for (j=0;j<t;j++)
    {
        l=0;
        maxn=0;
        MathExp=0;
        for (i=0;i<n;i++)
        {
			while (1)
			{
				rnd=NewRandom()%4;
				//frnd=rnd;
				//label1:
				if (rnd==0) 
				{
					if (x[i]<(long)pict->Width()-1 && pict->Pixel(y0,x0)==pict->Pixel(y[i],x[i]+1))  
					{
						x[i]++;
						break;
					}
					//else if (frnd!=1) rnd=1;
				}
				if(rnd==1)
				{
					if (x[i]>0 && pict->Pixel(y0,x0)==pict->Pixel(y[i],x[i]-1))  
					{
						x[i]--;
						break;
					}
					//else if (frnd!=2) rnd=2;
				}
				if(rnd==2)
				{
					if (y[i]<(long)pict->Height()-1 && pict->Pixel(y0,x0)==pict->Pixel(y[i]+1,x[i]))  
					{
						y[i]++;
						break;
					}
					//else if (frnd!=3) rnd=3;
				}
				if (rnd==3)
				{
					if(y[i]>0 && pict->Pixel(y0,x0)==pict->Pixel(y[i]-1,x[i])) 
					{
						y[i]--;
						break;
					}
					//else if (frnd!=0) {rnd=0;goto label1;}
				}
				if (!(x[i]<(long)pict->Width()-1 && pict->Pixel(y0,x0)==pict->Pixel(y[i],x[i]+1))  &&
					!(x[i]>0 && pict->Pixel(y0,x0)==pict->Pixel(y[i],x[i]-1))  &&
					!(y[i]<(long)pict->Height()-1 && pict->Pixel(y0,x0)==pict->Pixel(y[i]+1,x[i])) &&
					!(y[i]>0 && pict->Pixel(y0,x0)==pict->Pixel(y[i]-1,x[i])))
					break;


			}
            if (l<DWORD(abs(x[i]-x0)+abs(y[i]-y0))) l=abs(x[i]-x0)+abs(y[i]-y0);
            MathExp+=abs(x[i]-x0)+abs(y[i]-y0);
            _G->Points[abs(x[i]-x0)+abs(y[i]-y0)].Y++;
        }
        for (i=0;i<=l;i++)
        {
            if (_G->Points[i].Y>maxn) {maxn=(DWORD)_G->Points[i].Y;maxl=i;}
            _G->Points[i].Y=0;
        }
        if(j%step==0 || j==t-1)
        {
            MathExp/=(double)n;
            sprintf(buffer,"%s | %10d", tstr, j);
            strcpy(tstr,buffer);
            sprintf(buffer,"%s | %10d", lstr, l);
            strcpy(lstr,buffer);
            sprintf(buffer,"%s | %10d", maxnstr, maxn);
            strcpy(maxnstr,buffer);
            sprintf(buffer,"%s | %10d", maxlstr, maxl);
            strcpy(maxlstr,buffer);
            sprintf(buffer,"%s | %10f", mathexpstr, MathExp);
            strcpy(mathexpstr,buffer);
       }
    }

    #ifdef HIDE_NULL
        l=0;
        for (i=0;i<n;i++)
        {
            if (l<DWORD(abs(x[i]-x0)+abs(y[i]-y0))) l=abs(x[i]-x0)+abs(y[i]-y0);
        }
    #else
        l=t;
    #endif

    _G->SetPointsNumber(l+1);
    _G->SetQuotientsNumber(0);
    _G->Quotients[0]=0;

    _L->SetPointsNumber(SectorNumber);
    _L->Draw=true;
    _L->Type = CLayer::ltPolygon;
    for (i=0;i<SectorNumber;i++)
    {
        _L->Points[i].X = x0;
        _L->Points[i].Y = y0;
    }

    for (i=0;i<=l;i++)
    {
        _G->Points[i].Y=0;
    }
	LPoints->SetPointsNumber(n);

    double r;
    int t1;
	double _t1;
    for (i=0;i<n;i++)
    {
		LPoints->Points[i].X=x[i];
		LPoints->Points[i].Y=y[i];

        _G->Points[abs(x[i]-x0)+abs(y[i]-y0)].Y++;
        r = sqrt((x[i]-x0)*(x[i]-x0)+(y[i]-y0)*(y[i]-y0));
        if (r<0.01) continue;
        if (x[i]<x0) 
            _t1=((M_PI - asin((y[i]-y0)/r))/M_PI/2.0*SectorNumber);
        else 
            _t1=((asin((y[i]-y0)/r))/M_PI/2.0*SectorNumber);
        if (_t1<0) _t1 = SectorNumber+_t1;
		t1=int(_t1);
        if (sqrt((_L->Points[t1].X-x0)*(_L->Points[t1].X-x0)+(_L->Points[t1].Y-y0)*(_L->Points[t1].Y-y0))<r) 
        {
            _L->Points[t1].X=x[i];
            _L->Points[t1].Y=y[i];
        }
    }

    for (i=0;i<=l;i++)
    {
        if (_G->Points[i].Y>maxn) {maxn=(DWORD)_G->Points[i].Y;maxl=i;}
        _G->Points[i].X=i;
        MathExp+=_G->Points[i].Y*_G->Points[i].X;
    }
    _G->Quotients[0]=maxn;
    sprintf(buffer,"\n %s\n %s\n %s\n %s\n %s", tstr, lstr, maxnstr, maxlstr, mathexpstr);
    strcat(str,buffer);
 
    delete []x;
    delete []y;

    return _G->Quotients[0];
}




double WalkingLine(void *param, TImage* pict, CList*Graphics, CList *Layers, LongString str, SApproximation*)
{

    #define Dist(x,y) abs(x)
    LWParam *p=(LWParam*)param;
    DWORD n=p->N, t=p->T;
    ShortString sn, st;
    LongString mathexpstr,maxlstr,maxnstr,lstr,tstr,buffer;

    sprintf(tstr,"%25s","Time");
    sprintf(lstr,"%25s","Maximal distance");
    sprintf(maxnstr,"%25s","Maximum points         ");
    sprintf(maxlstr,"%25s","Maximum points distance");
    sprintf(mathexpstr,"%25s","Mathematical expectanse");

    sprintf(sn, "\nPicture size = %dx%d", pict->Width(),pict->Height());
    strcpy(str, sn);
    sprintf(sn, "\nNumber of points = %d",n);
    strcat(str, sn);
    sprintf(st, "\nNumber of iterations = %d",t);
    strcat(str, st);
    
    CLayer *_L=(CLayer*)Layers->GetFirst();
	CLayer *LPoints =(CLayer*)Layers->GetFirst();
    Layers->ElementSize = sizeof(CLayer);
	int *counts=new int[pict->Height()];//[SectorNumber];//количества точек в каждом из секторов.

    while (_L && strcmp(_L->Caption, p->str))
    {
        _L = (CLayer*)_L->GetNext();
    }
    if (!_L)
    {
        _L = (CLayer*)VirtualAlloc(NULL, sizeof(CLayer), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
        strcpy(_L->Caption, p->str);
        Layers->Add(_L);
    };
	while (LPoints && strcmp(LPoints->Caption, p->str2))
    {
        LPoints = (CLayer*)LPoints->GetNext();
    }
    if (!LPoints)
    {
        LPoints = (CLayer*)VirtualAlloc(NULL, sizeof(CLayer), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
        strcpy(LPoints->Caption, p->str2);
        Layers->Add(LPoints);
    };
	LPoints->Type = CLayer::ltPoints;
    

    CGraphic *_G = (CGraphic*)Graphics->GetFirst();
    Graphics->ElementSize = sizeof(CGraphic);
    if (!pict->Width() || !pict->Height()) return 0;
    while (_G && strcmp(_G->Caption, "walking from line graphic"))
    {
        _G = (CGraphic*)_G->GetNext();
    }
    if (!_G)
    {
        _G = (CGraphic*)VirtualAlloc(NULL, sizeof(CGraphic), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
        strcpy(_G->Caption, "walking from line graphic");
        Graphics->Add(_G);
    };
    
    long *x=new long[n];
    long *y=new long[n];
    DWORD i=0,j=0, step=t/20;
    DWORD maxn=0, maxl=0;
    DWORD l=0;
    long double MathExp=0;
    int rnd;
     //initialising starting position
    long *pos0=new long[pict->Height()], posn=0;
    for (i=0;i<pict->Height();i++)
    {
        if (pict->Pixel(i, 0)==1) {pos0[posn]=i,posn++;}
    }
    if (posn==0)
    {
        for (i=0;i<n;i++)
        {
            x[i]=0;
            y[i]=i*posn/p->N;
        }
    }
    else
    {
        for (i=0;i<n;i++)
        {
            x[i]=0;
            //y[i]=pos0[rand()%posn];
			y[i]=pos0[i*posn/p->N];
        }
    }
    //walking
    _G->SetPointsNumber(t+1);
    for (j=0;j<t;j++)
    {
        l=0;
        maxn=0;
        MathExp=0;
        for (i=0;i<n;i++)
        {
			//chosing a direction
			while(1)
			{
				rnd=NewRandom()%3;

				if (rnd==0) 
				{
					if (x[i]<(long)pict->Width()-1 && (posn==0)==(pict->Pixel(y[i],x[i]+1)==0))  
					{
						x[i]++;
						break;
					}
				}
				if(rnd==1)
				{
					if (y[i]<(long)pict->Height()-1 && (posn==0)==(pict->Pixel(y[i]+1,x[i])==0))  
					{
						y[i]++;
						break;
					}
				}
				if (rnd==2)
				{
					if(y[i]>0 && (posn==0)==(pict->Pixel(y[i]-1,x[i])==0)) 
					{
						y[i]--;
						break;
					}
				}
				if ( 
					!(y[i]>0 && (posn==0)==(pict->Pixel(y[i]-1,x[i])==0)) &&
					!(y[i]<(long)pict->Height()-1 && (posn==0)==(pict->Pixel(y[i]+1,x[i])==0)) &&
					!(x[i]<(long)pict->Width()-1 && (posn==0)==(pict->Pixel(y[i],x[i]+1)==0)))
					 break;

			}
            if (l<DWORD(Dist(x[i],y[i]))) l=Dist(x[i],y[i]);
            MathExp+=Dist(x[i],y[i]);
            _G->Points[Dist(x[i],y[i])].Y++;
        }
        for (i=0;i<=l;i++)
        {
            if (_G->Points[i].Y>maxn) {maxn=(DWORD)_G->Points[i].Y;maxl=i;}
            _G->Points[i].Y=0;
        }
        if(j%step==0 || j==t-1)
        {
            MathExp/=(double)n;
            sprintf(buffer,"%s | %10d", tstr, j);
            strcpy(tstr,buffer);
            sprintf(buffer,"%s | %10d", lstr, l);
            strcpy(lstr,buffer);
            sprintf(buffer,"%s | %10d", maxnstr, maxn);
            strcpy(maxnstr,buffer);
            sprintf(buffer,"%s | %10d", maxlstr, maxl);
            strcpy(maxlstr,buffer);
            sprintf(buffer,"%s | %10f", mathexpstr, MathExp);
            strcpy(mathexpstr,buffer);
       }
    }

    #ifdef HIDE_NULL
        l=0;
        for (i=0;i<n;i++)
        {
            if (l<DWORD(Dist(x[i],y[i]))) l=Dist(x[i],y[i]);
        }
    #else
        l=t;
    #endif

    _G->SetPointsNumber(l+1);
    _G->SetQuotientsNumber(0);
    _G->Quotients[0]=0;

    _L->SetPointsNumber(pict->Height()+2);
    _L->Draw=true;
    _L->Type = CLayer::ltPolygon;
    for (i=0;i<pict->Height();i++)
    {
        _L->Points[i+1].X = 0;
        _L->Points[i+1].Y = 0;//i*pict->Height()/SectorNumber;
		counts[i]=0;
    }
    _L->Points[0].X=0;
	_L->Points[0].Y=0;
    _L->Points[pict->Height()+1].X=0;
	_L->Points[pict->Height()+1].Y=pict->Height()-1;
    for (i=0;i<=l;i++)
    {
        _G->Points[i].Y=0;
    }
	LPoints->SetPointsNumber(n);
	

	for (i=0;i<pict->Height();i++)
    {
        _L->Points[i+1].X =0;;
        _L->Points[i+1].Y =i;
    }

    for (i=0;i<n;i++)
    {
		LPoints->Points[i].X=x[i];
		LPoints->Points[i].Y=y[i];

        _G->Points[Dist(x[i],y[i])].Y++;
            _L->Points[y[i]+1].X+=x[i];
            _L->Points[y[i]+1].Y=y[i];
			counts[y[i]]++;
    }

	for (i=0;i<pict->Height();i++)
    {
        _L->Points[i+1].X /= counts[i];
        //_L->Points[i+1].Y /= counts[i];
    }

    for (i=0;i<=l;i++)
    {
        if (_G->Points[i].Y>maxn) {maxn=(DWORD)_G->Points[i].Y;maxl=i;}
        _G->Points[i].X=i;
        MathExp+=_G->Points[i].Y*_G->Points[i].X;
    }
    _G->Quotients[0]=maxn;
    sprintf(buffer,"\n %s\n %s\n %s\n %s\n %s", tstr, lstr, maxnstr, maxlstr, mathexpstr);
    strcat(str,buffer);
 
    delete []x;
    delete []y;
    #undef Dist
	delete counts;
    return _G->Quotients[0];
}