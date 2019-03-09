#ifndef __LANGUAGE_CPP__
#define __LANGUAGE_CPP__

#include "..\..\..\Common\H\Data.h"
#include "..\H\Language.h"
#include "..\H\FileIni.h"

void LoadLangStruct(LNG_MAIN_STRUCT &Lng_Main_Struct, char *filename)
{
    CIniReader fin(filename);

    char Key[INI_MAX_KEY];
    char Value[INI_MAX_VALUE];
    char Section[INI_MAX_SECTION];
    
    while (!fin.eof()) 
    {
        fin.NextLine(Key, Value, Section);

        if (!strcmp(Section, "Main Menu"))
        {
            if (!strcmp(Key, "File") && Value[0]!=0) strcpy(Lng_Main_Struct.MainMenu.File, Value);
            if (!strcmp(Key, "View") && Value[0]!=0) strcpy(Lng_Main_Struct.MainMenu.View, Value);
            if (!strcmp(Key, "Plugins") && Value[0]!=0) strcpy(Lng_Main_Struct.MainMenu.Plugins, Value);
            if (!strcmp(Key, "Help") && Value[0]!=0) strcpy(Lng_Main_Struct.MainMenu.Help, Value);
        }
        if (!strcmp(Section, "File Menu"))
        {
            if (!strcmp(Key, "Open") && Value[0]!=0) strcpy(Lng_Main_Struct.FileMenu.Open, Value);
            if (!strcmp(Key, "Save") && Value[0]!=0) strcpy(Lng_Main_Struct.FileMenu.Save, Value);
            if (!strcmp(Key, "Run batch file") && Value[0]!=0) strcpy(Lng_Main_Struct.FileMenu.RunBat, Value);
            if (!strcmp(Key, "Recent") && Value[0]!=0) strcpy(Lng_Main_Struct.FileMenu.Recent, Value);
            if (!strcmp(Key, "Exit") && Value[0]!=0) strcpy(Lng_Main_Struct.FileMenu.Exit, Value);
        }
        if (!strcmp(Section, "View Menu"))
        {
            if (!strcmp(Key, "Left Panel") && Value[0]!=0) strcpy(Lng_Main_Struct.ViewMenu.LeftPanel, Value);
            if (!strcmp(Key, "Right Panel") && Value[0]!=0) strcpy(Lng_Main_Struct.ViewMenu.RightPanel, Value);
            if (!strcmp(Key, "Show Log File") && Value[0]!=0) strcpy(Lng_Main_Struct.ViewMenu.ShowLogFile, Value);
        }
        if (!strcmp(Section, "Help Menu"))
        {
            if (!strcmp(Key, "Help") && Value[0]!=0) strcpy(Lng_Main_Struct.HelpMenu.Help, Value);
            if (!strcmp(Key, "About") && Value[0]!=0) strcpy(Lng_Main_Struct.HelpMenu.About, Value);
            if (!strcmp(Key, "Hot Keys") && Value[0]!=0) strcpy(Lng_Main_Struct.HelpMenu.HotKeys, Value);
            if (!strcmp(Key, "Web site") && Value[0]!=0) strcpy(Lng_Main_Struct.HelpMenu.Internet, Value);
        }
        if (!strcmp(Section, "Panel Menu"))
        {
            if (!strcmp(Key, "Color Picture") && Value[0]!=0) strcpy(Lng_Main_Struct.PanelMenu.ColorPicture, Value);
            if (!strcmp(Key, "Picture") && Value[0]!=0) strcpy(Lng_Main_Struct.PanelMenu.Picture, Value);
            if (!strcmp(Key, "No Picture") && Value[0]!=0) strcpy(Lng_Main_Struct.PanelMenu.NoPicture, Value);
            if (!strcmp(Key, "Disabled") && Value[0]!=0) strcpy(Lng_Main_Struct.PanelMenu.Disabled, Value);
        }
        if (!strcmp(Section, "Files Filter"))
        {
            if (!strcmp(Key, "bmp") && Value[0]!=0) strcpy(Lng_Main_Struct.FileFilter.bmp, Value);
            if (!strcmp(Key, "*") && Value[0]!=0) strcpy(Lng_Main_Struct.FileFilter.Any, Value);
        }
        if (!strcmp(Section, "Dialogs"))
        {
            if (!strcmp(Key, "Open Dialog Caption") && Value[0]!=0) strcpy(Lng_Main_Struct.Dialogs.OpenDialogCaption, Value);
            if (!strcmp(Key, "Save Dialog Caption") && Value[0]!=0) strcpy(Lng_Main_Struct.Dialogs.SaveDialogCaption, Value);
        }
        if (!strcmp(Section, ""))
        {
            if (!strcmp(Key, "Author") && Value[0]!=0) strcpy(Lng_Main_Struct.Author, Value);
        }
    }
    //make filter
    char *bmp="*.bmp";
    char *Any="*.*";
    int k=0;
    UINT i;
    for (i=0;i<=strlen(Lng_Main_Struct.FileFilter.bmp);i++)
    {Lng_Main_Struct.FileFilter.Filter[k] = Lng_Main_Struct.FileFilter.bmp[i];k++;}
    for (i=0;i<=strlen(bmp);i++)
    {Lng_Main_Struct.FileFilter.Filter[k] = bmp[i];k++;}
    for (i=0;i<=strlen(Lng_Main_Struct.FileFilter.Any);i++)
    {Lng_Main_Struct.FileFilter.Filter[k] = Lng_Main_Struct.FileFilter.Any[i];k++;}
    for (i=0;i<=strlen(Any);i++)
    {Lng_Main_Struct.FileFilter.Filter[k] = Any[i];k++;}
};

