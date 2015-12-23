#pragma once
#include "stdafx.h"
class CInputWnd :public CWindowWnd, public INotifyUI
{
public:
	CInputWnd(void);
	~CInputWnd(void);
private:
	CPaintManagerUI m_pm;
	CEditUI* m_pIp;
	CEditUI* m_pPort;
	CEditUI* m_pUname;
	CEditUI* m_pPwd;
	CRichEditUI* m_pNote;


	void init();
public:
	UINT GetClassStyle() const;
	LPCTSTR GetWindowClassName() const;
	void OnFinalMessage(HWND /*hWnd*/) ;

	LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void Notify(TNotifyUI& msg);
	//添加一条信息
	void BtnOkClick();
};