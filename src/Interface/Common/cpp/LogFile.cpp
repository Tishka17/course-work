#ifndef  __LOGFILE_CPP__
#define  __LOGFILE_CPP__

#include "..\..\..\Common\H\Data.h"
#include "..\H\LogFile.h"
#include "stdio.h"
//#include "..\H\Variables.h"

static String LogFilePath="";
static FILE *LogFile;
String FractalsAnalyserName="\0";

void SetLogFilePath()
{
    GetCurrentDirectory(MAX_PATH, LogFilePath);
    strcat(LogFilePath, "\\__fractals.log.html");
};

void SetLogFilePath(char *str)
{
    strcpy(LogFilePath, str);
};

void GetLogFilePath(char *str)
{
	strcpy(str, LogFilePath);
}

bool ExistsLogFile()
{
    FILE *file;
    file = fopen(LogFilePath, "r");
    if (!file)//there is no such file
    {        
        return false;
    }
    else
    {
        fclose(file);
        return true;
    }
};

bool OpenLog()
{
    if (ExistsLogFile())
    {
        LogFile = fopen(LogFilePath, "a");
    }
    else
    {
        LogFile = fopen(LogFilePath, "w");
        WriteLogHeader();
    }
    if (!LogFile)//there is no such file
    {        
        return false;
    }
    else
    {
        return true;
    }
};

bool CloseLog()
{
    if (!LogFile)//there is no such file
    {        
        return false;
    }
    else
    {
        fclose(LogFile);
        return true;
    }
};

void WriteLogHeader()
{
    WriteLog("<HTML>\n");
    WriteLog("<HEAD>\n");
    WriteLog(" <TITLE>Fractals Analyser Log File </TITLE>\n");
    WriteLog("</HEAD>\n");
    WriteLog("<BODY text=\"#000000\" bgcolor=\"#aaaaaa\" >\n");    
};

void WriteLog(char *s)
{
    fputs(s, LogFile);
};

void WriteLog(double a)
{
    char s[256]="\0\0\0\0";
    gcvt(a, 10, s);
    fputs(s, LogFile);
};

void WriteLogFontColor(char *s)
{
    WriteLog("\n<FONT COLOR=\"");
    WriteLog(s);
    WriteLog("\">");
};

void WriteLogFontEnd()
{
    WriteLog("</FONT>");
}
void WriteLogUnderlined()
{
    WriteLog("<u>");
};

void WriteLogUnderlinedEnd()
{
    WriteLog("</u>");
};

void WriteLogBold()
{
    WriteLog("<b>");
};

void WriteLogBoldEnd()
{
    WriteLog("</b>");
};

void WriteLogNewLine()
{
    WriteLog("<br>\n");
}
void WriteLog2Digits(UINT a)
{
    char s[3]="\0\0";
    s[0] = '0' + ((a<10)?0:a/10);
    s[1] = '0' + (a%10);
    WriteLog(s);
}

void WriteLog3Digits(UINT a)
{
    char s[4]="\0\0\0";
    s[0] = '0' + ((a<100)?0:a/100);
    s[1] = '0' + ((a<10)?0:a%100/10);
    s[2] = '0' + a%10;
    WriteLog(s);
}

void WriteLogDateTime(LPSYSTEMTIME time)
{
    WriteLogFontColor("#800000");
    WriteLog2Digits(time->wYear/100);
    WriteLog2Digits(time->wYear%100);
    WriteLog(".");
    WriteLog2Digits(time->wMonth);
    WriteLog(".");
    WriteLog2Digits(time->wDay);
    WriteLog(" ");
    WriteLog2Digits(time->wHour);
    WriteLog(":");
    WriteLog2Digits(time->wMinute);
    WriteLog(":");
    WriteLog2Digits(time->wSecond);
    WriteLog(".");
    WriteLog3Digits(time->wMilliseconds);
    WriteLog(" ");
    WriteLogFontEnd();
};

void WriteLogTime(LPSYSTEMTIME time)
{
    WriteLogFontColor("#800000");
     WriteLog2Digits(time->wHour);
    WriteLog(":");
    WriteLog2Digits(time->wMinute);
    WriteLog(":");
    WriteLog2Digits(time->wSecond);
    WriteLog(".");
    WriteLog3Digits(time->wMilliseconds);
    WriteLog(" ");
    WriteLogFontEnd();
};

void WriteLogStarted(char *s)
{
    LPSYSTEMTIME time = new _SYSTEMTIME;
    GetLocalTime(time);
    WriteLogDateTime(time);
    WriteLogFontColor("#000050");
    WriteLog("Fractals Analyser ");    
    if (s) 
    {
        strcpy(FractalsAnalyserName, s);
        WriteLog(FractalsAnalyserName);
    }
    WriteLog(" was started.");
    WriteLogFontEnd();
    WriteLogNewLine();
};

void WriteLogFinished()
{
    LPSYSTEMTIME time = new _SYSTEMTIME;
    GetLocalTime(time);
    WriteLogDateTime(time);
    WriteLogFontColor("#000050");
    WriteLog("Fractals Analyser ");
    if (FractalsAnalyserName[0]) WriteLog(FractalsAnalyserName);
    WriteLog(" was closed.");    
    WriteLogFontEnd();
    WriteLogNewLine();
    WriteLog("<hr>");
    WriteLogNewLine();
    WriteLog("<hr>");
    WriteLogNewLine();
};