void LoadDefaultLangStruct(LNG_MAIN_STRUCT &Lng_Main_Struct)
{
    strcpy(Lng_Main_Struct.Author, "Tishka17");

    strcpy(Lng_Main_Struct.MainMenu.File,   "&File");
    strcpy(Lng_Main_Struct.MainMenu.View,   "&View");
    strcpy(Lng_Main_Struct.MainMenu.Plugins,"&Plugins");
    strcpy(Lng_Main_Struct.MainMenu.Help,   "&Help");

    strcpy(Lng_Main_Struct.FileMenu.Open,    "&Open \tCtrl+O");
    strcpy(Lng_Main_Struct.FileMenu.Save,    "&Save \tCtrl+S");
    strcpy(Lng_Main_Struct.FileMenu.RunBat,  "&Run batch file");
    strcpy(Lng_Main_Struct.FileMenu.Recent,    "Re&cent");
    strcpy(Lng_Main_Struct.FileMenu.Exit,    "&Exit \tCtrl+Q");

    strcpy(Lng_Main_Struct.ViewMenu.LeftPanel, "&Left Panel");
    strcpy(Lng_Main_Struct.ViewMenu.RightPanel, "&Right Panel");
    strcpy(Lng_Main_Struct.ViewMenu.ShowLogFile, "&Show Log File");

    strcpy(Lng_Main_Struct.HelpMenu.Help, "&Help \tF1");
    strcpy(Lng_Main_Struct.HelpMenu.About, "&About \tCtrl+F1");
    strcpy(Lng_Main_Struct.HelpMenu.HotKeys, "Hot &Keys");
    strcpy(Lng_Main_Struct.HelpMenu.Internet, "Visit &web site");
    
    strcpy(Lng_Main_Struct.PanelMenu.ColorPicture, "&Color Picture");
    strcpy(Lng_Main_Struct.PanelMenu.Picture, "&Picture");
    strcpy(Lng_Main_Struct.PanelMenu.NoPicture, "&No Picture");
    strcpy(Lng_Main_Struct.PanelMenu.Disabled, "&Disabled");
        
    strcpy(Lng_Main_Struct.FileFilter.bmp, "Bit maps (*.bmp)");
    strcpy(Lng_Main_Struct.FileFilter.Any, "Any files (*.*)");
    
    strcpy(Lng_Main_Struct.Dialogs.OpenDialogCaption, "Opening picture");
    strcpy(Lng_Main_Struct.Dialogs.SaveDialogCaption, "Saving picture");
    
    //make filter
    char *bmp="*.bmp";
    char *Any="*.*";
    int k=0;
    UINT i;
    for (i=0;i<=strlen(Lng_Main_Struct.FileFilter.bmp);i++)
    {Lng_Main_Struct.FileFilter.Filter[k] = Lng_Main_Struct.FileFilter.bmp[i];k++;}
    for (i=0;i<=strlen(bmp);i++)
    {Lng_Main_Struct.FileFilter.Filter[k] = bmp[i];k++;}
    for (i=0;i<=strlen(Lng_Main_Struct.FileFilter.Any);i++)
    {Lng_Main_Struct.FileFilter.Filter[k] = Lng_Main_Struct.FileFilter.Any[i];k++;}
    for (i=0;i<=strlen(Any);i++)
    {Lng_Main_Struct.FileFilter.Filter[k] = Any[i];k++;}
}

