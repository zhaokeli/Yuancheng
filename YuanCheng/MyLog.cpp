#include "stdafx.h"
#include "MyLog.h"


MyLog::MyLog(void)
{
}


MyLog::~MyLog(void)
{
}
void MyLog::WriteLog(CString str){
#ifdef _DEBUG
	OutputDebugString(str );
	OutputDebugString(_T("\n"));
#else
	CTime t = CTime::GetCurrentTime();
	CString t_str=t.Format("%Y-%m-%d %H:%M:%S");
	FILE * file=fopen("log.log","a+");
	str+="----->"+t_str+"\r\n";
	fwrite(str,strlen(str),1,file);
	fclose(file);
#endif
}
