#ifndef __GENERATOR_H__
#define __GENERATOR_H__

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

//=================================================================================================================
// Function name    : GenerateKokh
// Description        : Generates Kokh's Snowflake
// Function Type    : fBWSimple
EXPORT fBWSimple GenerateKokh;

//=================================================================================================================
// Function name    : GenerateTriangle1
// Description        : Generates Triangle1 which is Kokh's Snowflake
// Function Type    : fBWSimple
EXPORT fBWSimple GenerateTriangle1;

//=================================================================================================================
// Function name    : GenerateDust
// Description        : Generates Kantor's Dust
// Function Type    : fBWSimple
EXPORT fBWSimple GenerateDust;

//=================================================================================================================
// Function name    : GenerateDust2
// Description        : Generates modification of Kantor's Dust
// Function Type    : fBWSimple
EXPORT fBWSimple GenerateDust2;

//=================================================================================================================
// Function name    : KantorCluster
// Description      : Generates cluster as modification of Kantor's Dust (2 dimensional)
// Function Type    : fBWFunction
EXPORT fBWFunction KantorCluster;

EXPORT fBWFunction TamplierCluster;
#endif //__GENERATOR_H__
