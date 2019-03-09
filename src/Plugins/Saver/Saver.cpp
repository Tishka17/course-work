// Saver.cpp : Defines the entry point for the DLL application.
//

#include "..\..\Common\H\wndws.h"
#include "..\..\Common\H\data.h"
#include "..\..\Common\H\_List.h"
#include "math.h"
#include "stdio.h"
#include "..\..\Common\H\Plugins.h"
#include "..\..\Common\H\Graphic.h"
#include "Saver.h"

struct SaveVGParam
{
    char Path[256];
	double h;
	
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
	
    CDataDescription dd[]={{CDataDescription::dtString,1,256,"Path to svg file for saving"},
	{CDataDescription::dtDouble,0.1,10000,"Height of screen"}};

    Plugin->Functions.Clear();

    strcpy(Plugin->Caption, "Saver");
    Plugin->Functions.ElementSize = sizeof(CFunction);

  	CFunction *f = (CFunction*)VirtualAlloc(NULL, sizeof(CFunction), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    f->SetAll("SaveVisibleGraphics", "Save all visible graphics", CFunction::ftFunction,2,dd);
    Plugin->Functions.Add(f);
	
	SaveVGParam *pp=(SaveVGParam*)f->Parameters;
    strcpy(pp->Path, "graphics.svg");
	pp->h=480;

	f = (CFunction*)VirtualAlloc(NULL, sizeof(CFunction), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    f->SetAll("SaveVisibleLayers", "Save all visible layers", CFunction::ftFunction,2,dd);
    Plugin->Functions.Add(f);
	
	pp=(SaveVGParam*)f->Parameters;
    strcpy(pp->Path, "layers.svg");
	pp->h=480;
};


double SaveVisibleGraphics(void *param, CList *Graphics, CList *, LongString str, SApproximation*)
{
	SaveVGParam *p =(SaveVGParam*)param;

	if (p->h<=0) 
	{
		p->h=600;
	}

	double minx=0, miny=0, maxx=0, maxy=0;
	DWORD i;

	CGraphic *c=(CGraphic*)Graphics->GetFirst();
	
	while (c!=NULL)
	{
		if (c->Draw)
		{
			for (i=0;i<c->PointsNumber;i++)
			{
				if (c->Points[i].X<minx) minx=c->Points[i].X;
				if (c->Points[i].X>maxx) maxx=c->Points[i].X;
				if (c->Points[i].Y<miny) miny=c->Points[i].Y;
				if (c->Points[i].Y>maxy) maxy=c->Points[i].Y;
			}
		}
		c=(CGraphic*)(c->GetNext());
	}


	double w;
	if (minx==maxx && miny!=maxy) 
		maxx=maxy-miny+minx;
	else if (miny==maxy && minx!=maxx) 
		maxy=maxx-minx+miny;
	else if (maxx==minx && maxy==miny)
	{
		maxx+=1;
		maxy+=1;
	}
	w = p->h*(maxx-minx)/(maxy-miny);

	FILE *file;
	file=fopen(p->Path, "w");
	fprintf(file,"<?xml version=\"1.0\" standalone=\"no\"?>\n"
			"<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \n"
			"\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n"
			"<svg width=\"%f\" height=\"%f\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n"
			"<title>Fractals Analyzer. Saver Plugin. Graphics. (Created by Tishka17)</title>\n", w+0.02*w, p->h+0.02*p->h);


	c=(CGraphic*)Graphics->GetFirst();
	fprintf(file,"<g>");
	fprintf(file," <path d=\"M %f %f L %f %f L %f %f\" fill=\"none\" stroke=\"black\" stroke-width=\"1\"/>\n", 
		(float)(((0-minx)/(maxx-minx)+0.01)*w), (float)(p->h-0.99*p->h),
		(float)(((0-minx)/(maxx-minx)+0.01)*w), (float)(p->h+((miny)/(maxy-miny)+0.01)*p->h),
		(float)(((maxx-minx)/(maxx-minx)+0.01)*w), (float)(p->h+((miny)/(maxy-miny)+0.01)*p->h));
	fprintf(file," <path d=\"M %f %f L %f %f L %f %f\" fill=\"none\" stroke=\"black\" stroke-width=\"1\"/>\n", 
		(float)(((maxx-minx)/(maxx-minx)-0.005)*w), (float)(p->h+((miny)/(maxy-miny)+0.02)*p->h),
		(float)(((maxx-minx)/(maxx-minx)+0.01)*w), (float)(p->h+((miny)/(maxy-miny)+0.01)*p->h),
		(float)(((maxx-minx)/(maxx-minx)-0.005)*w), (float)(p->h+((miny)/(maxy-miny)+0.00)*p->h));
	fprintf(file," <path d=\"M %f %f L %f %f L %f %f\" fill=\"none\" stroke=\"black\" stroke-width=\"1\"/>\n", 
		(float)(((0-minx)/(maxx-minx)+0.02)*w), (float)(p->h-(0.975)*p->h),
		(float)(((0-minx)/(maxx-minx)+0.01)*w), (float)(p->h-(0.99)*p->h),
		(float)(((0-minx)/(maxx-minx)-0.00)*w), (float)(p->h-(0.975)*p->h));
	fprintf(file,"</g>\n");
	while (c!=NULL)
	{
		if (c->Draw)
		{
			fprintf(file,"<g>\n");
			for (i=0;i<c->PointsNumber;i++)
			{
					fprintf(file,"<circle cx=\"%f\" cy=\"%f\" r=\"1\" fill=\"blue\" stroke=\"blue\" stroke-width=\"0.1\" />\n", 
						(float)(((c->Points[i].X-minx)/(maxx-minx)+0.01)*w), (float)(p->h-((c->Points[i].Y-miny)/(maxy-miny)-0.01)*p->h));
			}
			fprintf(file,"</g>\n");
		}
		c=(CGraphic*)(c->GetNext());
	}
	sprintf(str, "filename = %s\nminx = %f\nmaxx = %f\nminy = %f\nmaxy = %f,\n screen:%f x %f", p->Path, minx, maxx, miny, maxy, w, p->h);
	
	fprintf(file,"</svg>");
	fclose(file);
	return 0;
}


double SaveVisibleLayers(void *param, CList *Graphics, CList *Layers, LongString str, SApproximation*)
{
	SaveVGParam *p =(SaveVGParam*)param;
	double w;	
	if (p->h<=0) 
	{
		p->h=600;
	}


	double minx=0, miny=0, maxx=0, maxy=0;
	DWORD i;

	CLayer *c=(CLayer*)Layers->GetFirst();
	while (c!=NULL)
	{
		if (c->Draw)
		{
			for (i=0;i<c->PointsNumber;i++)
			{
				if (c->Points[i].X<minx) minx=c->Points[i].X;
				if (c->Points[i].X>maxx) maxx=c->Points[i].X;
				if (c->Points[i].Y<miny) miny=c->Points[i].Y;
				if (c->Points[i].Y>maxy) maxy=c->Points[i].Y;
			}
		}
		c=(CLayer*)(c->GetNext());
	}


	FILE *file;
	file=fopen(p->Path, "w");


	if (minx==maxx && miny!=maxy) 
		maxx=maxy-miny+minx;
	else if (miny==maxy && minx!=maxx) 
		maxy=maxx-minx+miny;
	else if (maxx==minx && maxy==miny)
	{
		maxx+=1;
		maxy+=1;
	}

	w = p->h*(maxx-minx)/(maxy-miny);
	fprintf(file,"<?xml version=\"1.0\" standalone=\"no\"?>\n"
			"<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \n"
			"\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n"
			"<svg width=\"%f\" height=\"%f\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n"
			"<title>Fractals Analyzer. Saver Plugin. Layers. (Created by Tishka17)</title>\n", w+0.02*w, p->h+0.02*p->h);

	c=(CLayer*)Layers->GetFirst();
	while (c!=NULL)
	{
		if (c->Draw)
		{
			if (c->Type == CLayer::ltPoints)
			{
				fprintf(file,"<g>\n");
				for (i=0;i<c->PointsNumber;i++)
				{
					fprintf(file,"<circle cx=\"%f\" cy=\"%f\" r=\"1\" fill=\"blue\" stroke=\"blue\" stroke-width=\"0.1\" />\n", 
						(float)(((c->Points[i].X-minx)/(maxx-minx)+0.01)*w), (float)(p->h-((c->Points[i].Y-miny)/(maxy-miny)-0.01)*p->h));
				}
				fprintf(file,"</g>\n");
			}
			else if (c->Type == CLayer::ltPolygon)
			{
				if (c->PointsNumber>0)
				{
					fprintf(file, "<polygon fill=\"none\" stroke=\"black\" stroke-width=\"1\" points=\"");
					for (i=0;i<c->PointsNumber;i++)
					{
						fprintf(file,"%f,%f ", 
							(float)(((c->Points[i].X-minx)/(maxx-minx)+0.01)*w), (float)(p->h-((c->Points[i].Y-miny)/(maxy-miny)-0.01)*p->h));
					}
					fprintf(file, "\"/>\n");
				}
			}

		}
		c=(CLayer*)(c->GetNext());
	}

	sprintf(str, "filename = %s\nminx = %f\nmaxx = %f\nminy = %f\nmaxy = %f,\n screen:%f x %f", p->Path, minx, maxx, miny, maxy, w, p->h);

	fprintf(file,"</svg>");
	fclose(file);
	return 0;
}