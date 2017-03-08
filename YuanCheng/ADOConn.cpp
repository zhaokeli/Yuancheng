
// ADOConn.cpp: implementation of the CADOConn class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ADOConn.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CADOConn::CADOConn()
{
	//数据库类型：Access
	m_iDatabaseType = 1;
	m_strDatabaseName = _bstr_t("./data/data.mdb");
}

CADOConn::~CADOConn()
{

}

/************************************************************************
函数名:  CADOConn
作  者:	 谭友亮(Charles Tan)
日  期:	 2013-3-5
作  用:  将数据库名称传递给m_strDatabaseName,并判断数据库类型
形参数:  strDatabaseName 数据库名称
返回值:
修改记录:
************************************************************************/
CADOConn::CADOConn(CString strDatabaseName)
{
	CString strFormat;
	strDatabaseName.TrimLeft();
	strDatabaseName.TrimRight();
	m_strDatabaseName = _bstr_t(strDatabaseName);
	strFormat = strDatabaseName.Right(strDatabaseName.GetLength() - strDatabaseName.ReverseFind('.') - 1);

	if (strFormat == "mdb")
	{
		m_iDatabaseType = 1;
	}
	if (strFormat == "xls" || strFormat == "xlsx")
	{
		m_iDatabaseType = 2;
	}
}

/************************************************************************
函数名:  GetAppPath
作  者:	 谭友亮(Charles Tan)
日  期:	 2013-3-18
作  用:  获取当前程序的可执行文件所在的目录
形参数:
返回值:
修改记录:
************************************************************************/
CString CADOConn::GetAppPath()
{
	char lpFilePath[MAX_PATH];
	CString strPath;

	GetModuleFileName(::GetModuleHandle(NULL), lpFilePath, MAX_PATH);
	strPath = lpFilePath;
	strPath = strPath.Left(strPath.ReverseFind('\\'));

	return strPath;
}

/************************************************************************
函数名:  InitCADOConn
作  者:	 谭友亮(Charles Tan)
日  期:	 2013-3-5
作  用:  初始化数据库连接
形参数:
返回值:
修改记录:
************************************************************************/
void CADOConn::InitCADOConn()
{
	CString toolPath = GetAppPath();

	//初始化OLE/COM库环境
	::CoInitialize(NULL);
	try
	{
		m_pConnection = NULL;
		m_pRecordset = NULL;
		//创建Connection对象
		m_pConnection.CreateInstance("ADODB.Connection");
		//设置连接字符串，必须是BSTR型或者_bstr_t类型
		_bstr_t strConnect;

		switch (m_iDatabaseType)
		{
		case 1://ACCESS
			strConnect = _bstr_t("Provider = Microsoft.Jet.OLEDB.4.0;Data Source = ");
			strConnect = strConnect + _bstr_t(toolPath) + _bstr_t("\\data\\") + m_strDatabaseName;
			break;
		case 2://EXCEL
			strConnect = _bstr_t("Provider = Microsoft.Jet.OLEDB.4.0;Data Source = ");
			strConnect = strConnect + _bstr_t(toolPath) + _bstr_t("\\") + m_strDatabaseName;
			strConnect = strConnect + ";Extended Properties=Excel 8.0";
			break;
		case 3://SQL SERVER
			strConnect = _bstr_t("Provider = Microsoft.Jet.OLEDB.4.0;Data Source = ");
			strConnect = strConnect + _bstr_t(toolPath) + _bstr_t("\\") + m_strDatabaseName;
			strConnect = strConnect + ";Extended Properties=Excel 8.0";
			break;
		}

		m_pConnection->Open(strConnect, _bstr_t(""), _bstr_t(""), adModeUnknown);
		//ShellExecute(NULL, _T("open"), toolPath + "\\" + m_strDatabaseName, NULL, NULL, SW_SHOWMAXIMIZED);
	}
	catch (_com_error e)
	{
		::MessageBox(NULL, e.Description(), "错误", MB_ICONEXCLAMATION);
	}
}

