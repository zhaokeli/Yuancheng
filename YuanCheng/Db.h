#ifndef _DB_H
#define _DB_H
#pragma once

#include "stdafx.h"
//#import "C://Program Files//Common Files//System//ado//msado15.dll" 
#import "C:\\Program Files\\Common Files\\System\\ado\\msado15.dll" no_namespace rename("EOF","rsEOF")
class CDb
{
public:
	CDb(void);
	//得到数据集
	_RecordsetPtr GetRs(CString strSql);
	//执行SQL语句
	bool ExecuteSql(CString& strSql);
	//通过id取单个记录的一个字段
	string getByfield(string table,string id,string field);
public:
	~CDb(void);
private:
	_ConnectionPtr m_conn;
	_RecordsetPtr m_rs;

};
#endif