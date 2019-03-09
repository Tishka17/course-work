#if !defined(_READ_DATA_H)
#define _READ_DATA_H 

#define EXPORT extern "C" __declspec (dllexport)

#pragma pack(push, 1)
struct BMP_HEADER
{
    WORD    Sign;           //   sign of BMP-format, 
                            // always equal 0x04D42 
    DWORD   Size;           //   size of the BMP-file
    WORD    Reserved1;      //   reserved 
    WORD    Reserved2;      //   reserved 
    DWORD   Lock;           //   allocation of bitmap data
    DWORD   Header_Length;  //   length of BMP-header,
                            // always equal 0x036 
    DWORD   Width;          //   width of image data (in pixels)
    DWORD   Height;         //   height of image data (in pixels)
    WORD    Num_of_Planes;  //   number of color planes,
                            // always equal 1 
    WORD    Bits_per_Pixel; //   bits per pixel
    DWORD   Compression;    //   method of compression; 
                            // 0 - not compressed, 
                            // 1 -  compressed with RLE-algorythm 
    DWORD   Bitmap_Length;  //   size of bitmap data
    DWORD   HorWidening;    //   horizontal widening 
    DWORD   VerWidening;    //   vertical widening
    DWORD   Num_of_Colors;  //   number of image colors 
    DWORD   MainColNum;     //   number of main image colors 
};
#pragma pack(pop)

#pragma pack(push, 1)
struct RGB_QUAD             //    definition of color-statement in 
                            // BMP-format
{                 
    BYTE    rgbBlue;        //    intensity of blue color
    BYTE    rgbGreen;       //    intensity of green color
    BYTE    rgbRed;         //    intensity of red color
    BYTE    rgbReserved;    //    reserved for alpha-blending
}; 
#pragma pack(pop)


EXPORT int ReadData(const char *File_Name, TColorImage *Image, LongString str); 
//EXPORT int WriteData(const char *File_Name, TImage *Image); 

#endif
