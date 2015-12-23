#include "FrameWindowWnd.h"
#include "InputWnd.h"
#include "Db.h"
//创建一个互斥对象  
#define  WM_USER_SETTEXT WM_USER+2//设置文本消息
Mutex g_Lock;  
CInputWnd * pinputmsg;
//当前选中的服务器列表项目
ServerInfo *selectedItem=new ServerInfo;
CFrameWindowWnd::CFrameWindowWnd()
{
	selectedItem->index=-1;
}

CFrameWindowWnd::~CFrameWindowWnd()
{
}

LPCTSTR CFrameWindowWnd::GetWindowClassName() const { return _T("UIMainFrame"); };

UINT CFrameWindowWnd::GetClassStyle() const { return UI_CLASSSTYLE_FRAME | CS_DBLCLKS; };

void CFrameWindowWnd::OnFinalMessage(HWND /*hWnd*/) { delete this; };

void CFrameWindowWnd::init()
{
	m_pTitleLab= static_cast<CLabelUI*>(m_pm.FindControl(_T("wintitle")));
	m_pCloseBtn= static_cast<CButtonUI*>(m_pm.FindControl(_T("btn_close")));
	m_pMinBtn= static_cast<CButtonUI*>(m_pm.FindControl(_T("btn_min")));

	m_pConbtn= static_cast<CButtonUI*>(m_pm.FindControl(_T("btn_con")));
	m_pAddbtn= static_cast<CButtonUI*>(m_pm.FindControl(_T("btn_add")));
	m_pModbtn= static_cast<CButtonUI*>(m_pm.FindControl(_T("btn_set")));
	m_pDelbtn= static_cast<CButtonUI*>(m_pm.FindControl(_T("btn_del")));

	m_pIplist= static_cast<CListIp*>(m_pm.FindControl(_T("iplist")));
	m_pNote= static_cast<CRichEditUI*>(m_pm.FindControl(_T("note")));


	//初始化服务器数据列表
	initList();
	//m_pGetUrlContentBtn= static_cast<CButtonUI*>(m_pm.FindControl(_T("btn_guc")));
	//m_pPostBtn= static_cast<CButtonUI*>(m_pm.FindControl(_T("btn_post")));
	//m_pUrlText= static_cast<CEditUI*>(m_pm.FindControl(_T("urltext")));	
	//m_pPageCodeRdt= static_cast<CRichEditUI*>(m_pm.FindControl(_T("pagecode")));
	//m_pPostDataRdt= static_cast<CRichEditUI*>(m_pm.FindControl(_T("postdata")));
}

void CFrameWindowWnd::initList(){
	m_pIplist->RemoveAll();
	CDb* db=new CDb;
	if (db)
	{
		_RecordsetPtr rs= db->GetRs("select * from list");
		if(rs){
			while (!rs->rsEOF)
			{
				CString idstr=(LPCTSTR)(_bstr_t)(rs->Fields->GetItem("id")->Value);
				CString ipstr=(LPCTSTR)(_bstr_t)(rs->Fields->GetItem("ip")->Value);
				CString portstr=(LPCTSTR)(_bstr_t)(rs->Fields->GetItem("port")->Value);
				CString unamestr=(LPCTSTR)(_bstr_t)(rs->Fields->GetItem("uname")->Value);
				CString statusstr=(LPCTSTR)(_bstr_t)(rs->Fields->GetItem("status")->Value);

				int nIndex = m_pIplist->GetCount();
				m_pIplist->InsertItem(nIndex);

				const char* key="adminrootkl";
				CMyString* temstr=new CMyString;
				ipstr=temstr->deString(ipstr.GetBuffer(),key).c_str();
				portstr=temstr->deString(portstr.GetBuffer(),key).c_str();
				unamestr=temstr->deString(unamestr.GetBuffer(),key).c_str();
				//pwd=temstr->deString(pwd.c_str(),key);
				//note=temstr->deString(note.c_str(),key);


				CString idname,ipname,portname,unamename,statusname;
				idname.Format("id%lu",nIndex);
				ipname.Format("ip%lu",nIndex);
				portname.Format("port%lu",nIndex);
				unamename.Format("uname%lu",nIndex);
				statusname.Format("statusname%lu",nIndex);

				m_pIplist->SetItemData(nIndex, 0, idstr, idname);
				m_pIplist->SetItemData(nIndex, 1, statusstr,statusname);
				m_pIplist->SetItemData(nIndex, 2, ipstr, ipname);
				m_pIplist->SetItemData(nIndex, 3, portstr, portname);
				m_pIplist->SetItemData(nIndex, 4, unamestr, unamename);
				
				//if (pList->GetHeader()->GetCount() > 3)
				//{
				//	pList->SetItemData(nIndex, 3, "新增列数据", "testid1");
				//}
				rs->MoveNext();
			}
		}
	}
}

