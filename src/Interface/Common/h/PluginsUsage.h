#ifndef __PLUGINSUSAGE_H__
#define __PLUGINSUSAGE_H__

#include "..\..\..\Common\H\plugins.h"
//=================================================================================================================
// Function name    : LoadFunctions
// Description      : Loads functions, which names are already stored in Plugin structure
// Return type      : bool 
// Argument         : CPlugIn *Plugin
bool LoadFunctions(CPlugIn *Plugin);

//=================================================================================================================
// Function name    : LoadPlugin
// Description      : Load's a plugin(which is a dll), which name is already stores in Plugin->Name.
// Return type      : bool 
// Argument 1       : CPlugIn *Plugin
// Argument 2       : DWORD &FirstWM
bool LoadPlugin(CPlugIn *Plugin, DWORD &FirstWM);

//=================================================================================================================
// Function name    : FreePlugins
// Description      : Frees all instances of all loaded plugins
// Return type      : bool 
// Argument         : CPlugIn *First
bool FreePlugins(CPlugIn *First);

//=================================================================================================================
// Function name    : ExecuteFunction
// Description      : Execute function according its type
// Return type      : double 
// Argument 1       : CFunction *f
// Argument 2       : CPlugIn *p
// Argument 3       : LongString ReturnStr
// Argument 4       : SApproximation *Approximation
// Argument 5       : TImage *Picture
// Argument 6       : TColorImage *ColorPicture
double ExecuteFunction(CFunction *f, CPlugIn *p, LongString ReturnStr, SApproximation *Approximation, TImage *Picture, TColorImage *ColorPicture, CList *Graphics, CList *Layers, void* InputFunc=NULL, bool=false, char *DataFileName=NULL);

//=================================================================================================================
// Function name    : RunFunctionByCM
// Description      : Finds and executes function according windows message
// Return type      : bool 
// Argument 1       : DWORD CMessage
// Argument 2       : CPlugIn *First
bool RunFunctionByCM(DWORD CMessage, CPlugIn *First, SApproximation *Approximation, TImage *Picture, TColorImage *ColorPicture, CList *Graphics, CList *Layers, FInput InputFunc=NULL, bool input=false);

//=================================================================================================================
// Function name    : RunFunctionByCM
// Description      : Finds and executes function according to name of plugin and function name
// Return type      : bool 
// Argument 1       : char *c
// Argument 2       : char *b2
// Argument 3       : CPlugIn *First
bool RunFunctionByName(char *c, char *b2, CPlugIn *First, SApproximation *Approximation, TImage *Picture, TColorImage *ColorPicture, CList *Graphics, CList *Layers, void* InputFunc=NULL, bool=false, char *DataFileName=NULL);

#endif //__PLUGINSUSAGE_H__