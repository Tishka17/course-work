#ifndef __FILEINI_CPP__
#define __FILEINI_CPP__

#include "..\H\FileIni.h"
#include "string.h"

//==============================================================================================
char *FIRSTCHAR(char*a)
{
    char *b=a;
    while((*b<33 && *b>0) || int(*b) == 255)
    {
        b++;
    }
    return b;
};

void SETEND(char *a)
{
    char *b=a+strlen(a)-1;
    while((*b<33 && *b>0) || int(*b) == 255 && b>=a)
    {
        b--;
    }
    b++;
    *b=0;
}

//==============================================================================================
//CIniReader
CIniReader::CIniReader(void)
{
    opened = FALSE;
    WasComment = FALSE;
    lineend = TRUE;
    end = FALSE;

    LastKey    [0]=0;
    LastValue  [0]=0;
    Section    [0]=0;
    LastComment[0]=0;
}

CIniReader::CIniReader(char *name)
{
    strcpy(FileName, name);
    WasComment = FALSE;
    lineend = TRUE;

    LastKey    [0]=0;
    LastValue  [0]=0;
    Section    [0]=0;
    LastComment[0]=0;

    fin.open(FileName);
    if (fin.good()) opened = TRUE;
    else  opened = FALSE;
    end = fin.eof();
}

void CIniReader::Open(char *name)
{
    strcpy(FileName, name);
    WasComment = FALSE;
    lineend = TRUE;

    LastKey    [0]=0;
    LastValue  [0]=0;
    Section    [0]=0;
    LastComment[0]=0;

    fin.open(FileName);
    if (fin.good()) opened = TRUE;
    else  opened = FALSE;
    end = fin.eof();
}

void CIniReader::Close(void)
{
    if (opened)
    {
        fin.close();
        opened = FALSE;
    }
}

CIniReader::~CIniReader(void)
{
    Close();
}


void CIniReader::GetName(char *s)
{
    strcpy(s, FileName);
}

void CIniReader::GetKey(char *s)
{
    strcpy(s, LastKey);
}

void CIniReader::GetValue(char *s)
{
    strcpy(s, LastValue);
}

void CIniReader::GetSection(char *s)
{
    strcpy(s, Section);
}

void CIniReader::GetComment(char *s)
{
    strcpy(s, LastComment);
}

int  CIniReader::NextLine (void)
{
    char *defsymbol;
    if (!opened) return -1;
    int result=0;//default result is 0 - empty string
    if (lineend)
    {
        if (fin.eof())
        {
            end = TRUE;
            return 0;
        }
        fin.getline(string, INI_MAXALL);//reading string from file
        end = fin.eof();
        firstchar=FIRSTCHAR(string);//finding first meaning symbol
    }
    lineend = FALSE;
    while (*firstchar != 0)
    {
        if (*firstchar == INI_StartSection)//section
        {
            defsymbol = firstchar;
            firstchar++;
            firstchar=FIRSTCHAR(firstchar);
            if (result)//there was something from previous section
            {
                firstchar = defsymbol;
                return result;
            }
            char *k = Section;
            for (char *i=firstchar;(*i!=0 && *i!=INI_EndSection && *i!=INI_StartComment); i++)
            {
                if (*i>=32 || *i<0)
                {
                    *k=*i;
                    k++;
                }
            }
            *k=0;
            firstchar = i;
            if (*firstchar == INI_EndSection) firstchar ++;
            result |= INI_ISSECTION;
            SETEND(Section);
        }
        else if (*firstchar == INI_StartComment)//comment
        {
            firstchar++;//ignore symbol ;
            firstchar=FIRSTCHAR(firstchar);//first meaning character
            char *k = LastComment;
            for (char *i=firstchar; (*i!=0); i++)
            {
                if (*i>=32 || *i<0)
                {
                    *k=*i;
                    k++;
                }
            }
            *k=0;
            lineend = TRUE;
            result |= INI_ISCOMMENT;
            SETEND(LastComment);
            return result;
        }
        else if (*firstchar == INI_StartValue)//values
        {
            defsymbol = firstchar;
            firstchar++;
            firstchar=FIRSTCHAR(firstchar);
            if (result & INI_ISVALUE)//there was another value
            {
                firstchar = defsymbol;
                return result;
            }
            char *k = LastValue;
            for (char *i=firstchar;(*i!=0 && *i!=INI_StartSection && *i!=INI_StartValue && *i!=INI_StartComment); i++)
            {
                if (*i>=32 || *i<0 || *i=='\t')
                {
                    *k=*i;
                    k++;
                }
            }
            *k=0;
            firstchar = i;
            result |= INI_ISVALUE;
            SETEND(LastValue); 
        }
        else//key
        {
            char *k = LastKey;
            for (char *i=firstchar;(*i!=0 && *i!=INI_StartSection && *i!=INI_StartValue && *i!=INI_StartComment); i++)
            {
                if (*i>=32 || *i<0)
                {
                    *k=*i;
                    k++;
                }
            }
            *k=0;
            firstchar = i;
            result |= INI_ISKEY;
            SETEND(LastKey);
        }
    }
    lineend = TRUE;
    return result;
}