DWORD WINAPI CFrameWindowWnd::GetUrlContent(LPVOID lpParameter){
	try{
		return 0;
	}catch(...){
		return 0;
	}
}

void CFrameWindowWnd::Notify(TNotifyUI& msg)
{
	try
	{

	if( msg.sType == _T("click") ) {
			if( msg.pSender->GetName() == _T("btn_close") ) {
				Close();
			}else if( msg.pSender->GetName() == _T("btn_min") ) {
				SendMessage(WM_SYSCOMMAND,SC_MINIMIZE,0);
				return;
			}else if( msg.pSender->GetName() == _T("btn_con") ) {
				BtnConClick(msg);
			}else if( msg.pSender->GetName() == _T("btn_add") ) {
				BtnAddClick(msg);
			}else if( msg.pSender->GetName() == _T("btn_del") ) {
				BtnDelClick(msg);
			}else if( msg.pSender->GetName() == _T("btn_mod") ) {
				BtnModClick(msg);
			}
		}else if(msg.sType=="itemselect"){
			ItemSelectClick(msg);
		}
	}
	catch (CException* e)
	{
		TCHAR err[1024];
		e->GetErrorMessage(err,1024);
		MyLog::WriteLog(err);
	}
}

LRESULT CFrameWindowWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{


	LRESULT lRes=0;
	BOOL bHandled=TRUE; 
	switch(uMsg)  
	{  
	case WM_CREATE:        lRes=OnCreate(uMsg,wParam,lParam);break;  
		//能去除边框  
	case WM_NCCALCSIZE:    return 0;break;  
		//去除显示的标题栏  
	case WM_SIZE:          lRes=OnSize(uMsg,wParam,lParam,bHandled);break;  
		//解决按住左键或右键时会出现边框的问题  
	case WM_NCACTIVATE:    lRes = OnNcActivate(uMsg, wParam, lParam, bHandled); break;  
		//实现按住窗口（除按钮外）拖动窗口  
	case WM_NCHITTEST:     lRes=OnNcHitTest(uMsg,wParam,lParam,bHandled);break;  
		//获取边框最大最小值  
	case WM_GETMINMAXINFO: lRes=OnGetMinMaxInfo(uMsg,wParam,lParam,bHandled);break; 
	

	case WM_DESTROY: lRes=OnDestroy(uMsg,wParam,lParam);break; 
	
	case WM_USER_SETTEXT: OnSetText(uMsg,wParam,lParam);break; 

	default:               bHandled=FALSE;  
	}  

	if(bHandled)  
		return lRes;  
	if(m_pm.MessageHandler(uMsg,wParam,lParam,lRes))  
		return lRes;  
	return CWindowWnd::HandleMessage(uMsg,wParam,lParam);  

}

