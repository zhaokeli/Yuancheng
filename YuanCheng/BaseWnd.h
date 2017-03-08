#pragma once
#include "stdafx.h"



#ifndef  _BASEWND_H_ 
#define  _BASEWND_H_

struct SetCText{
	HWND m_hwnd;
	CControlUI* m_pcontrol;
	CString m_settext;
};
struct Prama
{
	HWND m_hwnd;
	CString postdata;
	CString m_settext;
	int requesttype;
	CLabelUI* plab;
	CRichEditUI* prdt;
	CString url;
	CRichEditUI* pPostdata;

};
class BaseWnd: public CWindowWnd, public INotifyUI
{
public:
	BaseWnd(void);
	~BaseWnd(void);
	UINT GetClassStyle() const;
	LPCTSTR GetWindowClassName() const;
	void OnFinalMessage(HWND /*hWnd*/);

protected:

};

#endif