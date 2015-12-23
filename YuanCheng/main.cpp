#pragma once 
#include "FrameWindowWnd.h"

// 程序入口及Duilib初始化部分
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
//创建命名信标对象。 
HANDLE hSem=CreateSemaphore(NULL,1,1,"重复运行标记"); 
if(hSem) //信标对象创建成功。 
{ 
	//信标对象已经存在，则程序已有一个实例在运行。 
	if(ERROR_ALREADY_EXISTS==GetLastError()) 
	{ 
		CloseHandle(hSem); //关闭信号量句柄。 

		//获取桌面窗口的一个子窗口。 
		HWND hWndPrev=::GetWindow(::GetDesktopWindow(),GW_CHILD); 

		while(::IsWindow(hWndPrev)) 
		{ 
			//判断窗口是否有我们预先设置的标记，如有，则是我们寻找的窗口，并将它激活。 
			if(::GetProp(hWndPrev,"重复运行标记")) 
			{ 
			//如果主窗口已最小化，则恢复其大小。 
			if (::IsIconic(hWndPrev)) 
				::ShowWindow(hWndPrev,SW_RESTORE); 

				//将应用程序的主窗口激活。 
				::SetForegroundWindow(hWndPrev); 
				return FALSE; //退出实例。
			}
			//继续寻找下一个窗口。 
			hWndPrev = ::GetWindow(hWndPrev,GW_HWNDNEXT); 
		}
	}
}

//初始化一个窗口
CWndShadow::Initialize(hInstance);

    CPaintManagerUI::SetInstance(hInstance);
    CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath()+_T(".//skin"));
	//CPaintManagerUI::SetResourceZip("skin.zip");

    CFrameWindowWnd* pFrame = new CFrameWindowWnd();
    if( pFrame == NULL ) return 0;
    //pFrame->Create(NULL, _T("测试"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);//窗口可最大化

	pFrame->Create(NULL, _T("远程桌面管理工具"), UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE);//窗口不可最大化
	//LONG styleValue = ::GetWindowLong(*pFrame, GWL_STYLE);
	//styleValue &= ~WS_CAPTION;
	//::SetWindowLong(*pFrame, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

    //pFrame->ShowWindow(true);
	pFrame->CenterWindow();
    CPaintManagerUI::MessageLoop();
	::CoUninitialize();
    return 0;
}

