#ifndef _DATA_H_2384623487287
#define _DATA_H_2384623487287
#include "wndws.h"

class TImage                                        //Picture type
{
  private:
    DWORD width, height;                            //width & height of picture
    DWORD length;                                   //lebgth of a row 

  public:
    char *pixels;                                   //variable for array to store data

    TImage(void);                                   //constructor
   ~TImage(void);                                   //destructor

    DWORD Width(void);                              //returns width
    DWORD Height(void);                             //returns height
    int   SetSize(DWORD, DWORD);                    //set width && height
    char  Pixel(DWORD, DWORD);                      //get pixel;
    int   SetPixel(DWORD,DWORD, char);              //set pixel
    char &Byte(DWORD);                              //get link to the byte in pixels-array
};

class TColorImage                                   //Picture type
{
  private:
    DWORD width, height;                            //width & height of picture
    DWORD length;                                   //lebgth of a row
    char Depth;                                     //depth of a picture

  public:
    DWORD *pixels;                                  //array of pixels

    TColorImage(void);                              //constructor
   ~TColorImage(void);                              //destructor

    DWORD Width(void);                              //returns width
    DWORD Height(void);                             //returns height
    int   SetSize(DWORD, DWORD);                    //set width && height
    DWORD Pixel(DWORD, DWORD);                      //get pixel 
    int   SetPixel(DWORD y, DWORD x, DWORD color);            //set pixel   
    char  GetDepth(void);                           //get depth of a picture
    int   SetDepth(char);                           //set depth of a picture
};


struct TSquare                                      //Square type
{
    DWORD X, Y;
    DWORD Width;
};

struct TPoint                                       //Point type
{
    double X, Y;
};

struct TIntPoint                                       //Point type
{
    DWORD X, Y;
};

//string types
typedef char ShortString[80];
typedef char String[256];
typedef char LongString[8192];

#endif  //_DATA_H_2384623487287
