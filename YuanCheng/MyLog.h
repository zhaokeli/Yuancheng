#ifndef _MYLOG_H_
#define _MYLOG_H_

#pragma once
#include "stdafx.h"
class MyLog
{
public:
	MyLog(void);
	~MyLog(void);
	/**
	 *记录日志文件
	 **/
	static void WriteLog(CString str);
};

#endif