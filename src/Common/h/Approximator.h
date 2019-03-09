#ifndef __APPROXIMATOR_H__
#define __APPROXIMATOR_H__

#include "Graphic.h"

// Function type    : fMinSquare
// Description      : Makes an approximation of points by a polynom 
// Return type      : int 
// Argument         : CGraphic* DataStructure
typedef int (*fApproximator) (CGraphic*);

struct SApproximation
{
   fApproximator APlusBX;
   fApproximator APlusBX2;
   HINSTANCE hInstance;
};

#endif //__APPROXIMATOR_H__