#ifndef __Saver_H__
#define __Saver_H__

#define EXPORT extern "C" __declspec (dllexport)

struct CSegment
{
    DWORD x,x2,y,y2;
    
};

//=================================================================================================================
// Function name    : LoadContents
// Description        : Tells about plugins contents to the main program
// Return type        : void 
// Argument         : CPlugIn *
EXPORT void LoadContents(CPlugIn *);

EXPORT fFunction SaveVisibleGraphics;
EXPORT fFunction SaveVisibleLayers;
#endif //__Saver_H__