void WriteLogError(char *s)
{
    WriteLogFontColor("#ff0000");
    WriteLog("&#8855;&#8658; ");
    WriteLogUnderlined();
    WriteLog(s);
    WriteLogUnderlinedEnd();
    WriteLogFontEnd();
    WriteLogNewLine();
};

void WriteLogTable()
{
    WriteLog("<TABLE BORDER=\"1\" WIDTH=\"100%\" ALIGN=\"center\" BGCOLOR=\"#bbbbbb\">");
};

void WriteLogTableLight()
{
    WriteLog("<TABLE BORDER=\"1\" WIDTH=\"100%\" ALIGN=\"center\" BGCOLOR=\"#eeeecc\">");
};

void WriteLogTableColor(char *s)
{
    WriteLog("<TABLE BORDER=\"1\" WIDTH=\"100%\" ALIGN=\"center\" BGCOLOR=\"");
    WriteLog(s);
    WriteLog("\">");
};
void WriteLogTableInvisible()
{
    WriteLog("<TABLE BORDER=\"0\" CELLPADDING=\"10\" WIDTH=\"100%\" ALIGN=\"center\">");
};
void WriteLogTableEnd()
{
    WriteLog("</TABLE>");
};

void WriteLogRow()
{
    WriteLog("<TR>");
};

void WriteLogRowEnd()
{
    WriteLog("</TR>");
};

void WriteLogCell()
{
    WriteLog("<TD WIDTH=\"150\">");
};

void WriteLogCell(char *width)
{
    WriteLog("<TD NOWRAP WIDTH=\"");
    WriteLog(width);
    WriteLog("\">");
}

void WriteLogCellEnd()
{
    WriteLog("</TD>");
};

void WriteLogPre()
{
   WriteLog("<PRE>");
}
void WriteLogPreEnd()
{
   WriteLog("</PRE>");
}

void WriteLogFunctionCall(char *dll, char *function)
{
    //WriteLogFontColor("#000000");
    WriteLogTable();
    WriteLogRow();
    WriteLogCell();
    WriteLog("Dll Name");
    WriteLogCellEnd();
    WriteLogCell();
    WriteLog("Function Name");
    WriteLogCellEnd();
    WriteLogCell();
    WriteLog("Beginning Time");
    WriteLogCellEnd();
    WriteLogCell();
    WriteLog("End Time");
    WriteLogCellEnd();
    WriteLogCell();
    WriteLog("Calculation Time");
    WriteLogCellEnd();
    WriteLogCell();
    WriteLog("Result");
    WriteLogCellEnd();
    WriteLogRowEnd();
    WriteLog("\n");
    WriteLogRow();
    WriteLogCell();
    WriteLogFontColor("#000050");
    WriteLog(dll);
    WriteLogFontEnd();
    WriteLogCellEnd();
    WriteLogCell();
    WriteLogFontColor("#000050");
    WriteLog(function);
    WriteLogFontEnd();
    WriteLogCellEnd();
};

void WriteLogFunctionCallTime(LPSYSTEMTIME time1, LPSYSTEMTIME time2)
{
    WriteLogCell();
    WriteLogTime(time1);
    WriteLogCellEnd();
    WriteLogCell();
    WriteLogTime(time2);
    WriteLogCellEnd();
    WriteLogCell();

    if (!(time2->wMilliseconds>=time1->wMilliseconds)) 
    {
        time2->wSecond-=1;
        time2->wMilliseconds+=1000;
    }
    time2->wMilliseconds = time2->wMilliseconds-time1->wMilliseconds;

    if (!(time2->wSecond>=time1->wSecond)) 
    {
        time2->wMinute-=1;
        time2->wSecond+=60;
    }
    time2->wSecond = time2->wSecond-time1->wSecond;

    if (!(time2->wMinute>=time1->wMinute)) 
    {
        time2->wHour-=1;
        time2->wMinute+=60;
    }
    time2->wMinute = time2->wMinute-time1->wMinute;
    
    if (!(time2->wHour>=time1->wHour)) 
    {
        time2->wDay-=1;
        time2->wHour+=24;
    }
    time2->wHour = time2->wHour-time1->wHour;

    WriteLogTime(time2);
    WriteLogCellEnd();
    WriteLogCell();
    //WriteLogFontColor("#000050");
};

void WriteLogFunctionString(char *str)
{   
    if (str==NULL || str[0]==0) return;
    WriteLogTableLight();
    WriteLogRow();
    WriteLogCell();
    WriteLogFontColor("#000050");
    WriteLog("Function returned: ");
    WriteLogFontEnd();
    //WriteLogFontColor("#000000");
    WriteLogNewLine();
     WriteLogTableInvisible();
     WriteLogRow();
     WriteLogCell();
     WriteLogPre();
     WriteLog(str);
     WriteLogPreEnd();
     WriteLogCellEnd();
     WriteLogRowEnd();
     WriteLogTableEnd();
    WriteLogCellEnd();
    WriteLogRowEnd();
    WriteLogTableEnd();
    WriteLogNewLine();
}
void WriteLogFunctionCallEnd()
{
    WriteLogCellEnd();
    WriteLogRowEnd();
    WriteLogTableEnd();
    WriteLogNewLine();
};

void WriteLogFunctionCallInfo(char *dll, char *function, LPSYSTEMTIME time1, LPSYSTEMTIME time2,double ret, char *str)
{
    WriteLogFunctionCall(dll, function);
    WriteLogFunctionCallTime(time1, time2);
    WriteLog(ret);
    WriteLogFunctionCallEnd();
    WriteLogFunctionString(str);
}

#endif //__LOGFILE_CPP__