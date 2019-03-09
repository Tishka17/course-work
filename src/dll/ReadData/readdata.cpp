// readdata.cpp : Defines the entry point for the DLL application.
//

#include "..\..\Common\H\wndws.h"
#include "..\..\Common\H\data.h"
#include "readdata.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int ReadBMP(const char* File_Name, TColorImage *Image, LongString str)
{
    strcpy(str, "Filename = ");
    strcat(str, File_Name);
    ShortString sw,sh,sd;
    
    BMP_HEADER   *bmp_header = new BMP_HEADER;
	BYTE	     *Line = NULL;
	DWORD        Size_Of_Line;
	DWORD	     Counter1 = 0;
	DWORD	     Counter2;
	RGB_QUAD     *rgb_quad = NULL;
	DWORD        *Palette = NULL;
    HANDLE       File;
    DWORD BytesRead;

	File = CreateFile (File_Name, GENERIC_READ, FILE_SHARE_READ, NULL,
				       OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL|FILE_FLAG_SEQUENTIAL_SCAN, NULL);

    if (!ReadFile(File, bmp_header, sizeof(BMP_HEADER), &BytesRead, NULL))
	{
		if(Image!=NULL) delete Image;
		if(bmp_header!=NULL) delete bmp_header;
		MessageBox(NULL, "Error in file!", "Error", MB_OK);
		return -0x0F;
	};

	if ((bmp_header->Bits_per_Pixel==1)||
		(bmp_header->Bits_per_Pixel==4)||
		(bmp_header->Bits_per_Pixel==8))
			Counter1 = (1 << bmp_header->Bits_per_Pixel);
	
	if ((bmp_header->Bits_per_Pixel!=24)&&(Counter1==0))
	{
        CloseHandle(File);
		if(bmp_header!=NULL) delete bmp_header;
		MessageBox(NULL, "Unknown bitmap depth!", "Error", MB_OK);
		return -0x0E;
	};

	if (Counter1 !=0)
	{
		Size_Of_Line = bmp_header->Width *
			bmp_header->Bits_per_Pixel/8 +
			((bmp_header->Width%(8/bmp_header->Bits_per_Pixel)>0) ? 1:0);
		Size_Of_Line += ((Size_Of_Line%4)>0 ? (4-Size_Of_Line%4):0);
		Palette = new DWORD[Counter1];
		rgb_quad = new RGB_QUAD;
	}
	else
	{
		Size_Of_Line = bmp_header->Width*3 + (4-(bmp_header->Width*3)%4) % 4;
	};

	for (Counter2=0; Counter2 < Counter1; Counter2++)
	{
        ReadFile(File, rgb_quad, 4, &BytesRead, NULL);
		Palette[Counter2] = RGB(rgb_quad->rgbRed, rgb_quad->rgbGreen, rgb_quad->rgbBlue);
	};

    gcvt(bmp_header->Bits_per_Pixel, 6, sd);
    gcvt(bmp_header->Width, 6, sw);
    gcvt(bmp_header->Height, 6, sh);
    strcat(str, "\nWidth = ");
    strcat(str, sw);
    strcat(str, "\nHeight = ");
    strcat(str, sh);
    strcat(str, "\nBit per pixel = ");
    strcat(str, sd);

    Image->SetSize(bmp_header->Height, bmp_header->Width); 

	Line = new BYTE[Size_Of_Line];

	switch(bmp_header->Bits_per_Pixel)
	{
	case 1:
		{
            DWORD  X, Y, Z;

//            NormalizePalette(Palette, 2);
            for(Counter2 = 0; Counter2 < bmp_header->Height; Counter2++)
            {
                    ReadFile(File, Line, Size_Of_Line, &BytesRead, NULL);
                    Y = Counter2;
                    for(Counter1 = 0; Counter1 < bmp_header->Width; Counter1++)
                    {
							X = Counter1;//*8;
                            //for(Bits = 0; Bits<8; Bits++)
                            //{
                            Z = (Line[Counter1/8] & (1 << (7-(Counter1%8)))) >> ((7-(Counter1%8)));
                            Image->SetPixel(Y, X, Palette[Z]); 
                               //     X++;
                            //};
                    };
            };
			break;
		};
	case 4:
		{
			BYTE
					BadBits = (BYTE)(bmp_header->Width % 2);
			DWORD
					WholeBytes = bmp_header->Width/2,
					X, Y, Z;
//			NormalizePalette(Palette, 16);


			for(Counter2 = 0; Counter2 < bmp_header->Height; Counter2++)
        	{
				Y = Counter2;
				if(!ReadFile(File, Line, Size_Of_Line, &BytesRead, NULL))
				{
					MessageBox(NULL, "Error in file-reading", "Error!", MB_OK);
					CloseHandle(File);
					return 0x0F04;
				};
				for(Counter1 = 0; Counter1 < WholeBytes; Counter1++)
				{
					X = Counter1*2;
					Z = Palette[(Line[Counter1] & 240) >> 4];
					Image->SetPixel(Y, X, Z); 
					X++;
					Z = Palette[(Line[Counter1] & 15)];
					Image->SetPixel(Y, X, Z); 
				};
                if(BadBits)
                {
                    X++;
                    Z = Palette[(Line[Counter1] & 240) >> 4];
                    Image->SetPixel(Y, X, Z);
                };
			};
			break;
		};
	case 8:
 		{
            DWORD   X, Y, Z;
//          NormalizePalette(Palette, 256);
			for(Counter2 = 0; Counter2 < bmp_header->Height; Counter2++)
        		{
                Y = Counter2;
				if(!ReadFile(File, Line, Size_Of_Line, &BytesRead, NULL))
				{
					MessageBox(NULL, "Error in file-reading", "Error!", MB_OK);
                    CloseHandle(File);
					return 0x0F04;
				};
				for(Counter1 = 0; Counter1 < bmp_header->Width; Counter1++)
				{
                    X = Counter1;
                    Z = Palette[Line[Counter1]];
                    Image->SetPixel(Y, X, Z);
				};
			};
			break;
		};
	case 24:
		{

			DWORD   Y;
			
			for(Counter2=0; Counter2 < bmp_header->Height; Counter2++)
			{
				if(!ReadFile(File, Line, Size_Of_Line, &BytesRead, NULL))
				{
					MessageBox(NULL, "Error in file-reading", "Error!", MB_OK);
                    CloseHandle(File);
					return 0x0F04;
				};
				Y = Counter2;
			
				for(Counter1=0; Counter1<Size_Of_Line; Counter1+=3)
				{
						Image->SetPixel(Y, Counter1/3,
							RGB(Line[Counter1+2], Line[Counter1 + 1], Line[Counter1]));
				};
			}; 
			break;
		};
	default:
		{
			MessageBox(NULL, "Error!", "Unkown error!", MB_OK);
			return -0x0FFFF;
		};
	};

        CloseHandle(File);
	if(Line!=NULL) delete Line;
	if(bmp_header!=NULL) delete bmp_header;
	if(Palette!=NULL) delete Palette;
	if(rgb_quad!=NULL) delete rgb_quad;
	return 0;
};

int ReadData(const char *File_Name, TColorImage *Image, LongString str)
{
	FILE *Data_File;             // variable of file-type
	WORD *Format_Sign = new WORD;  // sign of format (see types.h)

	if((Data_File = fopen(File_Name, "rb"))==NULL)
	{
		MessageBox(NULL, "File has not opened!", "Error", MB_OK);
		if(Format_Sign!=NULL) delete Format_Sign;
		return -0x0FFFF; // error of file-opening
	};

	if(fread(Format_Sign,2,1,Data_File)==0)
	{
		MessageBox(NULL, "Sign error or error in file!", "Error", MB_OK);
		if(Format_Sign!=NULL) delete Format_Sign;
		return -0x0EEEE; // error in file
	}

	switch (*Format_Sign)
	{ // KNOWN_FORMATS, STANDART_FORMATS etc.
	case 0x04D42:
		{
			fclose(Data_File);
			if(Format_Sign!=NULL) delete Format_Sign;
			return ReadBMP(File_Name, Image, str);
		};
	default: break;
	};
	
	MessageBox(NULL, "Unknown format", "Error", MB_OK);
	if(Format_Sign!=NULL) delete Format_Sign;
	fclose(Data_File);
	return -1;
};

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

