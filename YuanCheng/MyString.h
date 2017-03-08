#pragma once
#include "stdafx.h"
#define C1 52845
#define C2 22719
class CMyString
{
private:
	string subject;
public:
	CMyString(string subject);
	CMyString(void);
	~CMyString(void);
	string replace(string search,string replace,string subject="");
	string enString(const char* src,const char* key);
	string deString(const char* src,const char* key);
	char* substr(const char* _str,int pos,int len);

	CString Encryptt(CString S, WORD Key);
	CString Decryptt(CString S, WORD Key);
};

