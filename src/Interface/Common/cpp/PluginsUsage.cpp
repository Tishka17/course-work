#ifndef __PLUGINSUSAGE_CPP__
#define __PLUGINSUSAGE_CPP__

#include "..\..\..\Common\H\plugins.h"
#include "..\..\..\Common\H\Approximator.h"
#include "..\H\PluginsUsage.h"
#include "..\H\LogFile.h"
#include "..\H\Variables.h"
//=================================================================================================================
// Function name    : LoadFunctions
// Description      : Loads functions, which names are already stored in Plugin structure
// Return type      : bool 
// Argument         : CPlugIn *Plugin
bool LoadFunctions(CPlugIn *Plugin)
{
    Plugin->Functions.Current = Plugin->Functions.GetFirst();
    while (Plugin->Functions.Current)
    {
        ((CFunction*)Plugin->Functions.Current)->Adress = ::GetProcAddress(Plugin->hInstance, ((CFunction*)Plugin->Functions.Current)->Name);
        if (!((CFunction*)Plugin->Functions.Current)->Adress) 
        {
            char s[1000];
            strcpy(s, "Function ");
            strcat(s, ((CFunction*)Plugin->Functions.Current)->Name);
            strcat(s, " not found in ");
            strcat(s, Plugin->Name);
            WriteLogError(s);
            Plugin->Functions.Delete(Plugin->Functions.Current);
        };
        if (!Plugin->Functions.Current) Plugin->Functions.Current=Plugin->Functions.GetFirst();
        else Plugin->Functions.Current = Plugin->Functions.Current->GetNext();
    }
    return true;
};

//=================================================================================================================
// Function name    : LoadPlugin
// Description      : Load's a plugin(which is a dll), which name is already stores in Plugin->Name.
// Return type      : bool 
// Argument 1       : CPlugIn *Plugin
// Argument 2       : DWORD &FirstWM
bool LoadPlugin(CPlugIn *Plugin, DWORD &FirstWM)
{
    Plugin->hInstance = LoadLibrary(Plugin->Name);
    char s[MAX_PATH], *sl;
    strcpy(s, Plugin->Name);
    sl = strrchr(s, '\\');
    strcpy(Plugin->Name, sl+1);
    if (!Plugin->hInstance) 
    {
        char s[1000];
        strcpy(s, "Cannot load  ");
        strcat(s, Plugin->Name);
        WriteLogError(s);
        return false;
        return false;
    }
    fLoadContents *Load = (fLoadContents*) :: GetProcAddress(Plugin->hInstance, "LoadContents");
    if (!Load) 
    {
        Load = (fLoadContents*) :: GetProcAddress(Plugin->hInstance, "_LoadContents");
        if (!Load) 
        {
            FreeLibrary(Plugin->hInstance);  
            char s[1000];
            strcpy(s, "No contents function found in ");
            strcat(s, Plugin->Name);
            WriteLogError(s);
            return false;
        };
    };
    Load(Plugin);
    if (!LoadFunctions(Plugin) || !Plugin->Functions.GetNumber())
    {
        FreeLibrary(Plugin->hInstance);  
        char s[1000];
        strcpy(s, "No functions found in ");
        strcat(s, Plugin->Name);
        WriteLogError(s);
        return false;
    };
    Plugin->FirstWM = FirstWM;
    FirstWM+= Plugin->Functions.GetNumber();
    Plugin->LastWM = FirstWM-1;
    return true;
};
//===============
bool NeedParams(CFunction::cfType type)
{
	if (type<CFunction::ftFunction) return false;
	return true;
}

//=================================================================================================================
// Function name    : FreePlugins
// Description      : Frees all instances of all loaded plugins
// Return type      : bool 
// Argument         : CPlugIn *First
bool FreePlugins(CPlugIn *First)
{
    CPlugIn *p = First;
    while(p)
    {
        FreeLibrary(p->hInstance);
        p = (CPlugIn*)p->GetNext();
    }
    return true;
}

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
double ExecuteFunction(CFunction *f, CPlugIn *p, LongString ReturnStr, SApproximation *Approximation, TImage *Picture, TColorImage *ColorPicture, CList *Graphics, CList *Layers, void* InputFunc, bool input, char *DataFileName)
{
    //without parameters
    if (f->Type == CFunction::ftSimple)//Simple function
    {
        return ((fSimple*)f->Adress)(Graphics, Layers, ReturnStr, Approximation);
    }
    else if (f->Type == CFunction::ftBWSimple)//Black & White Filter
    {
        return ((fBWSimple*)f->Adress)(Picture, Graphics, Layers, ReturnStr, Approximation);
    }
    else if (f->Type == CFunction::ftCSimple)//Color Filter
    {
        return ((fCSimple*)f->Adress)(ColorPicture, Graphics, Layers, ReturnStr, Approximation);
    }
    else if (f->Type == CFunction::ftCBWSimple)//Color nad Black & White Filter
    {
        return ((fCBWSimple*)f->Adress)(ColorPicture, Picture, Graphics, Layers, ReturnStr, Approximation);
    }
    //with parameters
    else if (f->Type == CFunction::ftFunction)//function with parameters
    {
        if (InputFunc!=NULL && input)
			if (DataFileName)
				((FFileInput)InputFunc)(f->Parameters, f->ParametersDescription, f->ParametersNumber, DataFileName);
			else ((FInput)InputFunc)(f->Parameters, f->ParametersDescription, f->ParametersNumber);
        else return ((fFunction*)f->Adress)((fFunction*)f->Parameters, Graphics, Layers, ReturnStr, Approximation);
    }
    else if (f->Type == CFunction::ftBWFunction)//Black & White Filter
    {
        if (InputFunc!=NULL && input)
		{
			if (DataFileName)
				((FFileInput)InputFunc)(f->Parameters, f->ParametersDescription, f->ParametersNumber, DataFileName);
			else ((FInput)InputFunc)(f->Parameters, f->ParametersDescription, f->ParametersNumber);
			return 0;
		}
        else return ((fBWFunction*)f->Adress)((fFunction*)f->Parameters,Picture, Graphics, Layers, ReturnStr, Approximation);
    }
    else if (f->Type == CFunction::ftCFunction)//Color Filter
    {
        if (InputFunc!=NULL && input)
			if (DataFileName)
				((FFileInput)InputFunc)(f->Parameters, f->ParametersDescription, f->ParametersNumber, DataFileName);
			else ((FInput)InputFunc)(f->Parameters, f->ParametersDescription, f->ParametersNumber);
        else return ((fCFunction*)f->Adress)((fFunction*)f->Parameters,ColorPicture, Graphics, Layers, ReturnStr, Approximation);
    }
    else if (f->Type == CFunction::ftCBWFunction)//Color nad Black & White Filter
    {
        if (InputFunc!=NULL && input)
			if (DataFileName)
				((FFileInput)InputFunc)(f->Parameters, f->ParametersDescription, f->ParametersNumber, DataFileName);
			else ((FInput)InputFunc)(f->Parameters, f->ParametersDescription, f->ParametersNumber);
        else return ((fCBWFunction*)f->Adress)((fFunction*)f->Parameters,ColorPicture, Picture, Graphics, Layers, ReturnStr, Approximation);
    }
    
    return 0;
}

