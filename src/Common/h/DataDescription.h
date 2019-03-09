#ifndef __DATA_DESCRIPTION_H__
#define __DATA_DESCRIPTION_H__
#include "wndws.h"

struct CDataDescription//structure with description of data to be entered
{                
    enum cdType{//data types
                 dtUnknown,             //unknown type
                 dtInt,                 //data is integer in [Min,Max]
                 dtDouble,              //data is double in [Min,Max]
                 dtString,              //data is char* with length int [Min,Max]
                 dtBool,                //data is boolean
                 dtCoordinates,         //dta is coordinates of point on the picture
                 dtColor                //data is color
    };
    cdType Type;              //Type of data to be stored
    long double Min, Max;     //special parameters see cdType
    char *Comment;            //comment or description of entered data
};

//=================================================================================================================
// Function name    : StrToVoid
// Description      : Converts string case of data type and stores result in ret. on error returns 0;
// Return type      : bool 
// Argument 1       : char *str
// Argument 2       : CDataDescription *desc
// Argument 3       : void *&ret
bool StrToVoid(char *str, CDataDescription *desc, void *&ret);

//=================================================================================================================
// Function name    : VoidToStr
// Description      : Converts data stored in x to string
// Return type      : void 
// Argument 1       : void*x
// Argument 2       : CDataDescription *desc
// Argument 3       : char *str
void VoidToStr(void*x, CDataDescription *desc, char *str);

//=================================================================================================================
// Function name    : Search
// Description      : searches beginning of field with number n in structure x, depending on data description dd
// Return type      : void *
// Argument 1       : void *x
// Argument 2       : CDataDescription *dd
// Argument 3       : int n
void *Search(void *x, CDataDescription *dd,int n);

//=================================================================================================================
// Function name    : GetSize
// Description      : returns size of parameter number n depending on data description
// Return type      : DWORD
// Argument 1       : CDataDescription *dd
// Argument 2       : int n
DWORD GetSize(CDataDescription *dd,int n);


typedef bool (*FInitGUIInput)     (HINSTANCE, HWND);
typedef bool (*FInitConsoleInput) ();
typedef bool (*FInitFileInput)    ();
typedef bool (*FInput)         (void *x, CDataDescription *dd, DWORD number);
typedef bool (*FFileInput)         (void *x, CDataDescription *dd, DWORD number, char *fname);

#endif __DATA_DESCRIPTION_H__