LRESULT CFrameWindowWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam){
		LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
	 CWndShadow *m_WndShadow=new CWndShadow;
        m_WndShadow->Create(m_hWnd);
	m_WndShadow->SetSize(8);
	m_WndShadow->SetPosition(1,1);


	//设置程序运行标记
	::SetProp(m_hWnd,"重复运行标记",(HANDLE)1); 
	//使用xml界面
	m_pm.Init(m_hWnd);
	CDialogBuilder builder;
	CControlUI* pRoot=NULL;
	pRoot= builder.Create(_T("main.xml"), (UINT)0, NULL, &m_pm);
	ASSERT(pRoot && "Failed to parse XML");
	m_pm.AttachDialog(pRoot);
	m_pm.AddNotifier(this);
	init();
	return 0;
}

LRESULT CFrameWindowWnd::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam){
		//移除生成的临时文件
		remove("tem.tmp");
		//移除标记
		::RemoveProp(m_hWnd,"重复运行标记"); 
		::PostQuitMessage(0);
		return 0;
}

LRESULT CFrameWindowWnd::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT pt; pt.x = GET_X_LPARAM(lParam); pt.y = GET_Y_LPARAM(lParam);
	::ScreenToClient(*this, &pt);

	RECT rcClient;
	::GetClientRect(*this, &rcClient);

	if( !::IsZoomed(*this) ) {
		RECT rcSizeBox = m_pm.GetSizeBox();    // GetSizeBox用来获取xml中Window标签的sizebox属性，该属性指示你的鼠标移动到窗口边框多少个像素会变成指示符（这个指示符表示可以改变窗口大小的指示符）
		if( pt.y < rcClient.top + rcSizeBox.top ) {
			if( pt.x < rcClient.left + rcSizeBox.left ) return HTTOPLEFT;
			if( pt.x > rcClient.right - rcSizeBox.right ) return HTTOPRIGHT;
			return HTTOP;
		}
		else if( pt.y > rcClient.bottom - rcSizeBox.bottom ) {
			if( pt.x < rcClient.left + rcSizeBox.left ) return HTBOTTOMLEFT;
			if( pt.x > rcClient.right - rcSizeBox.right ) return HTBOTTOMRIGHT;
			return HTBOTTOM;
		}
		if( pt.x < rcClient.left + rcSizeBox.left ) return HTLEFT;
		if( pt.x > rcClient.right - rcSizeBox.right ) return HTRIGHT;
	}
	RECT rcCaption = m_pm.GetCaptionRect();    // GetCaptionRect用来获取xml中Window标签的caption属性，该属性指示标题栏的大小
	if( pt.x >= rcClient.left + rcCaption.left && pt.x < rcClient.right - rcCaption.right && pt.y >= rcCaption.top && pt.y < rcCaption.bottom ) {
		CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl(pt));
		if( pControl && _tcsicmp(pControl->GetClass(), _T("ButtonUI")) != 0 && _tcsicmp(pControl->GetClass(), _T("OptionUI")) != 0)
			return HTCAPTION;
	}

	return HTCLIENT;
}

LRESULT CFrameWindowWnd::OnSetText(UINT uMsg, WPARAM wParam, LPARAM lParam){
	SetCText* ct=(SetCText*)wParam;
	//CRichEditUI* m_prdt=(CRichEditUI*)ct->m_pcontrol;
	ct->m_pcontrol->SetText(ct->m_settext);
	return 1;
}

LRESULT CFrameWindowWnd::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)  
{  
	if( !::IsIconic(*this) );
	SIZE szRoundCorner = m_pm.GetRoundCorner();//这个是圆角，是椭圆的半径  
	//这里有个很巧妙的用法，在xml文件中一定要设置圆角（roundcorner），  
	//不然不会进入下面的if，也就会出现标题栏。  
	if( !::IsIconic(*this) && (szRoundCorner.cx != 0 || szRoundCorner.cy != 0) ) {  
		CRect rcWnd;  
		::GetWindowRect(*this, &rcWnd);  
		//rcWnd.Offset(-rcWnd.left, -rcWnd.top);  
		rcWnd.right++; rcWnd.bottom++;  
		RECT rc = { rcWnd.left, rcWnd.top + szRoundCorner.cx, rcWnd.right, rcWnd.bottom };  
		HRGN hRgn1 = ::CreateRectRgnIndirect( &rc );  
		HRGN hRgn2 = ::CreateRoundRectRgn(rcWnd.left, rcWnd.top, rcWnd.right, rcWnd.bottom - szRoundCorner.cx, szRoundCorner.cx, szRoundCorner.cy);  
		::CombineRgn( hRgn1, hRgn1, hRgn2, RGN_OR );  
		::SetWindowRgn(*this, hRgn1, TRUE);  
		::DeleteObject(hRgn1);  
		::DeleteObject(hRgn2);  
	}  

	bHandled = FALSE;  
	return 0;  
}  