void SaveLangStruct(LNG_MAIN_STRUCT &Lng_Main_Struct, char *filename)
{
    CIniWriter fout(filename);
    
    fout.WriteComment("This is Fractals Analyser Language file");
    fout.WriteKeyValue("Author", Lng_Main_Struct.Author);
    fout.NextLine();
    fout.NextLine();

    fout.WriteSection("Main Menu");
        {
            fout.WriteKeyValue( "File", Lng_Main_Struct.MainMenu.File);
            fout.WriteKeyValue( "View", Lng_Main_Struct.MainMenu.View);
            fout.WriteKeyValue("Plugins", Lng_Main_Struct.MainMenu.Plugins);
            fout.WriteKeyValue("Help", Lng_Main_Struct.MainMenu.Help);
        }
    fout.WriteSection("File Menu");
        {
            fout.WriteKeyValue("Open", Lng_Main_Struct.FileMenu.Open);
            fout.WriteKeyValue("Save", Lng_Main_Struct.FileMenu.Save);
            fout.WriteKeyValue("Run batch file", Lng_Main_Struct.FileMenu.RunBat);
            fout.WriteKeyValue("Recent", Lng_Main_Struct.FileMenu.Recent);
            fout.WriteKeyValue("Exit", Lng_Main_Struct.FileMenu.Exit);
        }
    fout.WriteSection("View Menu");
        {
            fout.WriteKeyValue("Left Panel", Lng_Main_Struct.ViewMenu.LeftPanel);
            fout.WriteKeyValue("Right Panel", Lng_Main_Struct.ViewMenu.RightPanel);
            fout.WriteKeyValue("Show Log File", Lng_Main_Struct.ViewMenu.ShowLogFile);
        }
    fout.WriteSection("Help Menu");
        {
            fout.WriteKeyValue("Help", Lng_Main_Struct.HelpMenu.Help);
            fout.WriteKeyValue("About", Lng_Main_Struct.HelpMenu.About);
            fout.WriteKeyValue("Web site", Lng_Main_Struct.HelpMenu.Internet);
            fout.WriteKeyValue("Hot Keys", Lng_Main_Struct.HelpMenu.HotKeys);
        }
    fout.WriteSection("Panel Menu");
        {
            fout.WriteKeyValue("Color Picture", Lng_Main_Struct.PanelMenu.ColorPicture);
            fout.WriteKeyValue("Picture", Lng_Main_Struct.PanelMenu.Picture);
            fout.WriteKeyValue("No Picture", Lng_Main_Struct.PanelMenu.NoPicture);
            fout.WriteKeyValue("Disabled", Lng_Main_Struct.PanelMenu.Disabled);
        } 
    fout.WriteSection("Files Filter");
        {
            fout.WriteKeyValue("bmp", Lng_Main_Struct.FileFilter.bmp);
            fout.WriteKeyValue("*", Lng_Main_Struct.FileFilter.Any);
        }
    fout.WriteSection("Dialogs");
        {
            fout.WriteKeyValue("Open Dialog Caption", Lng_Main_Struct.Dialogs.OpenDialogCaption);
            fout.WriteKeyValue("Save Dialog Caption", Lng_Main_Struct.Dialogs.SaveDialogCaption);
        }

};

#endif //__LANGUAGE_CPP__