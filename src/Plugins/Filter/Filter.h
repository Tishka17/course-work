#ifndef __FILTER_H__
#define __FILTER_H__

#define EXPORT extern "C" __declspec (dllexport)

struct CSegment
{
    DWORD x,x2,y,y2;
    
};

//=================================================================================================================
// Function name    : LoadContents
// Description      : Tells about plugins contents to the main program
// Return type      : void 
// Argument         : CPlugIn *
EXPORT void LoadContents(CPlugIn *);

//=================================================================================================================
// Function name    : GetBoundary
// Description      : ...
// Function Type    : fBWSimple
EXPORT fBWSimple GetBoundary;

//=================================================================================================================
// Function name    : InvertColor
// Description      : Color invertion for BW picture (black -> white; white -> black)
// Function Type    : fBWSimple
EXPORT fBWSimple InvertColor;

//=================================================================================================================
// Function name    : Monohromize
// Description      : ...
// Function Type    : fCBWSimple
EXPORT fCBWSimple Monohromize;

//=================================================================================================================
// Function name    : ContrastMonohromize
// Description      : auto contrast and then monohromize
// Function Type    : fCBWSimple
EXPORT fCBWSimple ContrastMonohromize;

//=================================================================================================================
// Function name    : AutoLevels
// Description      : ... 
// Function Type    : fCSimple
EXPORT fCSimple AutoLevels;

//=================================================================================================================
// Function name    : GetSFromHSV
// Description        : RGB to HSV and then sets all bytes as S
// Function Type    : fCSimple
EXPORT fCSimple GetSFromHSV;

//=================================================================================================================
// Function name    : GetVFromHSV
// Description        : RGB to HSV and then sets all bytes as V
// Function Type    : fCSimple
EXPORT fCSimple GetVFromHSV;

//=================================================================================================================
// Function name    : GetHFromHSV
// Description        : RGB to HSV and then sets all bytes as H
// Function Type    : fCSimple
EXPORT fCSimple GetHFromHSV;

//=================================================================================================================
// Function name    : DeNoise
// Description        : Removew noise from BW picture
// Function Type    : fBWSimple
EXPORT fBWSimple DeNoise;

//=================================================================================================================
// Function name    : No Function
// Description      : nothing to do
// Function Type    : void
EXPORT void No();
#endif //__FILTER_H__