LRESULT CFrameWindowWnd::OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled){
	if( ::IsIconic(*this) ) bHandled = FALSE;  
	return (wParam == 0) ? TRUE : FALSE;  
}

LRESULT CFrameWindowWnd::OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled){
	MONITORINFO oMonitor = {};  
	oMonitor.cbSize = sizeof(oMonitor);  
	::GetMonitorInfo(::MonitorFromWindow(*this, MONITOR_DEFAULTTOPRIMARY), &oMonitor);  
	CRect rcWork = oMonitor.rcWork;  
	//rcWork.Offset(-rcWork.left, -rcWork.top);  

	LPMINMAXINFO lpMMI = (LPMINMAXINFO) lParam;  
	lpMMI->ptMaxPosition.x   = rcWork.left;  
	lpMMI->ptMaxPosition.y   = rcWork.top;  
	lpMMI->ptMaxSize.x       = rcWork.right;  
	lpMMI->ptMaxSize.y       = rcWork.bottom;  

	bHandled = FALSE;  
	return 0;  
}

string CFrameWindowWnd::edcodePwd(string pw){
	std::wstring wstr(pw.length(),L' ');
	std::copy(pw.begin(), pw.end(), wstr.begin());
	const wchar_t* pwd=wstr.c_str();
	//生成rdp密码
	DATA_BLOB DataIn;
	DATA_BLOB DataOut;
	BYTE *pbDataInput =(BYTE *)pwd;
	DWORD cbDataInput = wcslen((WCHAR *)pbDataInput) * sizeof(WCHAR);

	DataIn.pbData = pbDataInput;    
	DataIn.cbData = cbDataInput;

	if(!CryptProtectData(&DataIn,L"psw",NULL,NULL,NULL,0,&DataOut))
	{
		MyLog::WriteLog("Encryption error using CryptProtectData.\n");
	}
	char dest[1024]={0};
	int count=0;
	while( count <= (int)DataOut.cbData ){
		char t[10] = {0};            	
		sprintf(t,"%02X",DataOut.pbData[count]);
		strcat(dest,t);
		count++;
	}
	return (string)dest;
}

void CFrameWindowWnd::BtnConClick(TNotifyUI& msg){
	if (selectedItem->index==-1)
	{
		::MessageBox(m_hWnd,"请选择一个服务器","提醒",NULL);
		return;
	}
	string key="adminrootkl";//加密key
	string enpwd,ip,username;
	ip=selectedItem->ip+":"+selectedItem->port;
	username=selectedItem->uname;

	//把密码加密
	string pwd=selectedItem->pwd;
	enpwd=edcodePwd(pwd);

	//读配置文件
	CFileIO * fio=new CFileIO;
	//string str=fio->readAll("conf.db");
	CString s;
	s.Format("\
screen mode id:i:1 \n\
desktopwidth:i:1280\n\
desktopheight:i:750\n\
session bpp:i:24\n\
winposstr:s:2,3,188,8,1062,721\n\
full address:s:#ip#\n\
compression:i:1\n\
keyboardhook:i:2\n\
audiomode:i:0\n\
redirectdrives:i:0\n\
redirectprinters:i:0\n\
redirectcomports:i:0\n\
redirectsmartcards:i:0\n\
displayconnectionbar:i:1\n\
autoreconnection enabled:i:1\n\
username:s:#username#\n\
domain:s:\n\
alternate shell:s:\n\
shell working directory:s:\n\
password 51:b:#pwd#\n\
disable wallpaper:i:1\n\
disable full window drag:i:1\n\
disable menu anims:i:1\n\
disable themes:i:0\n\
disable cursor setting:i:0\n\
bitmapcachepersistenable:i:1\
		");
	CMyString* strr=new CMyString;


	string str = s.GetBuffer(0);
	//替换密码
	str=strr->replace("#pwd#",enpwd,str);
	//替换ip
	str=strr->replace("#ip#",ip,str);
	//替换用户名
	str=strr->replace("#username#",username,str);
	//替换空白
	//str = strr->replace(" ", "", str);

	//生成rdp文件
	fio->write("tem.tmp",str);

	delete fio;

	//运行远程参数
	WinExec("mstsc.exe /console /f tem.tmp",SW_HIDE);



	return;
}

