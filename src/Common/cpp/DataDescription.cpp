#ifndef __DATA_DESCRIPTION_CPP__
#define __DATA_DESCRIPTION_CPP__

#include "stdlib.h"
#include "stdio.h"
#include "..\H\DataDescription.h"

//convertation of string to void* data
//on error returns 0, on succes returns 1
bool StrToVoid(char *str, CDataDescription *desc, void *&ret)
{
    char *ch=NULL;
    switch (desc->Type)
    {
        case CDataDescription::dtInt:
        {
            int x;
            if (str[0] == 0) return 0;
            for (ch=str;*ch!=0;ch++)
            {
                if (*ch<'0' || *ch>'9') return 0;
            }
            x=atoi(str);
            if (x<desc->Min || x>desc->Max) return 0;
            *((int*)ret)=x;
            ret=(char*)ret+sizeof(int);
            break;
        }
        case CDataDescription::dtDouble:
        {
            double x;
            if (str[0] == 0) return 0;
            x=strtod(str,&ch);
            if (ch>=str && *ch!=0) return 0;
            if (x<desc->Min || x>desc->Max) return 0;
            *((double*)ret)=x;
               ret=(char*)ret+sizeof(double);
            break;
        }
        case CDataDescription::dtString:
        {
            for (ch=str;*ch!=0;ch++);
            if (ch-str<desc->Min || ch-str>desc->Max) return 0;
            for (ch=str;(ch-str)<desc->Max;ch++)
				*((char*)ret+(ch-str))=*ch;
			ret=(char*)ret+(int)desc->Max;
            break;
        }
    }
    return 1;
}

//back convertation: from void * data to string
void VoidToStr(void *x, CDataDescription *desc, char *str)
{
    char *ch=NULL;
    switch (desc->Type)
    {
        case CDataDescription::dtInt://integer
        {
            sprintf(str,"%i",((int*)x)[0]);
            break;
        }
        case CDataDescription::dtDouble://double
        {
            sprintf(str,"%f",(float)((double*)x)[0]);
            break;
        }
        case CDataDescription::dtString://char*
        {
            for (ch=(char*)x;(ch-(char*)x)<desc->Max;ch++) *(str+(ch-(char*)x))=*ch;
            break;
        }
    }   

}

//search data item number n
void *Search(void *x, CDataDescription *dd,int n)
{
    char*y=(char*)x;
    for (int i=0;i<n;i++)
    {
        switch (dd[i].Type)
        {
            case CDataDescription::dtInt:
            {
                y+=sizeof(int);
                break;
            }
            case CDataDescription::dtDouble:
            {
                y+=sizeof(double);
                break;
            }
            case CDataDescription::dtString:
            {
                y+=(int)dd[i].Max;
                break;
            }
        }   
    }
    return y;
}

//getting size of data item number n
DWORD GetSize(CDataDescription *dd,int n)
{
    DWORD size = 0;
    for (int i=0;i<n;i++)
    {
        switch (dd[i].Type)
        {
            case CDataDescription::dtInt:
            {
                size+=sizeof(int);
                break;
            }
            case CDataDescription::dtDouble:
            {
                size+=sizeof(double);
                break;
            }
            case CDataDescription::dtString:
            {
                size+=(int)dd[i].Max;
                break;
            }
			default:
			{
				char str[245];
				sprintf(str,"Type is %i",(int)(dd[i].Type));
				MessageBox(NULL,str,"1=1",MB_OK);
			}
        }   
    }
    return size;
}


#endif //__DATA_DESCRIPTION_CPP__
