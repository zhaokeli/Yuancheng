#include "Db.h"
#include "shlwapi.h"
CDb::CDb(void)
{
	//初始化COM
	::CoInitialize(NULL);
	try
	{
		try {
			if (FAILED(m_conn.CreateInstance("ADODB.Connection")))
			{
				::MessageBox(NULL, _T("Create Instance failed!"), _T("错误"), MB_ICONEXCLAMATION);
				return;
			}
			TCHAR curDirPath[MAX_PATH];
			::GetModuleFileName(NULL, curDirPath,MAX_PATH);
			PathRemoveFileSpec(curDirPath);
			CString ss = curDirPath;
			CString conn = _T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=")+ss+_T("./data/data.mdb");
			//CString conn = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=./bin/data/data.mdb";
			//SQL SERVER连接字符串
			//CString conn="Driver={SQL Server};server=(local);uid=sa;database=pubs";//local可以改为127.0.0.1
			if (FAILED(m_conn->Open((_bstr_t)conn, "", "", -1)))
			{
				::MessageBox(NULL, _T("数据库连接失败"), _T("错误"), MB_ICONEXCLAMATION);
				return;
			}
		}catch(_com_error &e){
			::MessageBox(NULL, e.Description(), _T("错误"), MB_ICONEXCLAMATION);
		}
	}
	catch(...)
	{
		::MessageBox(NULL, _T("数据库连接出现异常"), _T("错误"),MB_ICONEXCLAMATION);
	}

}

CDb::~CDb(void)
{
	//if(m_rs!=NULL)
	m_rs->Close();
	m_rs.Release();
	m_conn->Close();
	m_conn.Release();
	::CoUninitialize();
}
_RecordsetPtr CDb::GetRs(CString strSql)
{
	try
	{
		m_rs.CreateInstance("ADODB.Recordset");
		m_rs=m_conn->Execute((_bstr_t)strSql,NULL,adCmdText);
	}
	catch(...)
	{
		return NULL;
	}
	return m_rs;
}
string CDb::getByfield(string table,string id,string field){
	string sql="select top 1 "+field+" from "+table+" where id="+id;
	GetRs(CString(sql.c_str()));
	if(m_rs){
		string str=(LPCTSTR)(_bstr_t)(m_rs->Fields->GetItem(field.c_str())->Value);
		return str;
	}else{
		return NULL;
	}
}
bool CDb::ExecuteSql(CString& strSql)
{
	try
	{
		m_conn->Execute((_bstr_t)strSql,NULL,adCmdText);
		return true;
	}
	catch(...)
	{
		return false;
	}
}