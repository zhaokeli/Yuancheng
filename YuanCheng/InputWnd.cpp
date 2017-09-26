#include "InputWnd.h"
#include "Db.h"
#include "MyString.h"

CInputWnd::CInputWnd(void)
{
}

CInputWnd::~CInputWnd(void)
{
}

void CInputWnd::init() {
	m_pCloseBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_close")));
	m_pIp = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("ip")));
	m_pPort = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("port")));
	m_pUname = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("username")));
	m_pPwd = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("pwd")));
	m_pNote = static_cast<CRichEditUI*>(m_PaintManager.FindControl(_T("note")));
}
void CInputWnd::OnClick(TNotifyUI & msg)
{
	CDuiString sName = msg.pSender->GetName();
	sName.MakeLower();

	if (msg.pSender == m_pCloseBtn) {
		Close(0);
		return;
	}
	else if (sName == _T("btn_ok")) {
		BtnOkClick();
	}
}

void CInputWnd::BtnOkClick() {
	string ip, port, uname, pwd, note;
	ip = string(m_pIp->GetText());
	port = string(m_pPort->GetText());
	uname = string(m_pUname->GetText());
	pwd = string(m_pPwd->GetText());
	note = string(m_pNote->GetText());
	if (ip == "" || port == "" || uname == "" || pwd == "")
	{
		::MessageBox(NULL, "信息不能为空", "提醒", NULL);
		return;
	}
	//加密
	const char* key = "adminrootkl";
	CMyString* temstr = new CMyString;
	ip = temstr->enString(ip.c_str(), key);
	port = temstr->enString(port.c_str(), key);
	uname = temstr->enString(uname.c_str(), key);
	pwd = temstr->enString(pwd.c_str(), key);
	//note=temstr->enString(note.c_str(),key);

	CDb* db = new CDb;
	string sql = "insert into list([ip],[port],[uname],[pwd],[note]) values('" + ip + "','" + port + "','" + uname + "','" + pwd + "','" + note + "')";
	bool result = db->ExecuteSql(CString(sql.c_str()));
	if (result)
	{
		::MessageBox(NULL, "添加成功", "提醒", NULL);
	}
	else
	{
		::MessageBox(NULL, "添加失败", "提醒", NULL);
	}
	this->Close();
}
CDuiString CInputWnd::GetSkinFile()
{
	return "input.xml";
}

LRESULT CInputWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	//	
	//	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	//	styleValue &= ~WS_CAPTION;
	//	::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
	//	CWndShadow *m_WndShadow=new CWndShadow;
	//	m_WndShadow->Create(m_hWnd);
	//	m_WndShadow->SetSize(8);
	//	m_WndShadow->SetPosition(1,1);
	//	//使用xml界面
	//	m_PaintManager.Init(m_hWnd);
	//	CDialogBuilder builder;
	//	CControlUI* pRoot = builder.Create(_T("input.xml"), (UINT)0, NULL, &m_PaintManager);
	//	ASSERT(pRoot && "Failed to parse XML");
	//	m_PaintManager.AttachDialog(pRoot);
	//	m_PaintManager.AddNotifier(this);
	//	
	//	init();
	//	return 0;
	BaseWnd::OnCreate(uMsg, wParam, lParam, bHandled);
	init();
	return bHandled;
}
