#include "..\..\Common\H\wndws.h"
#include "commdlg.h"
#include "math.h"
#include "stdlib.h"
#include "string.h"
#include "iostream.h"
#include "fstream.h"
#include "conio.h"

#include "..\Common\H\Variables.h"
#include "..\Common\Variables.var"
#include "..\Common\H\DllsUsage.h"
#include "..\Common\H\LogFile.h"
#include "..\Common\H\PluginsUsage.h"

#include "..\Common\H\Settings.h"
#include "..\Common\H\script.h"
#include "Console.h"
//main function(Tishka)  


int main(int argc, char* argv[])
{
    SetLogFilePath();

    bool FileRead=false;
    bool NeedHelp=false;
    char *FileIn = Settings_Struct.AutoScripts.ConsoleInput;
    CList GlobalVariables;
    if (argc>1)
    {
        if (argc>2 && !strcmp(argv[1], "-l"))
        {
            SetLogFilePath(argv[2]);
            if (argc>4 && !strcmp(argv[3], "-f"))
            {
                FileIn = argv[4];
                FileRead = true;
            }
        }
        else if (argc>2 && !strcmp(argv[1], "-f"))
        {
            FileIn = argv[2];
            FileRead = true;
            if (argc>4 && !strcmp(argv[3], "-l"))
            {
                SetLogFilePath(argv[4]);
            }
        }
    }
    for(int i=0;i<argc;i++) 
    {
        if (!strcmp(argv[i],"/?")) 
        {
            NeedHelp=true;
            break;
        }
    }
    OpenLog();
    WriteLogStarted("Console");

    DWORD WMessage = 0;
    
    LoadDefaultSettings(Settings_Struct);
    LoadSettings(Settings_Struct, "Settings.ini");
    
    if (!LoadApproximation(Approximation, Settings_Struct.Libraries.ApproximationDll))
    {
        WriteLogError("Error while loading Approximation DLL");
    }
    else
    {
        WIN32_FIND_DATAA fData;
        HANDLE Handle;
        char str[256];
        char *c;
        GetCurrentDirectory(MAX_PATH, str);
        strcat(str, "\\Plugins\\*.dll");
        Handle = FindFirstFile(str, &fData);

        if (Handle != INVALID_HANDLE_VALUE)
        {
            CPlugIn *pl=new CPlugIn;
			//CPlugIn *pl=(CPlugIn*)VirtualAlloc(NULL, sizeof(CPlugIn), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
            SearchPath("Plugins\\", fData.cFileName, NULL, 256, pl->Name, &c);
            if (LoadPlugin(pl, WMessage))
            {
                Plugins.Add(pl);
            }
            while (FindNextFile(Handle, &fData))
            {
                CPlugIn *pl=new CPlugIn;
                SearchPath("Plugins\\", fData.cFileName, NULL, 256, pl->Name, &c);
                if (LoadPlugin(pl, WMessage))
                {
                    Plugins.Add(pl);
                }
            }
            FindClose(Handle);
        }
    }
   
//Load all DLL's

    int error=-1;

    if (!LoadReadData(Dlls.ReadData.ReadData, Settings_Struct.Libraries.ReadDataDll, Dlls.ReadData.hInstance)) 
    {
        WriteLogError("Error while loading ReadData DLL");
        error = 2;
        MessageBox(NULL, "Error while loading ReadData DLL", "Error", MB_OK|MB_SYSTEMMODAL|MB_ICONSTOP);
    };
    if (!LoadInput(Dlls.Input.InitGUIInput, 
                   Dlls.Input.InitConsoleInput, 
                   Dlls.Input.InitFileInput, 
                   Dlls.Input.GUIInput, 
                   Dlls.Input.ConsoleInput, 
                   Dlls.Input.FileInput,
                   Settings_Struct.Libraries.InputDll,
                   Dlls.Input.hInstance)) 
    {
        WriteLogError("Error while loading Input DLL");
        error = 3;
        MessageBox(NULL, "Error while loading Input DLL", "Error", MB_OK|MB_SYSTEMMODAL|MB_ICONSTOP);
    };
    if (!Dlls.Input.InitConsoleInput())
    {
        WriteLogError("Error while initializing Console input");
        error = 0;
        MessageBox(NULL, "Error while initializing Console input", "Error", MB_OK|MB_SYSTEMMODAL|MB_ICONSTOP);
    }

    switch (error)
    {
        case 0:
            FreeLibrary(Dlls.Input.hInstance);
        case 3:
            FreeLibrary(Dlls.ReadData.hInstance);
        case 2:
        case 1:
            WriteLogFinished();
            CloseLog();
            SaveSettings(Settings_Struct, "Settings.ini");
            return error+1;
        default:
            break;
    }
    /////////////////////////////
    int result=22;
    CloseLog();
  
    //processing of fractals
    Interpret(Settings_Struct.AutoScripts.OnStart, GlobalVariables, Plugins, Dlls, Picture, ColorPicture, Approximation, Graphics, Layers);
    Interpret(FileIn, GlobalVariables, Plugins, Dlls, Picture, ColorPicture, Approximation, Graphics, Layers);
    Interpret(Settings_Struct.AutoScripts.OnExit, GlobalVariables, Plugins, Dlls, Picture, ColorPicture, Approximation, Graphics, Layers);

    FreeLibrary(Dlls.ReadData.hInstance);    
    FreeLibrary(Dlls.Input.hInstance);

    CListItem *C = Plugins.GetFirst();
    while (C)
    {
        FreePlugins((CPlugIn*)C);
        C = C->GetNext();
    };
    OpenLog();
    WriteLogFinished();
    CloseLog();

    SaveSettings(Settings_Struct, "Settings.ini");

    return 0;
}

