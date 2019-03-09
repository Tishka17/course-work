#ifndef __TYPES_H__
#define __TYPES_H__

#include "_LIST.h"//lists and dynamic arrays
#include "DataDescription.h"//parameters of functions
#include "data.h"
#include "Approximator.h"

//class, which contains function description
class CFunction:public CListItem
{
    protected:
    public:
        enum cfType{ //constants to declare type of function
                      ftUnknown,//Unknown function type
                      //without parameters
                      ftBWSimple,
                      ftCSimple,
                      ftCBWSimple,
                      ftSimple,
                      //with parameters
                      ftFunction,
                      ftBWFunction,
                      ftCFunction,
                      ftCBWFunction,
                    };

        ShortString   Name;//name of function as it called while writing programm/unit
        ShortString   Caption;//caption as it should be called in user's menu

        void         *Adress;//pointer
        cfType        Type;//type of function, available one of constants above
        double        Result;//result returned by function after last call

        DWORD             ParametersNumber;//Number of parameters which are used by function
        CDataDescription *ParametersDescription;//array of description of parameters used in function
        void             *Parameters;

        SetAll(ShortString name="", ShortString caption="", cfType type=CFunction::ftUnknown, DWORD=0, CDataDescription *desc=NULL);//constructor
       ~CFunction();//destructor

};

class CPlugIn:public CListItem
{
    protected:
    public:
        CPlugIn();
        ShortString   Caption;
        String        Name;

        CList         Functions;
        //CList         Graphics;
        HINSTANCE     hInstance;  
        HMENU         hMenu;
        DWORD         FirstWM;
        DWORD         LastWM;
};

//this function must be in every plugin:

// Function type name: LoadContents
// Description       : Loads contents of plugin
// Return type       : void 
// Argument          : CPlugIn *Plugin
typedef void (fLoadContents) (CPlugIn *);

//different function types:

// Function type name: fSimple
// Description       : Makes Changes in Black & White Picture
// Return type       : double 
// Argument 1        : TList* Graphics
// Argument 2        : LongString ReturnString
// Argument 3        : SApproximation* ApproximationMethodsStructure
typedef double (fSimple) (CList*, CList *, LongString ReturnString, SApproximation*a=NULL);

// Function type name: fBWFilter
// Description       : Makes Changes in Black & White Picture
// Return type       : double 
// Argument 1        : TImage* Picture
// Argument 2        : TList* Graphics
// Argument 3        : SApproximation* ApproximationMethodsStructure
typedef double (fBWSimple) (TImage*, CList *, CList*, LongString str, SApproximation*a=NULL);

// Function type name: fCFilter
// Description       : Makes Changes in Color Picture
// Return type       : double 
// Argument 1        : TImage* Picture
// Argument 2        : TList* Graphics
// Argument 3        : SApproximation* ApproximationMethodsStructure
typedef double (fCSimple) (TColorImage*, CList *, CList*, LongString str, SApproximation*a=NULL);

// Function type name: fCBWFilter
// Description       : Makes Changes in Color or/and Black & White Picture
// Return type       : double 
// Argument 1        : TColorImage*
// Argument 2        : TImage*
// Argument 3        : CList*
// Argument 4        : SApproximation*
typedef double (fCBWSimple) (TColorImage*, TImage*, CList *, CList*, LongString str, SApproximation*a=NULL);

// Function type name: fSimple
// Description       : Makes Changes in Black & White Picture
// Return type       : double 
// Argument 1        : void *Parameters
// Argument 2        : TList* Graphics
// Argument 3        : TList* Layers
// Argument 4        : LongString ReturnString
// Argument 5        : SApproximation* ApproximationMethodsStructure
typedef double (fFunction) (void *Parameters, CList *Graphics, CList*Layers, LongString ReturnString, SApproximation*a=NULL);

// Function type name: fBWFilter
// Description       : Makes Changes in Black & White Picture
// Return type       : double 
// Argument 1        : void *Parameters
// Argument 2        : TImage* Picture
// Argument 3        : TList* Graphics
// Argument 4        : SApproximation* ApproximationMethodsStructure
typedef double (fBWFunction) (void *Parameters, TImage*, CList *, CList*Layers, LongString str, SApproximation*a=NULL);

// Function type name: fCFilter
// Description       : Makes Changes in Color Picture
// Return type       : double 
// Argument 1        : void *Parameters
// Argument 2        : TImage* Picture
// Argument 3        : TList* Graphics
// Argument 4        : SApproximation* ApproximationMethodsStructure
typedef double (fCFunction) (void *Parameters, TColorImage*, CList *, CList*, LongString str, SApproximation*a=NULL);

// Function name     : fCBWFilter
// Description       : Makes Changes in Color or/and Black & White Picture
// Return type       : double 
// Argument 1        : void *Parameters
// Argument 2        : TColorImage*
// Argument 3        : TImage*
// Argument 4        : CList*
// Argument 5        : SApproximation*
typedef double (fCBWFunction) (void *Parameters, TColorImage*, TImage*, CList *, CList*, LongString str, SApproximation*a=NULL);

#endif //__TYPES_H__
