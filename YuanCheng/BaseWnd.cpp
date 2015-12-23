#include "BaseWnd.h"

LPCTSTR BaseWnd::GetWindowClassName() const { return _T("AINIKUUIFRAME"); };

UINT BaseWnd::GetClassStyle() const { return UI_CLASSSTYLE_FRAME | CS_DBLCLKS; };

void BaseWnd::OnFinalMessage(HWND /*hWnd*/) { delete this; };

BaseWnd::BaseWnd(void)
{
}


BaseWnd::~BaseWnd(void)
{
}
