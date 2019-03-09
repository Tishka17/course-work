#if !defined(_MINK_H)
#define _MINK_H

#define EXPORT extern "C" __declspec (dllexport)

#include "..\..\Common\H\data.h"

//=================================================================================================================
// Function name    : LoadContents
// Description        : Tells about plugins contents to the main program
// Return type        : void 
// Argument         : CPlugIn *
EXPORT void LoadContents(CPlugIn *);

//=================================================================================================================
// Function name    : Minkovsky
// Description        : Calculates Minkovsky dimension using NULL method.
// Function Type    : fDimCalc
EXPORT fBWSimple Minkovsky;

//=================================================================================================================
// Function name    : Minkovsky1
// Description        : Calculates Minkovsky dimension using modified NULL method
// Function Type    : fDimCalc
EXPORT fBWSimple Minkovsky1;

//=================================================================================================================
// Function name    : Hausdorf
// Description        : Calculates Hausdorf dimension using data from Minkovsky method.
// Function Type    : fDimCalc
EXPORT fBWSimple Hausdorf;

//=================================================================================================================
// Function name    : Hausdorf1
// Description        : Calculates Hausdorf dimension using data from Minkovsky1 method
// Function Type    : fDimCalc
EXPORT fBWSimple Hausdorf1;

//=================================================================================================================
// Function name    : CountNull
// Description        : Counts squares with parts of fractal inside. Uses NULL method.
// Return type        : DWORD 
// Argument 1       : TImage &pict
// Argument 2       : DWORD size
DWORD CountNull(TImage &pict, DWORD size);

//=================================================================================================================
// Function name    : CountTishka
// Description        : Counts squares with parts of fractal inside. Uses modified NULL method.
// Return type        : DWORD 
// Argument 1       : TImage &pict
// Argument 2       : DWORD size
DWORD CountTishka(TImage &pict, DWORD size);

#endif
