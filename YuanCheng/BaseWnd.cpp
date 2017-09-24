#include "BaseWnd.h"
#include "resource.h"
LPCTSTR BaseWnd::GetWindowClassName() const { return _T("AINIKUUIFRAME"); };

UINT BaseWnd::GetClassStyle() const { return UI_CLASSSTYLE_FRAME | CS_DBLCLKS; };

void BaseWnd::OnFinalMessage(HWND /*hWnd*/) { delete this; }


BaseWnd::BaseWnd(void)
{
}


BaseWnd::~BaseWnd(void)
{
}
CDuiString BaseWnd::GetSkinFolder()
{
	return "skin";
}
UILIB_RESOURCETYPE BaseWnd::GetResourceType()  const {
	return UILIB_FILE;
	//下面是资源zip文件,调试期间用上面那个就可以
	//return UILIB_ZIPRESOURCE;
}
LPCTSTR BaseWnd::GetResourceID() const
{
	return MAKEINTRESOURCE(IDR_ZIPRES1);
}