/*
int Command(char *s, CPlugIn *First)
{
    char c[65536], p1[256], *sp, *b2, *b3;
    strcpy(c, s);
    sp = strchr(c, ' ');
    if ((sp != NULL && (sp-c)<255))//2 parameters
    {
        *sp = 0;
        b2 = sp+1;
        strcpy(p1, c);

        strupr(p1);
        if (!strcmp(p1, ">OPEN"))
        {
            OpenLog();
            char function[500]="ReadData(\"";
            strcat(function, b2);
            strcat(function, "\", &Picture)");
            WriteLogFunctionCall("ReadData.dll", function);
            LPSYSTEMTIME Time1 = new _SYSTEMTIME;
            LPSYSTEMTIME Time2 = new _SYSTEMTIME;
            GetLocalTime(Time1);
            LongString str="";
            int a = ReadData(b2, &ColorPicture, str); 
            GetLocalTime(Time2);
            WriteLogFunctionCallTime(Time1, Time2);
            WriteLog(a);
            WriteLogFunctionCallEnd();
            WriteLogFunctionString(str);
            CloseLog();
            if (!a) return 0;
            else return -1;
        }
        if (!strcmp(p1, ">SAVE"))
        {
            return 0;
        }
        if (!strcmp(p1, ">WRITELOG"))
        {
            OpenLog();
            WriteLog(b2);
            WriteLogNewLine();
            CloseLog();
            return 0;
        }       
        if (!strcmp(p1, ">WRITELOGERROR"))
        {
            OpenLog();
            WriteLogError(b2);
            CloseLog();
            return 0;
        }   
        if (!strcmp(p1, ">ECHO"))
        {
            cout<<b2<<endl;
            return 2;
        }   
        if (!strcmp(p1, ">LISTMETHODS"))
        {
            CPlugIn *p = First;
            CFunction *f;
            ofstream fout(b2, ios::out);
            fout<<"  >Open filename"<<"\n";
            fout<<"  >Save filename"<<"\n";
            fout<<"  >ListMethods filename"<<"\n";
            fout<<"  >WriteLog message"<<"\n";
            fout<<"  >WriteLogError errormessage"<<"\n";
            fout<<"  >Echo message"<<"\n";
            fout<<"  >Pause"<<"\n";
            fout<<"  >ShowLog"<<"\n";
            fout<<"  >Exit"<<"\n";
            while (p)
            {
                f = (CFunction*)p->Functions.GetFirst();
                while (f)
                {
                    fout<<"  "<<p->Name<<" "<<f->Name<<'\n';
                    f = (CFunction*)f->GetNext();
                }
                p = (CPlugIn*)p->GetNext();
            }
            return 0;
        }
        if (!strcmp(p1, ">EXIT") || !strcmp(p1, ">QUIT") || !strcmp(p1, ">Q") )
        {
            return 1;
        }
        else
        {
			b3=strchr(b2,' ');
			if (b3!=NULL) 
			{
				*b3=0;
				b3++;
				while (*b3<33 && *b3>0) b3++;
				if (*b3==0) b3=NULL;
			}
			if (b3) RunFunctionByName(c, b2, First, &Approximation, &Picture, &ColorPicture, &Graphics, &Layers, FileInput, true, b3);
			else RunFunctionByName(c, b2, First, &Approximation, &Picture, &ColorPicture, &Graphics, &Layers, ConsoleInput, true);
			bool q=RunFunctionByName(c, b2, First, &Approximation, &Picture, &ColorPicture, &Graphics, &Layers);
			if (q) return 0;
			else return -1;
        }
    }
    else if (sp == NULL && strlen(c)<255)//1 parameter
    {
        strcpy(p1, c);
        strupr(p1);
        if (!strcmp(p1, ">EXIT") || !strcmp(p1, ">QUIT") || !strcmp(p1, ">Q"))
        {
            return 1;
        }
        if (!strcmp(p1, ">ECHO"))
        {
            cout<<endl;
            return 2;
        }  
        if (!strcmp(p1, ">PAUSE"))
        {
            cout<<"Press any key to continue..."<<endl;
            while(kbhit()) getch();
            getch();
            return 2;
        }  
        if (!strcmp(p1, ">SHOWLOG"))
        {
			GetLogFilePath(LogFilePath);
            ShellExecute(NULL, "open", LogFilePath, NULL, NULL, SW_RESTORE);
            return 0;
        }
        if (!strcmp(p1, ">LISTMETHODS") || !strcmp(p1, ">HELP"))
        {
            CPlugIn *p = First;
            CFunction *f;
            cout<<"\n";
            cout<<"  >Open              filename"<<"\n";
            cout<<"  >Save              filename"<<"\n";
            cout<<"  >ListMethods               "<<"\n";
            cout<<"  >ListMethods       filename"<<"\n";
            cout<<"  >WriteLog          message"<<"\n";
            cout<<"  >WriteLogError     errormessage"<<"\n";
            cout<<"  >Echo message"<<"\n";
            cout<<"  >Pause"<<"\n";
            cout<<"  >ShowLog"<<"\n";
            cout<<"  >Exit"<<"\n\n";
            while (p)
            {
                f = (CFunction*)p->Functions.GetFirst();
                while (f)
                {
                    cout<<"  "<<p->Name<<" \t"<<f->Name<<'\n';
                    f = (CFunction*)f->GetNext();
                }
                cout<<'\n';
                p = (CPlugIn*)p->GetNext();
            }
            return 0;
        }
    }
    if (strlen(s)<2) return 2;
    else return -1;
}


*/