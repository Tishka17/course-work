#ifndef __SETTINGS_CPP__
#define __SETTINGS_CPP__
#include "..\H\settings.h"
#include "stdio.h"
void LoadSettings(SETTINGS_MAIN_STRUCT &Settings_Struct, char *filename)
{
    CIniReader fin(filename);

    char Key[INI_MAX_KEY];
    char Value[INI_MAX_VALUE];
    char Section[INI_MAX_SECTION];
    
    while (!fin.eof()) 
    {
        fin.NextLine(Key, Value, Section);

        if (!strcmp(Section, "Language"))
        {
            if (!strcmp(Key, "Language File") && Value[0]!=0) strcpy(Settings_Struct.Language.LngFile, Value);
            if (!strcmp(Key, "Help File") && Value[0]!=0) strcpy(Settings_Struct.Language.HlpFile, Value);
            if (!strcmp(Key, "Hot Keys File") && Value[0]!=0) strcpy(Settings_Struct.Language.HotKeysFile, Value);
        }else 
        if (!strcmp(Section, "Windows"))
        {
            if (!strcmp(Key, "Height") && Value[0]!=0) Settings_Struct.Windows.Height=atoi(Value);
            if (!strcmp(Key, "Width") && Value[0]!=0) Settings_Struct.Windows.Width=atoi(Value);
            if (!strcmp(Key, "Separator Position") && Value[0]!=0) Settings_Struct.Windows.SeparatorPosition=atoi(Value);
        }else
        if (!strcmp(Section, "Libraries"))
        {
            if (!strcmp(Key, "ReadData") && Value[0]!=0) strcpy(Settings_Struct.Libraries.ReadDataDll, Value);
            if (!strcmp(Key, "Graphics") && Value[0]!=0) strcpy(Settings_Struct.Libraries.GraphicsDll, Value);
            if (!strcmp(Key, "Approximation") && Value[0]!=0) strcpy(Settings_Struct.Libraries.ApproximationDll, Value);
            if (!strcmp(Key, "Input") && Value[0]!=0) strcpy(Settings_Struct.Libraries.InputDll, Value);
        }else
        if (!strcmp(Section, "Auto Scripts"))
        {
            if (!strcmp(Key, "On Start") && Value[0]!=0) strcpy(Settings_Struct.AutoScripts.OnStart, Value);
            if (!strcmp(Key, "On Exit") && Value[0]!=0) strcpy(Settings_Struct.AutoScripts.OnExit, Value);
            if (!strcmp(Key, "On Load Image") && Value[0]!=0) strcpy(Settings_Struct.AutoScripts.OnOpenImage, Value);
            if (!strcmp(Key, "Console Input") && Value[0]!=0) strcpy(Settings_Struct.AutoScripts.ConsoleInput, Value);
        }else
        if (!strcmp(Section, "Recent"))
        {
            if (!strcmp(Key, "Number") && Value[0]!=0) Settings_Struct.Recent.Number=atoi(Value);
            else if (!strcmp(Key, "Maximal Number") && Value[0]!=0)
            {
                int x=atoi(Value);
                if (x<=50)
                {
                    for (int i=Settings_Struct.Recent.MaxNumber;i<x;i++) Settings_Struct.Recent.File[i][0]=0;
                    Settings_Struct.Recent.MaxNumber=x;
                }
            }
            else 
            {
                char str[256];
                Key[4]=0;
                strcpy(str, Key+5);
                int x=atoi(str);
                if (!strcmp(Key, "File") && Value[0]!=0 && x>0) strcpy(Settings_Struct.Recent.File[x-1], Value);
            }
        }
        else
        {
            if (!strcmp(Key, "Author") && Value[0]!=0) strcpy(Settings_Struct.Author, Value);
        }
    }
    //make filter
};