int  CIniReader::NextTerm (void)
{
    char *defsymbol;
    if (!opened) return -1;
    int result=0;//default result is 0 - empty string
    if (lineend)
    {
        if (fin.eof())
        {
            end = TRUE;
            return 0;
        }
        fin.getline(string, INI_MAXALL);//reading string from file
        end = fin.eof();
        firstchar=FIRSTCHAR(string);//finding first meaning symbol
    }
    lineend = FALSE;
    if (*firstchar == INI_StartSection)//section
    {
        defsymbol = firstchar;
        firstchar++;
        firstchar=FIRSTCHAR(firstchar);
        char *k = Section;
        for (char *i=firstchar;(*i>0 && *i!=INI_EndSection && *i!=INI_StartComment); i++)
        {
            if (*i>=32 || *i<0)
            {
                *k=*i;
                k++;
            }
        }
        *k=0;
        firstchar = i;
        if (*firstchar == INI_EndSection) firstchar ++;
        result = INI_ISSECTION;
        SETEND(Section);
    }
    else if (*firstchar == INI_StartComment)//comment
    {
        firstchar++;//ignore symbol ;
        firstchar=FIRSTCHAR(firstchar);//first meaning character
        char *k = LastComment;
        for (char *i=firstchar; (*i>0); i++)
        {
            if (*i>=32 || *i<0)
            {
                *k=*i;
                k++;
            }
        }
        *k=0;
        lineend = TRUE;
        result = INI_ISCOMMENT;
        SETEND(LastComment);
    }
    else if (*firstchar == INI_StartValue)//values
    {
        defsymbol = firstchar;
        firstchar++;
        firstchar=FIRSTCHAR(firstchar);
        char *k = LastValue;
        for (char *i=firstchar;(*i>0 && *i!=INI_StartSection && *i!=INI_StartValue && *i!=INI_StartComment); i++)
        {
            if (*i>=32 || *i<0 || *i=='\t')
            {
                *k=*i;
                k++;
            }
        }
        *k=0;
        firstchar = i;
        result = INI_ISVALUE;
        SETEND(LastValue);
    }
    else//key
    {
        char *k = LastKey;
        for (char *i=firstchar;(*i>0 && *i!=INI_StartSection && *i!=INI_StartValue && *i!=INI_StartComment); i++)
        {
            if (*i>=32 || *i<0)
            {
                *k=*i;
                k++;
            }
        }
        *k=0;
        firstchar = i;
        result = INI_ISKEY;
        SETEND(LastKey);
    }
    if (firstchar == NULL)
    {
        lineend = TRUE;
    }
    return result;
}

int  CIniReader::NextLine (char *Key, char *Value, char *Section, char *Comment)
{
    BOOL le = lineend;
    int result = NextLine();
    if (Key != NULL)
        if ((result & INI_ISKEY) || (!le && (result & INI_ISVALUE))) GetKey(Key);
        else Key[0]=0;
    if (Value != NULL)
        if (result & INI_ISVALUE) GetValue(Value);
        else Value[0]=0;
    if (Section != NULL)  GetSection(Section);
    if (Comment != NULL)
        if (result & INI_ISCOMMENT) GetComment(Comment);
        else Comment[0]=0;
    return result;
}
BOOL CIniReader::eof()
{
    return end && lineend;
}

//==============================================================================================
//CIniWriter
CIniWriter::CIniWriter(void)
{
    opened = FALSE;
    WasComment = FALSE;
    lineend = TRUE;

    LastKey    [0]=0;
    LastValue  [0]=0;
    Section    [0]=0;
    LastComment[0]=0;
}

