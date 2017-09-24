#include "InputWnd.h"
#include "Db.h"
#include "MyString.h"

CInputWnd::CInputWnd(void)
{
}

CInputWnd::~CInputWnd(void)
{
}
//LPCTSTR CInputWnd::GetWindowClassName() const { return _T("UIMainFrame"); };
//UINT CInputWnd::GetClassStyle() const { return UI_CLASSSTYLE_FRAME | CS_DBLCLKS; };
//void CInputWnd::OnFinalMessage(HWND /*hWnd*/) { delete this; };

void CInputWnd::init() {
	m_pIp = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("ip")));
	m_pPort = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("port")));
	m_pUname = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("username")));
	m_pPwd = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("pwd")));
	m_pNote = static_cast<CRichEditUI*>(m_PaintManager.FindControl(_T("note")));
}

void CInputWnd::Notify(TNotifyUI& msg)
{
	try
	{
		string msgname = msg.pSender->GetName();
		if (msg.sType == _T("click")) {
			if (msgname == _T("btn_cancel") || msgname == _T("btn_close")) {
				this->Close();
			}
			else if (msgname == _T("btn_ok"))
			{
				BtnOkClick();
			}
		}
	}
	catch (...) {

	}
}
LRESULT CInputWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	BOOL bHandled = true;//true处理完后直接返回false为传给父类处理
	LRESULT lRes = 0;
	switch (uMsg)
	{
	case WM_CREATE:
		lRes = OnCreate(uMsg, wParam, lParam, bHandled);
		break;
	case WM_DESTROY:
		::PostQuitMessage(0);
		break;
	case WM_NCACTIVATE:
		if (!::IsIconic(m_hWnd)) {
			return (wParam == 0) ? TRUE : FALSE;
		}
		break;
	case  WM_NCCALCSIZE:
		return 0;
		break;
	case WM_NCHITTEST:
		lRes=OnNcHitTest(uMsg, wParam, lParam, bHandled);
		break;
	default:
		bHandled = FALSE;
	}
	if (bHandled)  return lRes;
	if (m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes)) return lRes;
	return BaseWnd::HandleMessage(uMsg, wParam, lParam);
}

LRESULT CInputWnd::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT pt; pt.x = GET_X_LPARAM(lParam); pt.y = GET_Y_LPARAM(lParam);
	::ScreenToClient(*this, &pt);

	RECT rcClient;
	::GetClientRect(*this, &rcClient);

	if (!::IsZoomed(*this)) {
		RECT rcSizeBox = m_PaintManager.GetSizeBox();    // GetSizeBox用来获取xml中Window标签的sizebox属性，该属性指示你的鼠标移动到窗口边框多少个像素会变成指示符（这个指示符表示可以改变窗口大小的指示符）
		if (pt.y < rcClient.top + rcSizeBox.top) {
			if (pt.x < rcClient.left + rcSizeBox.left) return HTTOPLEFT;
			if (pt.x > rcClient.right - rcSizeBox.right) return HTTOPRIGHT;
			return HTTOP;
		}
		else if (pt.y > rcClient.bottom - rcSizeBox.bottom) {
			if (pt.x < rcClient.left + rcSizeBox.left) return HTBOTTOMLEFT;
			if (pt.x > rcClient.right - rcSizeBox.right) return HTBOTTOMRIGHT;
			return HTBOTTOM;
		}
		if (pt.x < rcClient.left + rcSizeBox.left) return HTLEFT;
		if (pt.x > rcClient.right - rcSizeBox.right) return HTRIGHT;
	}
	RECT rcCaption = m_PaintManager.GetCaptionRect();    // GetCaptionRect用来获取xml中Window标签的caption属性，该属性指示标题栏的大小
	if (pt.x >= rcClient.left + rcCaption.left && pt.x < rcClient.right - rcCaption.right && pt.y >= rcCaption.top && pt.y < rcCaption.bottom) {
		CControlUI* pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(pt));
		if (pControl && _tcsicmp(pControl->GetClass(), _T("ButtonUI")) != 0 && _tcsicmp(pControl->GetClass(), _T("OptionUI")) != 0)
			return HTCAPTION;
	}

	return HTCLIENT;
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
