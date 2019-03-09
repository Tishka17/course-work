#ifndef __FUNCTIONS_CPP__
#define __FUNCTIONS_CPP__

#include "..\H\DataDescription.h"//parameters of functions
#include "..\H\Plugins.h"

#include <string.h>

CFunction::SetAll(ShortString name, ShortString caption, cfType type, DWORD number, CDataDescription *desc)
{
    strcpy(Name, name);
    strcpy(Caption, caption);
    Type = type;
    Result = 0;
    if (desc == NULL || number<=0) 
    {
        ParametersNumber = 0;
        ParametersDescription = NULL;
        Parameters = NULL;
    }
    else 
    {
        ParametersNumber = number;
        ParametersDescription = (CDataDescription*) VirtualAlloc(NULL, (number) * sizeof(CDataDescription), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
        Parameters = VirtualAlloc(NULL, GetSize(desc, number), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
        ZeroMemory(Parameters,GetSize(desc, number)); 
    }
    for (DWORD i=0;i<ParametersNumber;i++) 
    {
        ParametersDescription[i].Type = desc[i].Type;
        ParametersDescription[i].Min = desc[i].Min;
        ParametersDescription[i].Max = desc[i].Max;
        ParametersDescription[i].Comment = (char*) VirtualAlloc(NULL, strlen(desc[i].Comment), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
        strcpy(ParametersDescription[i].Comment, desc[i].Comment);
    }
}

CFunction::~CFunction()
{
    for (DWORD i=0;i<ParametersNumber;i++) 
    {
        VirtualFree((void*)ParametersDescription[i].Comment, strlen(ParametersDescription[i].Comment), MEM_DECOMMIT); 
    }
    if (ParametersNumber>0) 
    {
        VirtualFree((void*)ParametersDescription, (ParametersNumber) * sizeof(CDataDescription), MEM_DECOMMIT); 
        VirtualFree(Parameters, GetSize(ParametersDescription, ParametersNumber), MEM_DECOMMIT); 
    }
}

//===============================================================================================================
CPlugIn::CPlugIn():CListItem()
{
    Name[0]=0;
    Caption[0] = 0;

}


#endif //__FUNCTIONS_CPP__