void CFrameWindowWnd::BtnAddClick(TNotifyUI& msg){
	pinputmsg=new CInputWnd;
	pinputmsg->Create( GetHWND(), _T("信息窗口"), UI_WNDSTYLE_DIALOG, UI_WNDSTYLE_EX_FRAME );
	pinputmsg->CenterWindow();
	pinputmsg->ShowModal();
	//注意下面这一句必须有可以把消息循环挂到新建的窗口上
	CPaintManagerUI::MessageLoop();
	initList();
	return;
}

void CFrameWindowWnd::BtnDelClick(TNotifyUI& msg){
	if (selectedItem->index==-1 || selectedItem->id=="")
	{
		::MessageBox(m_hWnd,"请选择一个服务器","提醒",NULL);
		return;
	}
	string id=selectedItem->id;
	string sql="delete * from list where id="+id;
	CDb *db=new CDb;
	if(db->ExecuteSql(CString(sql.c_str())))
	{
		::MessageBox(m_hWnd,"删除成功","提醒",NULL);
		initList();
	}else{
		::MessageBox(m_hWnd,"删除失败","提醒",NULL);
	}
	return;
}

void CFrameWindowWnd::BtnModClick(TNotifyUI& msg){
	return;
}

void CFrameWindowWnd::ItemSelectClick(TNotifyUI& msg){
	if(msg.pSender->GetName()=="iplist"){

		//保存当前选中项目信息
		CString idstr,ipstr,portstr,unamestr;
		idstr.Format("id%lu",msg.wParam);
		ipstr.Format("ip%lu",msg.wParam);
		portstr.Format("port%lu",msg.wParam);
		unamestr.Format("uname%lu",msg.wParam);



		CLabelUI * pidstr= static_cast<CLabelUI*>(m_pm.FindControl(idstr));
		CLabelUI * pipstr= static_cast<CLabelUI*>(m_pm.FindControl(ipstr));
		CLabelUI * pportstr= static_cast<CLabelUI*>(m_pm.FindControl(portstr));
		CLabelUI * punamestr= static_cast<CLabelUI*>(m_pm.FindControl(unamestr));
		LPCTSTR st=pidstr->GetText();
		selectedItem->id=string(st);
		st=pipstr->GetText();
		selectedItem->ip=string(st);
		st=pportstr->GetText();
		selectedItem->port=string(st);
		st=punamestr->GetText();
		selectedItem->uname=string(st);

		selectedItem->index=msg.wParam;

		CMyString* str1=new CMyString;
		CDb* db=new CDb;
		string str2=pidstr->GetText();//取当前数据id
		//取密码
		string pwd=db->getByfield("list",str2,"pwd").c_str();
		selectedItem->pwd=str1->deString(pwd.c_str(),"adminrootkl");
		//设置备注信息
		m_pNote->SetText(db->getByfield("list",str2,"note").c_str());


		//::MessageBox(m_hWnd,msg.pSender->GetName(),"提醒",NULL);

	}
}