#ifndef __SCRIPT_H__
#define __SCRIPT_H__
#include "..\H\variables.h"

#define STRING_START   '\"'
#define STRING_END     '\"'
#define COMMENT_START  '#'
#define COMMENT_END    0
#define VARIABLE_START '$'
#define BRACKET_OPEN   '('
#define BRACKET_CLOSE  ')'
#define ARRAY_OPEN     '['
#define ARRAY_CLOSE    ']'
#define COMMA          ','
#define LABEL_DEFINE   ':'
#define MODIFER        '/'
#define DO_NOT_ECHO    '@'

class CStringItem:public CListItem
{
    public:
        CStringItem():CListItem(){str[0]=0;}
        String str;
};

class CVariable:public CListItem
{
    public:
        CVariable(char *n=NULL, char*v=NULL):CListItem()
        {
            if (n==NULL) name[0]=0;
            else strcpy(name,n);
            if (v==NULL) value[0]=0;
            else strcpy(value,v);
        }
        String name,value;
};

class CLabel:public CListItem
{
    public:
        CLabel(char *n=NULL, int p=0):CListItem(){strcpy(name,n);position=p;}
        String name;
        int position;
};


void RemoveSpaces(LongString oldstr, LongString newstr);//remove all double spaces and spaces in the end and beginning of the string
void RemoveComments(LongString oldstr, LongString newstr);
void RemoveQuotes(LongString oldstr, LongString newstr);
char *LastChar(LongString str);
char *FindSymbol(LongString str, char ch);
bool SeparateString(LongString oldstr, LongString newstr1, LongString newstr2);
bool CorrectIdentifer(LongString str);
bool CorrectInt(LongString str);
bool GetLabels(ifstream &fin, CList &LabelList);
bool Test(LongString str, CList &varlist1, CList &varlist2);
bool Calc(LongString oldstr, LongString newstr);
bool ResolveVariables(LongString oldstr, LongString newstr, CList &LocalVariableList, CList &VariableList);
CVariable *Search(LongString str, CList &varlist);

//interpret one line of command (no more than one command in it except if statement)
int Command(ifstream &fin, 
            CList &LabelList, 
            CList &VariableList, 
            CList &LocalVariableList, 
            CList &Plugins, 
            SDLLs Dlls, 
            TImage &Picture,
            TColorImage &ColorPicture,
            SApproximation Approximation,
            CList &Graphics,
            CList &Layers,
            LongString str, 
            int previousstate, 
            bool &echo
           );

//interprets the whole file line by line
int Interpret(char *fname, 
              CList &VariableList, 
              CList &Plugins, 
              SDLLs Dlls,
              TImage &Picture,
              TColorImage &ColorPicture,
              SApproximation Approximation,
              CList &Graphics,
              CList &Layers
             );

#endif __SCRIPT_H__