//=================================================================================================================
// Function name    : RunFunctionByCM
// Description      : Finds and executes function according windows message
// Return type      : bool 
// Argument 1       : DWORD CMessage
// Argument 2       : CPlugIn *First
bool RunFunctionByCM(DWORD CMessage, CPlugIn *First, SApproximation *Approximation, TImage *Picture, TColorImage *ColorPicture, CList *Graphics, CList *Layers, FInput InputFunc, bool input)
{

    if (CMessage<CM_PLUGINS_FIRST_METHOD || CMessage>CM_PLUGINS_LAST_METHOD) return false;
    CPlugIn *p = First;
    CFunction *f;
    int i=0;
    while (p)
    {
        if (p->FirstWM<=CMessage && p->LastWM>=CMessage)
        {
            i = 0;
            f = (CFunction*)p->Functions.GetFirst();
            while (f)
            {
                if (i+p->FirstWM == CMessage)
                {
                    LongString str="";
                    LPSYSTEMTIME Time1 = new _SYSTEMTIME;
                    LPSYSTEMTIME Time2 = new _SYSTEMTIME;
                    

                    GetLocalTime(Time1);
                    f->Result = ExecuteFunction(f, p, str, Approximation, Picture, ColorPicture, Graphics, Layers, InputFunc, input);
                    if (input && NeedParams(f->Type)) return true;
                    GetLocalTime(Time2);

                    OpenLog();
                    WriteLogFunctionCall(p->Name, f->Name);
                    WriteLogFunctionCallTime(Time1, Time2);
                    WriteLog(f->Result);
                    WriteLogFunctionCallEnd();
                    WriteLogFunctionString(str);
                    CloseLog();
                    return true;
                }
                f = (CFunction*)f->GetNext();
                i++;
            }
        }
        p = (CPlugIn*)p->GetNext();
    }
    return false;
}

//=================================================================================================================
// Function name    : RunFunctionByCM
// Description      : Finds and executes function according to name of plugin and function name
// Return type      : bool 
// Argument 1       : char *c
// Argument 2       : char *b2
// Argument 3       : CPlugIn *First

bool RunFunctionByName(char *c, char *b2, CPlugIn *First, SApproximation *Approximation, TImage *Picture, TColorImage *ColorPicture, CList *Graphics, CList *Layers, void* InputFunc, bool input, char*DataFileName)
{
    LongString str="";
    CPlugIn *p = First;
    CFunction *f;
    while (p)
    {
        if (!strcmp(p->Name, c))
        {
            f = (CFunction*)p->Functions.GetFirst();
            while (f)
            {
                if (!strcmp(f->Name, b2))
                {
                    
                    LPSYSTEMTIME Time1 = new _SYSTEMTIME;
                    LPSYSTEMTIME Time2 = new _SYSTEMTIME;

                    GetLocalTime(Time1);
                    if (input && NeedParams(f->Type)) 
					{
						f->Result = ExecuteFunction(f, p, str, Approximation, Picture, ColorPicture, Graphics, Layers, InputFunc,true,DataFileName);
						return true;
					}
					else if (!input) f->Result = ExecuteFunction(f, p, str, Approximation, Picture, ColorPicture, Graphics, Layers);
					else return true;
                    GetLocalTime(Time2);

                    OpenLog();
                    WriteLogFunctionCall(p->Name, f->Name);
                    WriteLogFunctionCallTime(Time1, Time2);
                    WriteLog(f->Result);
                    WriteLogFunctionCallEnd();
                    WriteLogFunctionString(str);
                    CloseLog();
                    return true;
                }
                f = (CFunction*)f->GetNext();
            }
        }
        p = (CPlugIn*)p->GetNext();
    }
    return false;
}

#endif //__PLUGINSUSAGE_CPP__
