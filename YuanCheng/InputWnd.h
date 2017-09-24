#pragma once
#include "stdafx.h"
#include "BaseWnd.h"
class CInputWnd :public BaseWnd
{
public:
	CInputWnd(void);
	~CInputWnd(void);
private:
	CEditUI* m_pIp;
	CEditUI* m_pPort;
	CEditUI* m_pUname;
	CEditUI* m_pPwd;
	CRichEditUI* m_pNote;
	void init();
public:
	//LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void Notify(TNotifyUI& msg);
	//添加一条信息
	void BtnOkClick();
	// 通过 BaseWnd 继承
	virtual CDuiString GetSkinFile() override;

	virtual LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;


	//virtual LPCTSTR GetWindowClassName(void) const override;

};