#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#include "..\..\..\Common\H\Data.h"
#include "FileIni.h"

struct SETTINGS_MAIN_STRUCT
{
    struct 
    {
        String LngFile;
        String HlpFile;
        String HotKeysFile;
    } Language;
    struct 
    {
        String ReadDataDll;
        String GraphicsDll;
        String ApproximationDll;
        String InputDll;
    } Libraries;
    String Author;
    struct
    {
        int Width;
        int Height;
        int SeparatorPosition;
    } Windows;
    struct
    {
        String File[50];
        int Number;
        int MaxNumber;
    } Recent;

    struct
    {
        String OnStart;
        String OnExit;
        String OnOpenImage;
        String ConsoleInput;
    } AutoScripts;
};

//loads setting from ini file
void LoadSettings(SETTINGS_MAIN_STRUCT&, char *filename);

//loads default setting stored nowhere
void LoadDefaultSettings(SETTINGS_MAIN_STRUCT&);

//saves setting to ini file
void SaveSettings(SETTINGS_MAIN_STRUCT, char *filename);

#endif //__SETTINGS_H__