CIniWriter::CIniWriter(char *name)
{
    strcpy(FileName, name);
    WasComment = FALSE;
    lineend = TRUE;

    LastKey    [0]=0;
    LastValue  [0]=0;
    Section    [0]=0;
    LastComment[0]=0;

    fout.open(FileName);
    if (fout.good()) opened = TRUE;
    else  opened = FALSE;
}

void CIniWriter::Open(char *name)
{
    strcpy(FileName, name);
    WasComment = FALSE;
    lineend = TRUE;

    LastKey    [0]=0;
    LastValue  [0]=0;
    Section    [0]=0;
    LastComment[0]=0;

    fout.open(FileName);
    if (fout.good()) opened = TRUE;
    else  opened = FALSE;
}

void CIniWriter::Close(void)
{
    if (opened)
    {
        fout.close();
        opened = FALSE;
    }
}

CIniWriter::~CIniWriter(void)
{
    Close();
}

void CIniWriter::GetName(char *s)
{
    strcpy(s, FileName);
}

void CIniWriter::GetKey(char *s)
{
    strcpy(s, LastKey);
}

void CIniWriter::GetValue(char *s)
{
    strcpy(s, LastValue);
}

void CIniWriter::GetSection(char *s)
{
    strcpy(s, Section);
}

void CIniWriter::GetComment(char *s)
{
    strcpy(s, LastComment);
}

int  CIniWriter::NextLine (void)
{
    if (!opened) return -1;
    fout<<INI_NewLine;
    lineend = TRUE;
    return 0;
}

int  CIniWriter::Write (char *Key, char *Value, char *Section, char *Comment)
{
    if (!opened) return -1;
    WriteSection(Section);
    WriteKeyValue(Key, Value);
    WriteComment(Comment);
    return 0;
}

int  CIniWriter::WriteSection(char *s)
{
    if (!opened) return -1;
    if (s != NULL)
    {
        if (strcmp(s, Section))
        {
            if (!lineend) NextLine();
            fout<<INI_StartSection<<s<<INI_EndSection;
            strcpy(Section, s);
            lineend = FALSE;
        }
    }
    return 0;
}

int  CIniWriter::WriteComment(char *s)
{
    if (!opened) return -1;
    if (s != NULL)
    {
        fout<<INI_StartComment<<s;
        strcpy(LastComment, s);
        NextLine();
    }
    return 0;
}
int  CIniWriter::WriteKey(char *s)
{
    if (!opened) return -1;
    if (s != NULL)
    {
        if (!lineend) NextLine();
        fout<<"  "<<s;
        strcpy(LastKey, s);
        lineend = FALSE;
    }
    return 0;
}

int  CIniWriter::WriteValue(char *s)
{
    if (!opened) return -1;
    if (s != NULL)
    {
        fout<<" "<<INI_StartValue<<" "<<s;
        strcpy(LastValue, s);
        lineend = FALSE;
    }
    return 0;
}

int  CIniWriter::WriteKeyValue(char *key, char *value)
{
    if (!opened) return -1;
    WriteKey(key);
    WriteValue(value);
    return 0;
}

//===========================================================================================
/* //test example for bc 3.11

#include "conio.h"
void main()
{
    clrscr();
    while (kbhit()) getch();
/* CIniWriter fout("test.ini");
    fout.Write("key1", "value1", "s1", "nothing");
    fout.Write("key2", "value2", "s2", "");
    fout.Write("key3", "value3", "s2");
    fout.Write("key4", "value4");
    fout.WriteValue("value4.1");
    fout.Close();

    CIniReader ini("lang.ini");
    char s[INI_MAX_SECTION];
    char k[INI_MAX_KEY];
    char v[INI_MAX_VALUE];
    char c[INI_MAX_COMMENT];

    while (!ini.eof())
    {
        ini.NextLine(k, v, s, c);
        textcolor(8);
        cputs("[ ");
        textcolor(11);
        cputs(s);
        textcolor(8);
        cputs(" ] ");
        textcolor(15);
        cputs(k);
        textcolor(8);
        cputs(" = ");
        textcolor(10);
        cputs(v);
        textcolor(8);
        cputs(" ; ");
        textcolor(7);
        cputs(c);
        cputs("\n\r");
    }

    getch();
};
*/ // end of test example


#endif //__FILEINI_CPP__
