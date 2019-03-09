// Filter.cpp : Defines the entry point for the DLL application.
//

#include "..\..\Common\H\wndws.h"
#include "..\..\Common\H\data.h"
#include "..\..\Common\H\_List.h"
#include "math.h"
#include "..\..\Common\H\Plugins.h"
#include "..\..\Common\H\Graphic.h"
#include "Filter.h"



#define NORM(R,G,B) (DWORD)sqrt(((double)(R*R)+(double)(G*G)+(double)(B*B))/3.)
//#define Norm(R,G,B) ((R+G+B)/3.)

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
                     )
{
    return TRUE;
};



void LoadContents(CPlugIn *Plugin)
{
    Plugin->Functions.Clear();

    strcpy(Plugin->Caption, "Filter");
    Plugin->Functions.ElementSize = sizeof(CFunction);

    CFunction *f = (CFunction*)VirtualAlloc(NULL, sizeof(CFunction), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

    f->SetAll("GetBoundary", "Get Boundary of Picture", CFunction::ftBWSimple);
    Plugin->Functions.Add(f);

    f = (CFunction*)VirtualAlloc(NULL, sizeof(CFunction), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    f->SetAll("InvertColor", "Invert Color in Black && White Picture", CFunction::ftBWSimple);
    Plugin->Functions.Add(f);

    f = (CFunction*)VirtualAlloc(NULL, sizeof(CFunction), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    f->SetAll("DeNoise", "Remove simple noise in Black && White Picture", CFunction::ftBWSimple);
    Plugin->Functions.Add(f);

    f = (CFunction*)VirtualAlloc(NULL, sizeof(CFunction), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    f->SetAll("No", "-", CFunction::ftUnknown);
    Plugin->Functions.Add(f);

    f = (CFunction*)VirtualAlloc(NULL, sizeof(CFunction), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    f->SetAll("Monohromize", "Monohromize picture", CFunction::ftCBWSimple);
    Plugin->Functions.Add(f);

    f = (CFunction*)VirtualAlloc(NULL, sizeof(CFunction), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    f->SetAll("ContrastMonohromize", "AutoContrast and Monohromize picture", CFunction::ftCBWSimple);
    Plugin->Functions.Add(f);

    f = (CFunction*)VirtualAlloc(NULL, sizeof(CFunction), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    f->SetAll("AutoLevels", "Auto Levels", CFunction::ftCBWSimple);
    Plugin->Functions.Add(f);

    f = (CFunction*)VirtualAlloc(NULL, sizeof(CFunction), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    f->SetAll("No", "-", CFunction::ftUnknown);
    Plugin->Functions.Add(f);

    f = (CFunction*)VirtualAlloc(NULL, sizeof(CFunction), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    f->SetAll("GetSFromHSV", "Get picture saturation (RGB to HSV)", CFunction::ftCBWSimple);
    Plugin->Functions.Add(f);
       
    f = (CFunction*)VirtualAlloc(NULL, sizeof(CFunction), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    f->SetAll("GetVFromHSV", "Get picture Value (RGB to HSV)", CFunction::ftCBWSimple);
    Plugin->Functions.Add(f);

    f = (CFunction*)VirtualAlloc(NULL, sizeof(CFunction), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    f->SetAll("GetHFromHSV", "Get picture hue (RGB to HSV)", CFunction::ftCBWSimple);
    Plugin->Functions.Add(f);

//    Plugin->Graphics.Clear();
};

double GetBoundary(TImage* Pict, CList*, CList *, LongString str, SApproximation*)
{
    if (Pict->Height()<5 || Pict->Width()<5) return -1;
    char *t;
    TImage BNewPict;
    TImage *NewPict = &BNewPict;
    NewPict->SetSize(Pict->Height(), Pict->Width());

    DWORD X, Y;
    char CheckedColor = 1;
    char CurPixel;
    for (X=1; X<Pict->Width()-1; X++)
    {
            CurPixel = Pict->Pixel(0, X);
            if (CurPixel == CheckedColor)
            {
                    if ((CurPixel != Pict->Pixel(0, X-1))||
                        (CurPixel != Pict->Pixel(0, X+1))||
                        (CurPixel != Pict->Pixel(0, X)))
                          NewPict->SetPixel(Y, X, CheckedColor);
                    else
                          NewPict->SetPixel(Y, X, 0);
            };

            CurPixel = Pict->Pixel(Pict->Height()-1, X);
            if (CurPixel == CheckedColor)
            {
                    if ((CurPixel != Pict->Pixel(Pict->Height()-1, X-1))||
                        (CurPixel != Pict->Pixel(Pict->Height()-1, X+1))||
                        (CurPixel != Pict->Pixel(Pict->Height()-2, X)))
                          NewPict->SetPixel(Y, X, CheckedColor);
                    else
                          NewPict->SetPixel(Y, X, 0);
            };//
            for (Y=1; Y<Pict->Height()-1; Y++)
            {
                    CurPixel = Pict->Pixel(Y, X);
                    if (CurPixel == CheckedColor)
                    {
                        if ((CurPixel != Pict->Pixel(Y, X-1))||
                            (CurPixel != Pict->Pixel(Y-1, X))||
                            (CurPixel != Pict->Pixel(Y, X+1))||
                            (CurPixel != Pict->Pixel(Y+1, X)))
                                NewPict->SetPixel(Y, X, CheckedColor);
                        else
                              NewPict->SetPixel(Y, X, 0);
                    };
            }; // for Y
     }; // for X

    t = Pict->pixels;
    Pict->pixels = NewPict ->pixels;
    NewPict->pixels = t;
    return 0;
};

double InvertColor(TImage* Pict, CList*, CList *, LongString str, SApproximation*)
{
    if (!Pict->Width() || !Pict->Height()) return -1;
    char *t;
    TImage BNewPict;
    TImage *NewPict = &BNewPict;
    NewPict->SetSize(Pict->Height(), Pict->Width());

    DWORD X, Y;

    for (X = 0; X<Pict->Width(); X++)
    {
        for (Y = 0; Y<Pict->Height(); Y++)
        {
            if (Pict->Pixel(Y, X))
                NewPict->SetPixel(Y, X, 0);
            else
                NewPict->SetPixel(Y, X, 1);
        }
    }
        
    t = Pict->pixels;
    Pict->pixels = NewPict ->pixels;
    NewPict->pixels = t;
    return 0;
}

double Monohromize(TColorImage* ColorPict, TImage* Pict, CList*, CList *, LongString str, SApproximation*)
{
    if (!ColorPict->Width() || !ColorPict->Height()) return -1;
    Pict->SetSize(ColorPict->Height(), ColorPict->Width());

    DWORD R, G, B, Norm;
    for (DWORD X=0; X<ColorPict->Width();X++)
        for (DWORD Y=0; Y<ColorPict->Height();Y++)
        {
                R = (ColorPict->Pixel(Y, X) >> 16) & 0x0FF;
                G = (ColorPict->Pixel(Y, X) >> 8) & 0x0FF;
                B = ColorPict->Pixel(Y, X) & 0x0FF;
                Norm = NORM(R, G, B);
                if ( (BYTE)Norm > 127)
                        Pict->SetPixel(Y, X, 0);
                else
                        Pict->SetPixel(Y, X, 1);
        };
    return 0;
};

double ContrastMonohromize(TColorImage* ColorPict, TImage* Pict, CList*, CList *, LongString str, SApproximation*)
{
    if (!ColorPict->Width() || !ColorPict->Height()) return -1;
    Pict->SetSize(ColorPict->Height(), ColorPict->Width());

    DWORD R, G, B, X, Y, Norm, Min=0xFFFFFFFF, Max=0, d = 0xFFFFFFFF, C;

    for (X=0; X<ColorPict->Width();X++)
        for (Y=0; Y<ColorPict->Height();Y++)
        {
            R = (ColorPict->Pixel(Y, X) >> 16) & 0x0FF;
            G = (ColorPict->Pixel(Y, X) >> 8) & 0x0FF;
            B = ColorPict->Pixel(Y, X) & 0x0FF;
            C = R+G+B;
            if (C>Max) Max=C;
            if (C<Min) Min=C;
        };
    d = Max - Min;
    for (X=0; X<ColorPict->Width();X++)
        for (Y=0; Y<ColorPict->Height();Y++)
        {
                R = (ColorPict->Pixel(Y, X) >> 16) & 0x0FF;
                G = (ColorPict->Pixel(Y, X) >> 8) & 0x0FF;
                B = ColorPict->Pixel(Y, X) & 0x0FF;
                Norm = NORM(R, G, B);//(DWORD)(255*(R + B + G - Min)/d);
                //Norm = (DWORD)sqrt(((double)(R*R)+(double)(G*G)+(double)(B*B))/3.);
                if ( (BYTE)Norm > 127)
                        Pict->SetPixel(Y, X, 0);
                else
                        Pict->SetPixel(Y, X, 1);
        };
    return 0;
};

double AutoLevels(TColorImage* Pict, CList*, CList *, LongString str, SApproximation*)
{
    if (!Pict->Width() || !Pict->Height()) return -1;
    BYTE MaxR=0,   MaxG=0,   MaxB=0;
    BYTE MinR=255, MinG=255, MinB=255;
    BYTE dR  =255, dG  =255,   dB=255;

    DWORD *t;
    TColorImage BNewPict;
    TColorImage *NewPict = &BNewPict;
    NewPict->SetSize(Pict->Height(), Pict->Width());

    DWORD X, Y;
    BYTE R, G, B;
    DWORD C;
    for (X=0; X<Pict->Width();X++)
        for (Y=0; Y<Pict->Height();Y++)
        {
            R = (BYTE)((Pict->Pixel(Y, X) >> 16) & 0x0FF);
            G = (BYTE)((Pict->Pixel(Y, X) >> 8)  & 0x0FF);
            B = (BYTE)( Pict->Pixel(Y, X)        & 0x0FF);
            if (R>MaxR) MaxR=R;
            if (G>MaxG) MaxG=G;
            if (B>MaxB) MaxB=B;
            if (R<MinR) MinR=R;
            if (G<MinG) MinG=G;
            if (B<MinB) MinB=B;
        };

    dR = MaxR - MinR;
    dG = MaxG - MinG;
    dB = MaxB - MinB;

    for (X = 0; X<Pict->Width(); X++)
    {
        for (Y = 0; Y<Pict->Height(); Y++)
        {
            if (MinR == MaxR) R=127;
            else R = (BYTE)(255*((Pict->Pixel(Y, X) >> 16) & 0x0FF - MinR)/dR);
            if (MinG == MaxG) G=127;
            else G = (BYTE)(255*((Pict->Pixel(Y, X) >> 8)  & 0x0FF - MinG)/dG);
            if (MinB == MaxB) B=127;
            else B = (BYTE)(255*( Pict->Pixel(Y, X)        & 0x0FF - MinB)/dB);
            C = (((DWORD)R)<<16) | (((DWORD)G)<<8) | ((DWORD)B);
            NewPict->SetPixel(Y, X, C);            
        }
    }
        
    t = Pict->pixels;
    Pict->pixels = NewPict ->pixels;
    NewPict->pixels = t;
    return 0;
}


double DeNoise(TImage* Pict, CList*, CList *, LongString str, SApproximation*)
{
    if (Pict->Height()<5 || Pict->Width()<5) return -1;
    char *t;
    TImage BNewPict;
    TImage *NewPict = &BNewPict;
    NewPict->SetSize(Pict->Height(), Pict->Width());

    DWORD X, Y;

    for (X = 1; X<Pict->Width()-1; X++)
    {
        for (Y = 1; Y<Pict->Height()-1; Y++)
        {
            if (Pict->Pixel(Y, X))
                if (!Pict->Pixel(Y-1, X) && !Pict->Pixel(Y, X-1) && !Pict->Pixel(Y+1, X) && !Pict->Pixel(Y, X+1))
                NewPict->SetPixel(Y, X, 0);
                else
                    NewPict->SetPixel(Y, X, 1);
            else
                if (Pict->Pixel(Y-1, X) && Pict->Pixel(Y, X-1) && Pict->Pixel(Y+1, X) && Pict->Pixel(Y, X+1))
                NewPict->SetPixel(Y, X, 1);
                else
                    NewPict->SetPixel(Y, X, 0);
        }
    }
        
    t = Pict->pixels;
    Pict->pixels = NewPict ->pixels;
    NewPict->pixels = t;
    return 0;
}

double GetSFromHSV(TColorImage* Pict, CList*, CList *, LongString str, SApproximation*)
{
    float R, G, B, S, V, TEMP;
    BYTE T;
    DWORD X, Y;
/*  R, G, B - остновные цвета (0-1),
    H - цветовой тон (0-360ш), 0ш - красный
    S - насыщенность (0-1)
    V - светлота (0-1)

    MAX - функция определения максимума
    MIN - функция определения минимума*/
    if (!Pict->Width() || !Pict->Height()) return -1;
    for (X=0; X<Pict->Width();X++)
        for (Y=0; Y<Pict->Height();Y++)
        {
            R = (float)(((Pict->Pixel(Y, X) >> 16) & 0x0FF)/256.);
            G = (float)(((Pict->Pixel(Y, X) >> 8)  & 0x0FF)/256.);
            B = (float)(( Pict->Pixel(Y, X)        & 0x0FF)/256.);
            /*Определение светлоты*/
            V=(R>G)?R:G;
            V=(V>B)?V:B;
             /*Определение насыщенности*/
            TEMP=(R<G)?R:G;
            TEMP=(TEMP<B)?V:B;
            if (V==0)  
                S=0 ;
            else 
                S=(V-TEMP)/V;
            T = (BYTE)(256*S);
            Pict->SetPixel(Y, X, (T<<16)| (T<<8) | T);
        };
    return 0;
}

double GetVFromHSV(TColorImage* Pict, CList*, CList *, LongString str, SApproximation*)
{
    float R, G, B, V;
    BYTE T;
    DWORD X, Y;
/*  R, G, B - остновные цвета (0-1),
    H - цветовой тон (0-360ш), 0ш - красный
    S - насыщенность (0-1)
    V - светлота (0-1)

    MAX - функция определения максимума
    MIN - функция определения минимума*/
    if (!Pict->Width() || !Pict->Height()) return -1;
    for (X=0; X<Pict->Width();X++)
        for (Y=0; Y<Pict->Height();Y++)
        {
            R = (float)(((Pict->Pixel(Y, X) >> 16) & 0x0FF)/256.);
            G = (float)(((Pict->Pixel(Y, X) >> 8)  & 0x0FF)/256.);
            B = (float)(( Pict->Pixel(Y, X)        & 0x0FF)/256.);
            /*Определение светлоты*/
            V=(R>G)?R:G;
            V=(V>B)?V:B;
            T = (BYTE)(256*V);
            Pict->SetPixel(Y, X, (T<<16)| (T<<8) | T);
        };
    return 0;
}

double GetHFromHSV(TColorImage* Pict, CList*, CList *, LongString str, SApproximation*)
{
    float R, G, B, H, S, V, TEMP, Cr, Cb, Cg;
    BYTE T;
    DWORD X, Y;
    //    R, G, B - остновные цвета (0-1),
    //    H - цветовой тон (0-360ш), 0ш - красный
    //    S - насыщенность (0-1)
    //    V - светлота (0-1)
    if (!Pict->Width() || !Pict->Height()) return -1;
    for (X=0; X<Pict->Width();X++)
        for (Y=0; Y<Pict->Height();Y++)
        {
            R = (float)(((Pict->Pixel(Y, X) >> 16) & 0x0FF)/256.);
            G = (float)(((Pict->Pixel(Y, X) >> 8)  & 0x0FF)/256.);
            B = (float)(( Pict->Pixel(Y, X)        & 0x0FF)/256.);
            //Определение светлоты
            V=(R>G)?R:G;
            V=(V>B)?V:B;
             //Определение насыщенности
            TEMP=(R<G)?R:G;
            TEMP=(TEMP<B)?V:B;
            if (V==0)  
                S=0 ;
            else 
                S=(V-TEMP)/V;
              //Определение цветового тона

            if (S==0)
                H=360;
            else
            {
                Cr=(V-R)/(V-TEMP);
                Cg=(V-G)/(V-TEMP);
                Cb=(V-B)/(V-TEMP);
                //Цвет между желтым и пурпурным
                if (R==V) 
                    H=Cb-Cg;
                //Цвет между голубым и желтым
                if (G==V) 
                    H=2+Cr-Cb;
               //Цвет между пурпурным и голубым
                if (B==V)
                    H=4+Cg-Cr;
                H=H*60;
                //Приведение к положительным величинам
                if (H<0) 
                    H=H+360;
            }
            T = (BYTE)(256*H/360.);
            Pict->SetPixel(Y, X, (T<<16)| (T<<8) | T);
        };
    return 0;
}
void No()
{
    return;
}