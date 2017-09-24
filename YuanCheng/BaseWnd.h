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
class BaseWnd: public WindowImplBase
{
public:
	BaseWnd(void);
	~BaseWnd(void);
	//返回加载皮肤的方法是zip压缩包还是文件夹还是zip资源
	UILIB_RESOURCETYPE GetResourceType() const;
	//如果是皮肤是zip资源就返回资源id
	LPCTSTR GetResourceID() const;
	UINT GetClassStyle() const;
	LPCTSTR GetWindowClassName() const;
	void OnFinalMessage(HWND /*hWnd*/);

	// 通过 WindowImplBase 继承
	virtual CDuiString GetSkinFolder() override;
	//下面保留纯虚函数要求子类一定要实现返回xml文件
	//virtual CDuiString GetSkinFile() override;
};

#endif