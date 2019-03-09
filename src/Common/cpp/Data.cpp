#ifndef _DATA_CPP
#define _DATA_CPP

#include "..\H\data.h"
//#include <WindowsX.h>
#include "..\H\wndws.h"

//TImage
TImage::TImage()                                                //constructor
{                                                               //in the beginning picture is empty
    width = 0;            
    height = 0;
    pixels = NULL;
    length=0;                                                   //length of a row
};

TImage::~TImage()                                               //destructor
{
    if(pixels != NULL) 
    {
            VirtualFree( (void*)pixels, length * height, MEM_DECOMMIT);//clear memory if it is assigned for array
    }

    width = 0;                                                  //empty picture
    height = 0;
    pixels = NULL;
    length=0;
};
               
DWORD TImage::Width()
{
    return width;
}

DWORD TImage::Height()
{
    return height;
}

int TImage::SetSize(DWORD _y, DWORD _x)                         //set size and allocate memory
{
    width = _x;
    height = _y;
    length= _x / 8 + ((_x%8==0) ? 0:1);                         //length == number of bytes allocated for 1 row

    if (pixels != NULL)
    {
        VirtualFree( (void*)pixels, length * _y, MEM_DECOMMIT); //if memory is allocated - free it;
    }                                                         
    //pixels = new char[length * _y];                           //allocate memory for array
    pixels = (char*)VirtualAlloc(NULL, length * _y, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    for (DWORD i=0;i<length * _y;i++)
    {
        pixels[i]=0;                                            //all pixels are white (empty)
    }
    return 0;
};

char TImage::Pixel(                                             //get pixel 
                    DWORD _y,                                   // row [from 0 to height-1]              
                    DWORD _x)                                   // column [from 0 to width-1] 
{                                                          
    if (_x<width && _y<height)
    {
        return ((*(pixels + _y*length + _x/8) & (1<<(_x%8)))>>(_x%8));//return color
    }
    else return 2;                                              //error
};

int TImage::SetPixel(
                     DWORD _y,                                  // row [from 0 to height-1]
                     DWORD _x,                                  // column [from 0 to width-1] 
                     char _color)                               //color ( 0 -white, 1 - black)
{
    if (_x>=width || _y>=height) return 1;
    if  (_color)
    {
         *(pixels + _y*length + _x/8) |= 1<<(_x%8);             //set black pixel  (set bit)
    }
    else
    {
         *(pixels + _y*length + _x/8) &= 255-(1<<(_x%8));       //set white pixele (reset bit)
    };
    return 0;
};


char& TImage::Byte(DWORD i)
{
    return pixels[i];
};

//===================================================================================================================
//TColorImage
TColorImage::TColorImage()                                      //constructor
{                                                               //in the beginning picture is empty
    width = 0;            
    height = 0;
    pixels = NULL;
    length=0;                                                   //lebgth of a row
};

TColorImage::~TColorImage()                                     //destructor
{
    if(pixels != NULL) 
    {
            VirtualFree( (void*)pixels, length * height, MEM_DECOMMIT);//clear memory if it is assigned for array
    }

    width = 0;                                                  //empty picture
    height = 0;
    pixels = NULL;
    length=0;
};
               
DWORD TColorImage::Width()
{
    return width;
}

DWORD TColorImage::Height()
{
    return height;
}

int TColorImage::SetSize(DWORD _y, DWORD _x)                    //set size and allocate memory
{
    width = _x;
    height = _y;
    length= _x * sizeof(DWORD);                                  //length == number of bytes allocated for 1 row

    if (pixels != NULL)
    {
        VirtualFree( (void*)pixels, length * _y, MEM_DECOMMIT); //if memory is allocated - free it;
    }                                                         
    //pixels = new char[length * _y];                           //allocate memory for array
    pixels = (DWORD*)VirtualAlloc(NULL, length * _y, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    for (DWORD i=0;i<_x * _y;i++)
    {
        pixels[i]=0;                                            //all pixels are white (empty)
    }
    return 0;
};

DWORD TColorImage::Pixel(                                        //get pixel 
                    DWORD _y,                                   // row [from 0 to height-1]              
                    DWORD _x)                                   // column [from 0 to width-1] 
{                                                          
    return pixels[_y*width+_x];
};

int TColorImage::SetPixel(
                     DWORD _y,                                  // row [from 0 to height-1]
                     DWORD _x,                                  // column [from 0 to width-1] 
                     DWORD _color)                               //
{
    if (_x>=width || _y>=height) return 1;                      //error there is no such pixel in picture
    pixels[_y*width + _x]= _color;
    return 0;
};
 
int TColorImage::SetDepth(char _depth)                          // column [from 0 to width-1] 
{                                                          
    Depth = _depth;
    return 0;
};

char TColorImage::GetDepth(void)         
{   
    return Depth;
};

#endif //_DATA_CPP
