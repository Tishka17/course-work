#ifndef __RandomWalk_H__
#define __RandomWalk_H__

#define EXPORT extern "C" __declspec (dllexport)


//=================================================================================================================
// Function name	: LoadContents
// Description	    : Tells about plugins contents to the main program
// Return type		: void 
// Argument         : CPlugIn *
EXPORT void LoadContents(CPlugIn *);

//=================================================================================================================
// Function name	: GetStatistics
// Description	    : (walking on clear area) Returns number of points which have moved to a certain distance in certain time of random walking
// Function Type    : fBWSimple
EXPORT fBWFunction GetStatistics;

//=================================================================================================================
// Function name	: GetStatisticsOnFractal
// Description	    : (walking on fractal) Returns number of points which have moved to a certain distance in certain time of random walking
// Function Type    : fBWSimple
EXPORT fBWFunction GetStatisticsOnFractal;



EXPORT fBWFunction WalkingLine;

#endif //__RandomWalk_H__