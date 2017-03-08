#pragma once
// ADOConn.h: interface for the CADOConn class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ADOCONN_H__6FC87078_9BAB_4B1F_B205_E932FD387E09__INCLUDED_)
#define AFX_ADOCONN_H__6FC87078_9BAB_4B1F_B205_E932FD387E09__INCLUDED_

//#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename ("EOF", "adoEOF")
#import "C:\\Program Files\\Common Files\\System\\ado\\msado15.dll" no_namespace rename("EOF","adoEOF")

#define ado_Field_Str 202
#define ado_Field_Text 203
#define ado_Field_Int 2
#define ado_Field_Long 3
#define ado_Field_Float 4
#define ado_Field_Double 5
#define ado_Field_Date 7
#define ado_Field_Byte 17


#ifdef _DEBUG
#define ASSERT_VALID_STRING( str ) ASSERT( !IsBadStringPtr( str, 0xfffff ) )
#else	//	_DEBUG
#define ASSERT_VALID_STRING( str ) ( (void)0 )
#endif	//	_DEBUG

class CADOConn
{
public:
	_ConnectionPtr m_pConnection;
	_RecordsetPtr m_pRecordset;
	_bstr_t m_strDatabaseName;
	int m_iDatabaseType;

	CADOConn();
	CADOConn(CString m_strDatabaseName);
	virtual ~CADOConn();
	CString GetAppPath();
	void InitCADOConn();
	void ExitConnect();
	_RecordsetPtr& GetRecordSet(CString strSQL);
	BOOL Open(CString strSQL);
	BOOL ExecuteSQL(CString strSQL);
	BOOL MoveFirst();
	BOOL MoveNext();
	CString GetItemString(int index);
	int GetItemInt(int index);
	long GetItemLong(int index);
	BOOL adoEOF();
	CString GetFieldName(int index);
	int GetFieldsCount();
	long GetRecordCount();
	//BOOL InitList(CListCtrl *listMain);
	//BOOL FillList(CListCtrl *listMain);
};

#endif // !defined(AFX_ADOCONN_H__6FC87078_9BAB_4B1F_B205_E932FD387E09__INCLUDED_)


