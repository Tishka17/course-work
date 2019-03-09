#ifndef __FILEINI_H__
#define __FILEINI_H__

#include "fstream.h"

#ifndef MAX_PATH
  #define MAX_PATH 256
#endif //MAX_PATH

#ifndef BOOL
  #define BOOL  char
  #define TRUE  1
  #define FALSE 0
#endif //BOOL

#define INI_MAX_SECTION 256
#define INI_MAX_COMMENT 256
#define INI_MAX_KEY	    256
#define INI_MAX_VALUE   256
#define INI_MAXALL      INI_MAX_SECTION+INI_MAX_COMMENT+INI_MAX_KEY+INI_MAX_VALUE-3

#define  INI_StartSection  '['
#define  INI_EndSection    ']'
#define  INI_StartValue    '='
#define  INI_StartComment  ';'
#define  INI_NewLine       "\n"

#define INI_ISSECTION 1
#define INI_ISKEY     2
#define INI_ISVALUE   4
#define INI_ISCOMMENT 8

class CIniReader
{
  protected:
    ifstream fin;
    char FileName[MAX_PATH];
    char LastKey[INI_MAX_KEY];
    char LastValue[INI_MAX_VALUE];
    char Section[INI_MAX_SECTION];
    char LastComment[INI_MAX_COMMENT];
    char string[INI_MAXALL];
    char *firstchar;

    BOOL WasComment;
    BOOL opened;
    BOOL lineend;
    BOOL end;

  public:
    CIniReader   (void);//default constructor
    CIniReader   (char *name);//constructor opening file
    void Open    (char *name);//open file
    void Close   (void);//close file
   ~CIniReader   (void);//destructor, closes file if it is opened

    void GetName    (char *);//get name of a file
    void GetKey     (char *);//get key name
    void GetValue   (char *);//get value of a key
    void GetSection (char *);//get section name
    void GetComment (char *);//get last comment

    int  NextLine (void);//reads next line from file and stores LastKey, Section, LastValue and LastComment if modified. Returns what was modified.
    int  NextLine (char *Key, char *Value, char *Section=NULL, char *Comment=NULL);//reads next line from file and stores LastKey, Section, LastValue and LastComment if modified. Returns what was modified.
    int  NextTerm (void);//reads next term from file (key, value, section or comment) and returns what it has read
    BOOL eof(void);
};

class CIniWriter
{
  protected:
    ofstream fout;
    char FileName[MAX_PATH];
    char LastKey[INI_MAX_KEY];
    char LastValue[INI_MAX_VALUE];
    char Section[INI_MAX_SECTION];
    char LastComment[INI_MAX_COMMENT];
    char string[INI_MAXALL];
    char *firstchar;

    BOOL WasComment;
    BOOL opened;
    BOOL lineend;

  public:
    CIniWriter   (void);//default constructor
    CIniWriter   (char *name);//constructor opening file
    void Open    (char *name);//open file
    void Close   (void);//close file
   ~CIniWriter   (void);//destructor, closes file if it is opened

    void GetName    (char *);//get name of a file
    void GetKey     (char *);//get key name
    void GetValue   (char *);//get value of a key
    void GetSection (char *);//get section name
    void GetComment (char *);//get last comment

    int  NextLine     (void);//writes new line character
    int  Write        (char *Key, char *Value, char *Section=NULL, char *Comment=NULL);//Writes Key, Section, Value and Comment to file
    int  WriteSection (char *s);
    int  WriteComment (char *s);
    int  WriteKey     (char *s);
    int  WriteValue   (char *s);
    int  WriteKeyValue(char *key, char *value);
};

#endif //__FILEINI_H__