/************************************************************************
函数名:  GetRecordSet
作  者:	 谭友亮(Charles Tan)
日  期:	 2013-3-5
作  用:  执行查询
形参数:  strSQL SQL语句
返回值:  m_pRecordset 字段集的指针
修改记录:
************************************************************************/
_RecordsetPtr& CADOConn::GetRecordSet(CString strSQL)
{
	try
	{
		//连接数据库，如果Connection对象为空，则重新连接数据库
		if (m_pConnection == NULL)
		{
			InitCADOConn();
		}

		strSQL.TrimLeft();
		strSQL.TrimRight();
		//创建记录集对象
		m_pRecordset.CreateInstance(__uuidof(Recordset));
		//取得表中的记录
		m_pRecordset->Open(_bstr_t(strSQL), m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
		return m_pRecordset;
	}
	catch (_com_error e)
	{
		::MessageBox(NULL, e.Description(), "错误", MB_ICONEXCLAMATION);
	}

	return m_pRecordset;
}

/************************************************************************
函数名:  Open
作  者:	 谭友亮(Charles Tan)
日  期:	 2013-3-5
作  用:  打开字符集
形参数:  strSQL SQL语句
返回值:  TRUE:成功 FALSE:失败
修改记录:
************************************************************************/
BOOL CADOConn::Open(CString strSQL)
{
	try
	{
		//连接数据库，如果Connection对象为空，则重新连接数据库
		if (m_pConnection == NULL)
		{
			InitCADOConn();
		}

		strSQL.TrimLeft();
		strSQL.TrimRight();
		//创建记录集对象
		m_pRecordset.CreateInstance(__uuidof(Recordset));
		//取得表中的记录
		m_pRecordset->Open(_bstr_t(strSQL), m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
	}
	catch (_com_error e)
	{
		::MessageBox(NULL, e.Description(), "错误", MB_ICONEXCLAMATION);
		return FALSE;
	}

	return TRUE;
}

/************************************************************************
函数名:  ExecuteSQL
作  者:	 谭友亮(Charles Tan)
日  期:	 2013-3-5
作  用:  执行SQL语句(Insert Update delete)
形参数:  strSQL SQL语句
返回值:  TRUE:成功 FALSE:失败
修改记录:
************************************************************************/
BOOL CADOConn::ExecuteSQL(CString strSQL)
{
	try
	{
		//连接数据库，如果Connection对象为空，则重新连接数据库
		if (m_pConnection == NULL)
		{
			InitCADOConn();
		}

		strSQL.TrimLeft();
		strSQL.TrimRight();
		m_pConnection->Execute(_bstr_t(strSQL), NULL, adCmdText);
		return TRUE;
	}
	catch (_com_error e)
	{
		::MessageBox(NULL, e.Description(), "错误", MB_ICONEXCLAMATION);
		return FALSE;
	}
	return TRUE;
}

/************************************************************************
函数名:  MoveFirst
作  者:	 谭友亮(Charles Tan)
日  期:	 2013-3-6
作  用:  记录集移向开头
形参数:
返回值:  TRUE:成功 FALSE:失败
修改记录:
************************************************************************/
BOOL CADOConn::MoveFirst()
{
	if (m_pRecordset == NULL)
	{
		return FALSE;
	}
	else
	{
		m_pRecordset->MoveFirst();
		return TRUE;
	}
}

/************************************************************************
函数名:  MoveNext
作  者:	 谭友亮(Charles Tan)
日  期:	 2013-3-6
作  用:  记录集向下移动
形参数:
返回值:  TRUE:成功 FALSE:失败
修改记录:
************************************************************************/
BOOL CADOConn::MoveNext()
{
	if (m_pRecordset == NULL)
	{
		return FALSE;
	}
	else
	{
		if (!m_pRecordset->adoEOF)
		{
			m_pRecordset->MoveNext();
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
}

/************************************************************************
函数名:  GetItemString
作  者:	 谭友亮(Charles Tan)
日  期:	 2013-3-6
作  用:  取得字段中的字符串
形参数:  index:字段集中的索引
返回值:
修改记录:
************************************************************************/
CString CADOConn::GetItemString(int index)
{
	_variant_t vValue;
	_variant_t vIndex;
	CString strValue, str;

	if (m_pRecordset == NULL || m_pRecordset->adoEOF)
	{
		return "";
	}

	vIndex.vt = VT_I2;
	vIndex.iVal = index;
	vValue = m_pRecordset->GetCollect(vIndex);
	//	vValue = m_pRecordset->Fields->GetItem(vIndex)->Value;

	switch (vValue.vt)
	{
	case VT_NULL:
		str = "";
		break;
	case VT_ERROR:
		str = "";
		break;
	case VT_EMPTY:
		str = "";
		break;
	default:
		str = (LPCTSTR)_bstr_t(vValue);
	}

	strValue.Format(_T("%s"), str);
	strValue.TrimRight();
	strValue.TrimLeft();

	return strValue;
}

/************************************************************************
函数名:  GetItemInt
作  者:	 谭友亮(Charles Tan)
日  期:	 2013-3-18
作  用:  取得字段中的整数
形参数:  index:字段集中的索引
返回值:
修改记录:
************************************************************************/
int CADOConn::GetItemInt(int index)
{
	_variant_t vValue;
	_variant_t vIndex;
	int iValue;

	if (m_pRecordset == NULL || m_pRecordset->adoEOF)
	{
		exit(1);
	}

	vIndex.vt = VT_I2;
	vIndex.iVal = index;
	vValue = m_pRecordset->GetCollect(vIndex);
	//	vValue = m_pRecordset->Fields->GetItem(vIndex)->Value;

	switch (vValue.vt)
	{
	case VT_NULL:
		iValue = 0;
		break;
	case VT_ERROR:
		iValue = 0;
		break;
	case VT_EMPTY:
		iValue = 0;
		break;
	default:
		iValue = vValue.iVal;
	}

	return iValue;
}

/************************************************************************
函数名:  GetItemLong
作  者:	 谭友亮(Charles Tan)
日  期:	 2013-3-18
作  用:  取得字段中的整数
形参数:  index:字段集中的索引
返回值:
修改记录:
************************************************************************/
long CADOConn::GetItemLong(int index)
{
	long lValue;
	_variant_t vIndex;
	_variant_t vValue;

	vIndex.vt = VT_I2;
	vIndex.iVal = index;
	vValue = m_pRecordset->Fields->GetItem(vIndex)->Value;

	switch (vValue.vt)
	{
	case VT_NULL:
		lValue = 0;
		break;
	case VT_ERROR:
		lValue = 0;
		break;
	case VT_EMPTY:
		lValue = 0;
		break;
	default:
		lValue = vValue.lVal;
	}

	return lValue;
}

/************************************************************************
函数名:  GetFieldName
作  者:	 谭友亮(Charles Tan)
日  期:	 2013-3-6
作  用:  取得列标题
形参数:  index:字段集中的索引,最小值为0
返回值:
修改记录:
************************************************************************/
CString CADOConn::GetFieldName(int index)
{
	_variant_t vIndex;
	CString strFieldName;

	if (index < m_pRecordset->Fields->Count)
	{
		vIndex.vt = VT_I2;
		vIndex.iVal = index;
		strFieldName = (LPCTSTR)m_pRecordset->Fields->GetItem(vIndex)->GetName();
	}
	else
	{
		::MessageBox(NULL,"Invalid index!" , "错误", MB_ICONEXCLAMATION);
	}

	return strFieldName;
}

/************************************************************************
函数名:  GetFieldsCount
作  者:	 谭友亮(Charles Tan)
日  期:	 2013-3-6
作  用:  取得列数
形参数:
返回值:
修改记录:
************************************************************************/
int CADOConn::GetFieldsCount()
{
	int colNum = m_pRecordset->Fields->Count;
	return colNum;
}

/************************************************************************
函数名:  adoEOF
作  者:	 谭友亮(Charles Tan)
日  期:	 2013-3-6
作  用:  判断字段集是否结束
形参数:
返回值:  TRUE:结束 FALSE:未结束
修改记录:
************************************************************************/
BOOL CADOConn::adoEOF()
{
	if (m_pRecordset->adoEOF)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/************************************************************************
函数名:  ExitConnect
作  者:	 谭友亮(Charles Tan)
日  期:	 2013-3-6
作  用:  退出连接
形参数:
返回值:
修改记录:
************************************************************************/
void CADOConn::ExitConnect()
{
	try
	{
		if (m_pRecordset != NULL)
		{
			m_pRecordset->Close();
		}
		if (m_pConnection != NULL)
		{
			m_pConnection->Close();
		}

		m_pRecordset = NULL;
		m_pConnection = NULL;

		//释放OLE/COM库环境
		::CoUninitialize();
	}
	catch (_com_error e)
	{
		::MessageBox(NULL, e.Description(), "错误", MB_ICONEXCLAMATION);

	}
}

/************************************************************************
函数名:  InitList
作  者:	 谭友亮(Charles Tan)
日  期:	 2013-3-19
作  用:  初始化列表
形参数:
返回值:
修改记录:
************************************************************************/
//BOOL CADOConn::InitList(CListCtrl *listMain)
//{
//	int iMaxCol = 0, i;
//	_variant_t vIndex;
//
//	vIndex.vt = VT_I2;
//	iMaxCol = m_pRecordset->Fields->Count;
//	listMain->SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
//
//	for (i = 0; i < iMaxCol; i++)
//	{
//		CString strTitle;
//		vIndex.iVal = i;
//		strTitle = (LPCTSTR)m_pRecordset->Fields->GetItem(vIndex)->GetName();
//		listMain->InsertColumn(i, strTitle, LVCFMT_CENTER, 100, 0);
//	}
//
//	int iWidth = 0;
//	for (i = 0; i < iMaxCol; i++)
//	{
//		listMain->SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
//		iWidth = iWidth + listMain->GetColumnWidth(i);
//	}
//
//	RECT rectList;
//	listMain->GetWindowRect(&rectList);
//	if (iWidth < (rectList.right - rectList.left))
//	{
//		iWidth = (rectList.right - rectList.left - iWidth) / iMaxCol;
//	}
//	else
//	{
//		return TRUE;
//	}
//
//	for (i = 0; i < iMaxCol; i++)
//	{
//		listMain->SetColumnWidth(i, listMain->GetColumnWidth(i) + iWidth);
//	}
//
//	return TRUE;
//}

/************************************************************************
函数名:  FillList
作  者:	 谭友亮(Charles Tan)
日  期:	 2013-3-19
作  用:  填充列表
形参数:
返回值:
修改记录:
************************************************************************/
//BOOL CADOConn::FillList(CListCtrl *listMain)
//{
//
//	int i, iType, iRow = 0, listWidth = 0;//iType:字段集的数据类型 listWidth:列表中列的宽度
//	_variant_t vIndex;
//	long lMax = 0;
//	lMax = m_pRecordset->Fields->Count;
//	vIndex.vt = VT_I2;
//	if (!m_pRecordset->adoEOF)
//	{
//		MoveFirst();
//		while (!m_pRecordset->adoEOF)
//		{
//			for (i = 0; i<lMax; i++)
//			{
//				CString strValue = "";
//				vIndex.iVal = i;
//				iType = m_pRecordset->Fields->GetItem(vIndex)->GetType();
//				switch (iType)
//				{
//				case ado_Field_Str:
//				case ado_Field_Text:
//					strValue = GetItemString(i);
//					break;
//				case ado_Field_Long:
//					strValue.Format(_T("%d"), GetItemLong(i));
//					break;
//				case ado_Field_Int:
//					strValue.Format(_T("%d"), GetItemInt(i));
//					break;
//					//				case ado_Field_Float:
//					//					strValue=GetValueFloatStr(i,0,2);
//					//					break;
//					//				case ado_Field_Double:
//					//					strValue=GetValueDoubleStr(i,0,2);
//					//					break;
//					//				case ado_Field_Byte:
//					//					strValue=GetValueByteStr(i,0);
//					//					break;
//				case ado_Field_Date:
//					strValue = GetItemString(i);
//					break;
//				default:
//					strValue = "";
//					break;
//				}
//
//				if (i == 0)
//					listMain->InsertItem(iRow, strValue, 0);
//				else
//					listMain->SetItemText(iRow, i, strValue);
//			}
//			m_pRecordset->MoveNext();
//		}
//		//移向开头
//		MoveFirst();
//	}
//
//	return TRUE;
//}