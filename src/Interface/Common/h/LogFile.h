#ifndef  __LOGFILE_H__
#define  __LOGFILE_H__
#include "..\..\..\Common\H\wndws.h"

void SetLogFilePath();
void SetLogFilePath(char *str);
void GetLogFilePath(char *str);
bool ExistsLogFile();
bool OpenLog();
bool CloseLog();
void WriteLogHeader();
void WriteLog(char *s);
void WriteLog(double a);
void WriteLogFontColor(char *s);
void WriteLogFontEnd();
void WriteLogUnderlined();
void WriteLogUnderlinedEnd();
void WriteLogBold();
void WriteLogBoldEnd();
void WriteLogNewLine();
void WriteLog2Digits(UINT a);
void WriteLog3Digits(UINT a);
void WriteLogDateTime(LPSYSTEMTIME time);
void WriteLogTime(LPSYSTEMTIME time);
void WriteLogStarted(char *s = NULL);
void WriteLogFinished();
void WriteLogError(char *s);
void WriteLogTable();
void WriteLogTableLight();
void WriteLogTableColor(char *s);
void WriteLogTableInvisible();
void WriteLogTableEnd();
void WriteLogRow();
void WriteLogRowEnd();
void WriteLogCell();
void WriteLogCell(char *width);
void WriteLogCellEnd();
void WriteLogPre();
void WriteLogPreEnd();
void WriteLogFunctionCall(char *dll, char *function);
void WriteLogFunctionCallTime(LPSYSTEMTIME time1, LPSYSTEMTIME time2);
void WriteLogFunctionString(char *str);
void WriteLogFunctionCallEnd();
void WriteLogFunctionCallInfo(char *dll, char *function, LPSYSTEMTIME time1, LPSYSTEMTIME time2,double ret, char *str);

#endif //__LOGFILE_H__