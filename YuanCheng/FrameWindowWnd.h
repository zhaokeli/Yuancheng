#ifndef _FRAMEWINDOWWND_H
#define _FRAMEWINDOWWND_H
#include "BaseWnd.h"
#include "ListIp.h"
class CFrameWindowWnd: public BaseWnd
{
private:
	CLabelUI*  m_pTitleLab;
	CButtonUI* m_pCloseBtn;
	CButtonUI* m_pMinBtn;

	CListIp* m_pIplist;
	CButtonUI* m_pConbtn;
	CButtonUI* m_pAddbtn;
	CButtonUI* m_pModbtn;
	CButtonUI* m_pDelbtn;
	CRichEditUI* m_pNote;
	CTextUI* m_pText;
	//CWndShadow *m_WndShadow;

	//CButtonUI* m_pGetUrlContentBtn;
	//CButtonUI* m_pPostBtn;

	//CEditUI* m_pUrlText;
	//CRichEditUI* m_pPageCodeRdt;
	//CRichEditUI* m_pPostDataRdt;
public:
	CFrameWindowWnd();
	~CFrameWindowWnd();
	//UILIB_RESOURCETYPE GetResourceType();
	//UINT GetClassStyle() const;
	//LPCTSTR GetWindowClassName() const;
	//void OnFinalMessage(HWND /*hWnd*/) ;
	void init();
	//初始化服务器列表
	void initList();

	 LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam,BOOL& bHandled);
	 LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam);
	 LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	 LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	 LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	 LRESULT OnSetText(UINT uMsg, WPARAM wParam, LPARAM lParam);
	 LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	 LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	 void Notify(TNotifyUI& msg);
	 static DWORD WINAPI GetUrlContent(LPVOID lpParameter);
	 //生成加密密码
	 string edcodePwd(string pwd);



private:
	void BtnAddClick(TNotifyUI& msg);
	void BtnDelClick(TNotifyUI& msg);
	void BtnModClick(TNotifyUI& msg);
	void BtnConClick(TNotifyUI& msg);

	void ItemSelectClick(TNotifyUI& msg);

	virtual CDuiString GetSkinFile() override;

	//virtual CDuiString GetSkinFolder() override;

	//virtual UILIB_RESOURCETYPE GetResourceType() const override;

	//virtual LPCTSTR GetResourceID() const override;



	// 通过 WindowImplBase 继承
	virtual LPCTSTR GetWindowClassName(void) const override;

};

#endif