void LoadDefaultSettings(SETTINGS_MAIN_STRUCT &Settings_Struct)
{     
    strcpy(Settings_Struct.Language.LngFile, "English.lng");
    strcpy(Settings_Struct.Language.HlpFile, "English.chm");
    strcpy(Settings_Struct.Language.HotKeysFile, "HotKeys.html");

    strcpy(Settings_Struct.Libraries.ReadDataDll, "DLL/ReadData.dll");
    strcpy(Settings_Struct.Libraries.GraphicsDll, "DLL/Graphics_.dll");
    strcpy(Settings_Struct.Libraries.ApproximationDll, "DLL/Approximation.dll");
    strcpy(Settings_Struct.Libraries.InputDll, "DLL/Input.dll");

    strcpy(Settings_Struct.AutoScripts.ConsoleInput, "AutoScripts/Console.sh");
    strcpy(Settings_Struct.AutoScripts.OnStart, "AutoScripts/Start.sh");
    strcpy(Settings_Struct.AutoScripts.OnExit, "AutoScripts/End.sh");
    strcpy(Settings_Struct.AutoScripts.OnOpenImage, "AutoScripts/OpenImage.sh");

    strcpy(Settings_Struct.Author, "_NSFGroup");

    Settings_Struct.Windows.Height=480;
    Settings_Struct.Windows.Width=640;
    Settings_Struct.Windows.SeparatorPosition=320;

    Settings_Struct.Recent.MaxNumber=5;
    Settings_Struct.Recent.Number=0;
}

void SaveSettings(SETTINGS_MAIN_STRUCT Settings_Struct, char *filename)
{
    CIniWriter fout(filename);
    
    fout.WriteComment("This is Fractals Analyser Settings file");
    fout.WriteKeyValue("Author", Settings_Struct.Author);
    fout.NextLine();
    fout.NextLine();

    fout.WriteSection("Language");
        {
            fout.NextLine();
            fout.WriteComment("Language settings are used only in GUI mode");
            fout.WriteKeyValue( "Language File", Settings_Struct.Language.LngFile);
            fout.WriteKeyValue( "Help File", Settings_Struct.Language.HlpFile);
            fout.WriteKeyValue( "Hot Keys File", Settings_Struct.Language.HotKeysFile);
        }
    fout.WriteSection("Libraries");
        {
            fout.NextLine();
            fout.WriteComment("These are paths to dlls which are needed for every run of the program");
            fout.WriteKeyValue( "ReadData", Settings_Struct.Libraries.ReadDataDll);
            fout.WriteKeyValue( "Approximation", Settings_Struct.Libraries.ApproximationDll);
            fout.WriteKeyValue( "Graphics", Settings_Struct.Libraries.GraphicsDll);
            fout.WriteKeyValue( "Input", Settings_Struct.Libraries.InputDll);
        }
    fout.WriteSection("Windows");
        {
            fout.NextLine();
            fout.WriteComment("Here are default sizes of windows (used only in GUI_.exe)");
            char str[10];
            sprintf(str,"%i",Settings_Struct.Windows.Height);
            fout.WriteKeyValue("Height",str);            
            sprintf(str,"%i",Settings_Struct.Windows.Width);
            fout.WriteKeyValue("Width",str);            
            sprintf(str,"%i",Settings_Struct.Windows.SeparatorPosition);
            fout.WriteKeyValue("Separator Position",str);
        }
    fout.WriteSection("Auto Scripts");
        {

            fout.WriteKeyValue("On Start", Settings_Struct.AutoScripts.OnStart);
            fout.WriteKeyValue("On Exit", Settings_Struct.AutoScripts.OnExit);
            fout.WriteKeyValue("On Load Image", Settings_Struct.AutoScripts.OnOpenImage);
            fout.WriteKeyValue("Console Input", Settings_Struct.AutoScripts.ConsoleInput);
        }
    fout.WriteSection("Recent");
        {
            fout.NextLine();
            fout.WriteComment("List of file which were recent opened");
            char str[20];
            sprintf(str,"%i",Settings_Struct.Recent.Number);
            fout.WriteKeyValue("Number", str);
            sprintf(str,"%i",Settings_Struct.Recent.MaxNumber);
            fout.WriteKeyValue("Maximal Number", str);
            for (int i=0;i<Settings_Struct.Recent.Number && i<Settings_Struct.Recent.MaxNumber;i++)
            {
                sprintf(str,"File %i", i+1);
                fout.WriteKeyValue( str, Settings_Struct.Recent.File[i]);
            }
        }
    fout.NextLine();
    fout.NextLine();
    fout.WriteComment("Thank you for using Fractals Analyser");
};

#endif //__SETTINGS_VPP__