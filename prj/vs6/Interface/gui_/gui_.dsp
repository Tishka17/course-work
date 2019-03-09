# Microsoft Developer Studio Project File - Name="GUI_" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=GUI_ - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "GUI_.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "GUI_.mak" CFG="GUI_ - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GUI_ - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "GUI_ - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "GUI_ - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\bin\Release\"
# PROP Intermediate_Dir "..\..\..\..\bin\Release\TEMP"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_GUI_" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_GUI_" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /machine:I386

!ELSEIF  "$(CFG)" == "GUI_ - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\bin\Debug\"
# PROP Intermediate_Dir "..\..\..\..\bin\Debug\Temp"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_GUI_" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_GUI_" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "GUI_ - Win32 Release"
# Name "GUI_ - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Common"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=..\..\..\..\src\Common\CPP\_LIST.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\Common\CPP\Data.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\Common\CPP\DataDescription.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\Common\CPP\Graphic.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\Common\CPP\Plugins.cpp
# End Source File
# End Group
# Begin Group "Inteface Common"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\..\src\Interface\Common\CPP\DLLsUsage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\Interface\Common\CPP\FileIni.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\Interface\Common\CPP\Language.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\Interface\Common\CPP\LogFile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\Interface\Common\CPP\PluginsUsage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\Interface\Common\cpp\script.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\Interface\Common\CPP\Settings.cpp
# End Source File
# End Group
# Begin Group "Interface"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\..\src\Interface\GUI_\Interface\CPP\Corners.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\Interface\GUI_\Interface\CPP\Dialogs.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\Interface\GUI_\Interface\CPP\Menu.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\..\..\src\Interface\GUI_\GUI_.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Common headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\..\src\Common\H\_LIST.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\Common\H\Approximator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\Common\H\Data.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\Common\H\DataDescription.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\Common\H\Graphic.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\Common\H\Plugins.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\Common\H\wndws.h
# End Source File
# End Group
# Begin Group "Inteface Common Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\..\src\Interface\Common\H\DLLsUsage.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\Interface\Common\H\FileIni.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\Interface\Common\H\Language.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\Interface\Common\H\LogFile.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\Interface\Common\H\PluginsUsage.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\Interface\Common\H\Settings.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\Interface\Common\H\Variables.h
# End Source File
# End Group
# Begin Group "Interface header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\..\src\Interface\GUI_\Interface\H\Corners.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\Interface\GUI_\Interface\H\Dialogs.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\Interface\GUI_\Interface\H\Menu.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\..\..\src\Interface\GUI_\GUI_.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
