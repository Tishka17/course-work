// Generator.cpp : Defines the entry point for the DLL application.
//

#include "..\..\Common\H\wndws.h"
#include "..\..\Common\H\data.h"
#include "..\..\Common\H\_List.h"
#include "math.h"
#include "..\..\Common\H\Plugins.h"
#include "..\..\Common\H\Graphic.h"
#include "generator.h"

struct KCParam
{
    int it;
};

struct TamplierClusterParam
{
    int L0; //nekii razmer cell
	int W, H; //size
	
};



BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
                     )
{
    return TRUE;
};

void LoadContents(CPlugIn *Plugin)
{
	
	CDataDescription dd[]={{CDataDescription::dtInt,3,8,"Number of iterations"}};
    CDataDescription de[]={{CDataDescription::dtInt,5,1024,"Cell size"},{CDataDescription::dtInt,1,100,"Number of cells along Ox"},{CDataDescription::dtInt,1,100,"Number of cells along Oy"}};

    Plugin->Functions.Clear();

    strcpy(Plugin->Caption, "Generator");
    Plugin->Functions.ElementSize = sizeof(CFunction);

    CFunction *f = (CFunction*)VirtualAlloc(NULL, sizeof(CFunction), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    f->SetAll("GenerateKokh", "Generate Koch Snowflake", CFunction::ftBWSimple);
    Plugin->Functions.Add(f);

    f = (CFunction*)VirtualAlloc(NULL, sizeof(CFunction), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    f->SetAll("GenerateTriangle1", "Generate Triangle Snowflake", CFunction::ftBWSimple);
    Plugin->Functions.Add(f);

    f = (CFunction*)VirtualAlloc(NULL, sizeof(CFunction), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    f->SetAll("GenerateDust", "Generate Kantor's Dust", CFunction::ftBWSimple);
    Plugin->Functions.Add(f);

    f = (CFunction*)VirtualAlloc(NULL, sizeof(CFunction), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    f->SetAll("GenerateDust2", "Generate Modified Kantor's Dust", CFunction::ftBWSimple);
    Plugin->Functions.Add(f);


    f = (CFunction*)VirtualAlloc(NULL, sizeof(CFunction), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    f->SetAll("KantorCluster", "Generate Cluster as Kantor's set", CFunction::ftBWFunction,1,dd);
    Plugin->Functions.Add(f);


	f = (CFunction*)VirtualAlloc(NULL, sizeof(CFunction), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    f->SetAll("TamplierCluster", "Generate Cluster like as Tamplier cross", CFunction::ftBWFunction,3,de);
    Plugin->Functions.Add(f);
//    Plugin->Graphics.Clear();

};

double GenerateKokh(TImage* Pict, CList*, CList *, LongString str, SApproximation*)
{
    int steps = 8;
    Pict->SetSize((DWORD)pow(3,steps-1), (DWORD)pow(3,steps));
    TPoint *a1, *a2, *c;

    a1 = (TPoint*)VirtualAlloc(NULL, sizeof(TPoint)*((DWORD)pow(4,steps)+1), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    a2 = (TPoint*)VirtualAlloc(NULL, sizeof(TPoint)*((DWORD)pow(4,steps)+1), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    int l1, l2;

    a1[0].X=0;
    a1[0].Y=0;
    a1[1].X=Pict->Width()-1; 
    a1[1].Y=0;
    l1=2;

    int i=0;
    int k=0;

    for (int j=0; j<steps; j++)
    {
        i=0;
        k=0;
        l2=l1*4-3;
        while (i<l1)
        {
            a2[k].X=a1[i].X;
            a2[k].Y=a1[i].Y;
            a2[k+4].X=a1[i+1].X;
            a2[k+4].Y=a1[i+1].Y;
      
            a2[k+1].X = (2*a1[i].X +a1[i+1].X )/3;
            a2[k+1].Y = (2*a1[i].Y +a1[i+1].Y )/3;
            a2[k+3].X = (2*a1[i+1].X +a1[i].X )/3;
            a2[k+3].Y = (2*a1[i+1].Y +a1[i].Y )/3;

            a2[k+2].X=(a1[i].X+a1[i+1].X)/2 + (a1[i].Y-a1[i+1].Y)/2/sqrt(3);
            a2[k+2].Y=(a1[i].Y+a1[i+1].Y)/2 + (a1[i+1].X-a1[i].X)/2/sqrt(3);

            i++;
            k+=4;
        }

        c=a2;
        a2=a1;
        a1=c;
        l1=l2;
    }
    for (i=0; i<l1; i++)
    {
        Pict->SetPixel((int)(a1[i].Y),(int)(a1[i].X),1);
    }

    VirtualFree( (void*)a1, sizeof(TPoint)*((DWORD)pow(4,steps)+1), MEM_DECOMMIT); 
    VirtualFree( (void*)a2, sizeof(TPoint)*((DWORD)pow(4,steps)+1), MEM_DECOMMIT); 
    return 0;
};

double GenerateTriangle1(TImage* Pict, CList*, CList *, LongString str, SApproximation*)
{
    int steps = 8;
    Pict->SetSize((DWORD)pow(3,steps), (DWORD)pow(3,steps));
    TPoint *a1, *a2, *c;

    a1 = (TPoint*)VirtualAlloc(NULL, sizeof(TPoint)*((DWORD)pow(5,steps)+1), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    a2 = (TPoint*)VirtualAlloc(NULL, sizeof(TPoint)*((DWORD)pow(5,steps)+1), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

    int l1, l2;

    a1[0].X=0;
    a1[0].Y=0;
    a1[1].X=Pict->Width()-1; 
    a1[1].Y=0;
    l1=2;

    int i=0;
    int k=0;

    for (int j=1; j<steps; j++)
    {
        i=0;
        k=0;
        l2=l1*5-3;
        while (i<l1)
        {
            a2[k].X=a1[i].X;
            a2[k].Y=a1[i].Y;
            a2[k+5].X=a1[i+1].X;
            a2[k+5].Y=a1[i+1].Y;
      
            a2[k+1].X = (2*a1[i].X +a1[i+1].X )/3;
            a2[k+1].Y = (2*a1[i].Y +a1[i+1].Y )/3;
            a2[k+4].X = (2*a1[i+1].X +a1[i].X )/3;
            a2[k+4].Y = (2*a1[i+1].Y +a1[i].Y )/3;
          
            a2[k+2].X= a2[k+1].X + (a2[k+1].Y-a2[k+4].Y);
            a2[k+2].Y= a2[k+1].Y - (a2[k+1].X-a2[k+4].X);
            
            a2[k+3].X= a2[k+4].X + (a2[k+1].Y-a2[k+4].Y);
            a2[k+3].Y= a2[k+4].Y - (a2[k+1].X-a2[k+4].X);            

            i++;
            k+=5;
        }
        c=a2;
        a2=a1;
        a1=c;
        l1=l2;
    }
    for (i=0; i<l1; i++)
    {
        Pict->SetPixel((int)(a1[i].Y),(int)(a1[i].X),1);
    }

    VirtualFree( (void*)a1, sizeof(TPoint)*((DWORD)pow(5,steps)+1), MEM_DECOMMIT); 
    VirtualFree( (void*)a2, sizeof(TPoint)*((DWORD)pow(5,steps)+1), MEM_DECOMMIT); 
    return 0;
};

double GenerateDust(TImage* Pict, CList*, CList *, LongString str, SApproximation*)
{
    int steps = 8;
    Pict->SetSize((DWORD)pow(3,steps-1), (DWORD)pow(3,steps));
    TPoint *a1, *a2, *c;

    a1 = (TPoint*)VirtualAlloc(NULL, sizeof(TPoint)*((DWORD)pow(2,steps)+1), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    a2 = (TPoint*)VirtualAlloc(NULL, sizeof(TPoint)*((DWORD)pow(2,steps)+1), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

    int l1, l2;

    a1[0].X=0;
    a1[0].Y=2;
    a1[1].X=Pict->Width()-1; 
    a1[1].Y=2;
    l1=2;

    int i=0;
    int k=0;

    for (int j=1; j<steps; j++)
    {
        i=0;
        k=0;
        l2=l1*2;
        while (i<l1)
        {
            a2[k].X=a1[i].X;
            a2[k].Y=a1[i].Y;
            a2[k+3].X=a1[i+1].X;
            a2[k+3].Y=a1[i+1].Y;

            a2[k+1].X = (2*a1[i].X +a1[i+1].X )/3;
            a2[k+1].Y = (2*a1[i].Y +a1[i+1].Y )/3;
            a2[k+2].X = (2*a1[i+1].X +a1[i].X )/3;
            a2[k+2].Y = (2*a1[i+1].Y +a1[i].Y )/3;

            i+=2;
            k+=4;
        }
        c=a2;
        a2=a1;
        a1=c;
        l1=l2;
    }
    for (i=0; i<l1; i++)
    {
        Pict->SetPixel((int)(a1[i].Y),(int)(a1[i].X),1);
    }

    VirtualFree( (void*)a1, sizeof(TPoint)*((DWORD)pow(2,steps)+1), MEM_DECOMMIT); 
    VirtualFree( (void*)a2, sizeof(TPoint)*((DWORD)pow(2,steps)+1), MEM_DECOMMIT); 
    return 0;
};

double GenerateDust2(TImage* Pict, CList*, CList *, LongString str, SApproximation*)
{
    int steps = 7;
    Pict->SetSize((DWORD)pow(4,steps-2), (DWORD)pow(4,steps));
    TPoint *a1, *a2, *c;

    a1 = (TPoint*)VirtualAlloc(NULL, sizeof(TPoint)*((DWORD)pow(2,steps)+1), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    a2 = (TPoint*)VirtualAlloc(NULL, sizeof(TPoint)*((DWORD)pow(2,steps)+1), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

    int l1, l2;

    a1[0].X=0;
    a1[0].Y=2;
    a1[1].X=Pict->Width()-1; 
    a1[1].Y=2;
    l1=2;

    int i=0;
    int k=0;

    for (int j=1; j<steps; j++)
    {
        i=0;
        k=0;
        l2=l1*2;
        while (i<l1)
        {
            a2[k].X=a1[i].X;
            a2[k].Y=a1[i].Y;
            a2[k+3].X=a1[i+1].X;
            a2[k+3].Y=a1[i+1].Y;

            a2[k+1].X = (3*a1[i].X +a1[i+1].X )/4;
            a2[k+1].Y = (3*a1[i].Y +a1[i+1].Y )/4;
            a2[k+2].X = (3*a1[i+1].X +a1[i].X )/4;
            a2[k+2].Y = (3*a1[i+1].Y +a1[i].Y )/4;

            i+=2;
            k+=4;
        }
        c=a2;
        a2=a1;
        a1=c;
        l1=l2;
    }
    for (i=0; i<l1; i++)
    {
        Pict->SetPixel((int)(a1[i].Y), (int)(a1[i].X), 1);
    }

    VirtualFree( (void*)a1, sizeof(TPoint)*((DWORD)pow(2,steps)+1), MEM_DECOMMIT); 
    VirtualFree( (void*)a2, sizeof(TPoint)*((DWORD)pow(2,steps)+1), MEM_DECOMMIT); 
    return 0;
};


double KantorCluster(void *param, TImage* Pict, CList*, CList *, LongString str, SApproximation*)
{
	KCParam *p=(KCParam*)param;	
	int i,j,k,size,s;
	size=1;
	for (k=1;k<p->it;k++) size*=3;
	s=1;
	Pict->SetSize(size,size);
	Pict->SetPixel(0,0,1);
	for (k=1;k<p->it;k++)
	{
		for (i=0;i<s;i++)
		for (j=0;j<s;j++)
		{
			Pict->SetPixel(i+2*s,j+s*2,Pict->Pixel(i,j));
			Pict->SetPixel(i,j+s*2,Pict->Pixel(i,j));
			Pict->SetPixel(i+2*s,j,Pict->Pixel(i,j));
		}
		s*=3;
	}
	return 0;
}



double TamplierCluster(void *param, TImage* Pict, CList*, CList *, LongString str, SApproximation*)
{
	TamplierClusterParam *p = (TamplierClusterParam*)param;
	
	
	int i,j,k,t;
	double h0,h1,h2,h3;
	double c0,c1,c2;
	Pict->SetSize(p->H*p->L0,p->W*p->L0);
	
	//Calculation that four cellos :)
	h0=0.1*p->L0/2;
	h1=0.475*h0;
	h2=0.475*h1;
	h3=0.475*h2;
	int L=p->L0;
	
	//coeffs centering
	c0=L/2.0;
	c1=(c0-h1+h0)/2;
	c2=(c1-h2+h1)/2;

	//border of tamplier cross
	for (i=0;i<h0;i++)
	{
		for(j=0;j<L;j++)
		{
			Pict->SetPixel(i,j,1);
			Pict->SetPixel(L-i-1,j,1);
			Pict->SetPixel(j,i,1);
			Pict->SetPixel(j,L-i-1,1);
		};
	};
	//cross
	L/=2;
	for (i=0;i<h1;i++)
	{
		for(j=0;j<p->L0;j++)
		{
			Pict->SetPixel(L-i,j,1);
			Pict->SetPixel(L+i,j,1);
			Pict->SetPixel(j,L-i,1);
			Pict->SetPixel(j,L+i,1);
		};
	};
	//second
	L/=2;
	for (i=0;i<h2;i++)
	{
		for(j=0;j<p->L0;j++)
		{
			Pict->SetPixel(L-i,j,1);
			Pict->SetPixel(L+i,j,1);
			Pict->SetPixel(j,L-i,1);
			Pict->SetPixel(j,L+i,1);

			Pict->SetPixel((p->L0-L)-i,j,1);
			Pict->SetPixel((p->L0-L)+i,j,1);
			Pict->SetPixel(j,(p->L0-L)-i,1);
			Pict->SetPixel(j,(p->L0-L)+i,1);
		};
	};

	//thirth
	L/=2;
	for (i=0;i<h3;i++)
	{
		for(j=0;j<p->L0;j++)
		{
			Pict->SetPixel(L-i,j,1);
			Pict->SetPixel(L+i,j,1);
			Pict->SetPixel(j,L-i,1);
			Pict->SetPixel(j,L+i,1);
			
			Pict->SetPixel((p->L0-L)-i,j,1);
			Pict->SetPixel((p->L0-L)+i,j,1);
			Pict->SetPixel(j,(p->L0-L)-i,1);
			Pict->SetPixel(j,(p->L0-L)+i,1);
			
			Pict->SetPixel(((p->L0/2)+L)-i,j,1);
			Pict->SetPixel(((p->L0/2)+L)+i,j,1);
			Pict->SetPixel(j,((p->L0/2)+L)-i,1);
			Pict->SetPixel(j,((p->L0/2)+L)+i,1);		
			
			Pict->SetPixel(((p->L0/2)-L)-i,j,1);
			Pict->SetPixel(((p->L0/2)-L)+i,j,1);
			Pict->SetPixel(j,((p->L0/2)-L)-i,1);
			Pict->SetPixel(j,((p->L0/2)-L)+i,1);

		};
	};

	//repeating of cell
	if (p->H>1 || p->W>1)
		for (i=0;i<p->H;i++)
			for (j=0;j<p->W;j++)
				for (k=0;k<p->L0;k++)
					for (t=0;t<p->L0;t++)
						Pict->SetPixel(i*p->L0+k, j*p->L0+t, Pict->Pixel(k,t));

	return 0;
}