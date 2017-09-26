#pragma once 
#include "FrameWindowWnd.h"
#include "resource.h"
#include "DES.h"
// 程序入口及Duilib初始化部分
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
	//测试des加密
	puts("Testing RunDES......");
	string s = CDES::EnCode("735579768", "735579768");
	string ds = CDES::DeCode("A7D7BBCEAFEDADF875E51F0CF10F13EAB08928FB52C77E63365DF0E3DCE1154BAB31E03802C93A9D9806ED0B9111DEAEC416E126AAC6718238737F593932DE9002580D168AF5AEECEE8FCEC87FEE9266E4E1B377AB122A1A8E9F2470A035F69B82DCF88C239C3F02AD7E2C34E7552D8A737BA22CBFA39046E981EC9091AEE8AF330AB7F641896C97B74ED9857BC4DB2466B19DB1C78C0FBB8B65E9CF246EE6E6EA9240ECF2E4C831965A80D6727F4841D314977B959A2D20770D1FAAEC0040E2AA09ABEF715812AF", "735579768");
	//string str = "735579768";
	//string iv = "735579768";
	//string key = "735579768";
	//char Out[1024] = { 0 };
	//char Key[8] = { 0 };
	//memcpy(Key, _ConstValue, 8);
	//char IV[8] = { 0 };
	//memcpy(IV, _ConstValue, 8);
	//puts("please input your words");
	//gets(In);

	//// 对str进行DES加密，CBC + PKCS7模式  
	//memset(Out, 0x00, 1024);
	//CDES::RunDES(CDES::ENCRYPT, CDES::CBC, CDES::PAD_PKCS_7, (const unsigned char*)iv.c_str(), (const unsigned char*)str.c_str(), (unsigned char*)Out, strlen(str.c_str()), (const unsigned char*)key.c_str(), strlen(key.c_str()));
	//puts("after encrypting:");
	//puts(Out);
	////转成十六进制
	////char hexs[1024] = { 0 };
	//string hexs=CDES::Bits2Hex(Out, strlen(Out));
	//// 将加密后的strout进行Base64编码  
	//char* Base64Out = TBase64::Base64_Encode(Out);
	//printf("Base64编码之后，您的文件经过DES加密后的密文是：\n");
	//printf("%s\n", Base64Out);

	////解密
	//string enstr = "A7D7BBCEAFEDADF875E51F0CF10F13EAB08928FB52C77E63365DF0E3DCE1154BAB31E03802C93A9D9806ED0B9111DEAEC416E126AAC6718238737F593932DE9002580D168AF5AEECEE8FCEC87FEE9266E4E1B377AB122A1A8E9F2470A035F69B82DCF88C239C3F02AD7E2C34E7552D8A737BA22CBFA39046E981EC9091AEE8AF330AB7F641896C97B74ED9857BC4DB2466B19DB1C78C0FBB8B65E9CF246EE6E6EA9240ECF2E4C831965A80D6727F4841D314977B959A2D20770D1FAAEC0040E2AA09ABEF715812AF";
	//char* estr = CDES::Hex2Bits(enstr);
	//CDES::RunDES(CDES::DECRYPT,CDES::CBC,CDES::PAD_PKCS_7, (const unsigned char*)iv.c_str(), (const unsigned char*)estr, (unsigned char*)Out, strlen(enstr.c_str()), (const unsigned char*)key.c_str(), strlen(key.c_str()));
	//string mstr = Out;
	//int nwLen = MultiByteToWideChar(CP_UTF8, 0, mstr.c_str(), -1, NULL, 0);//算出合适的长度
	//LPWSTR strUnicode = new WCHAR[nwLen];
	//MultiByteToWideChar(CP_UTF8, 0, mstr.c_str(), -1, strUnicode, nwLen);//ASCII转UNICODE

	//int nLen = WideCharToMultiByte(CP_ACP, 0, strUnicode, -1, NULL, 0, "", false);//算出合适的长度
	//char *strAscii = new char[nLen];
	//WideCharToMultiByte(CP_ACP, 0, strUnicode, -1, strAscii, nLen, "", false);//UNICODE转ASCII

	//// 对Base64编码的pEncodeStr进行解码  
	//char* ByteIn = TBase64::Base64_Decode(Base64Out);
	//printf("Base64解码之后的明文是：\n");
	//puts(ByteIn);

	//// 用Base64解码后的pDecodeStr进行DES解密，CBC + PKCS7模式  
	//memset(In, 0x00, 1024);
	//CDES::RunDES(CDES::DECRYPT, CDES::CBC, CDES::PAD_PKCS_7, IV, ByteIn, In, strlen(ByteIn), Key, strlen(Key));
	//printf("Base64解码之后，您的文件经过DES解密后的明文是：\n");
	//puts(In);

	//// 用未经编码的strout直接DES解密，CBC + PKCS7模式  
	//puts("after decrypting:");
	//memset(In, 0x00, 1024);
	//CDES::RunDES(CDES::DECRYPT, CDES::CBC, CDES::PAD_PKCS_7, IV, Out, In, strlen(Out), Key, strlen(Key));
	//puts(In);

	//delete[]Base64Out; Base64Out = NULL;
	//delete[]ByteIn; ByteIn = NULL;



















	//创建命名信标对象。 
	HANDLE hSem = CreateSemaphore(NULL, 1, 1, "重复运行标记");
	if (hSem) //信标对象创建成功。 
	{
		//信标对象已经存在，则程序已有一个实例在运行。 
		if (ERROR_ALREADY_EXISTS == GetLastError())
		{
			CloseHandle(hSem); //关闭信号量句柄。 

			//获取桌面窗口的一个子窗口。 
			HWND hWndPrev = ::GetWindow(::GetDesktopWindow(), GW_CHILD);

			while (::IsWindow(hWndPrev))
			{
				//判断窗口是否有我们预先设置的标记，如有，则是我们寻找的窗口，并将它激活。 
				if (::GetProp(hWndPrev, "重复运行标记"))
				{
					//如果主窗口已最小化，则恢复其大小。 
					if (::IsIconic(hWndPrev))
						::ShowWindow(hWndPrev, SW_RESTORE);

					//将应用程序的主窗口激活。 
					::SetForegroundWindow(hWndPrev);
					return FALSE; //退出实例。
				}
				//继续寻找下一个窗口。 
				hWndPrev = ::GetWindow(hWndPrev, GW_HWNDNEXT);
			}
		}
	}

	//初始化一个窗口
	CWndShadow::Initialize(hInstance);

	CPaintManagerUI::SetInstance(hInstance);
	//CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T(".//skin"));
	//使用zip包加载皮肤
	//CPaintManagerUI::SetResourceZip(CPaintManagerUI::GetInstancePath()+_T("skin.zip"));

	HRESULT Hr = ::CoInitialize(NULL);
	if (FAILED(Hr))
		return 0;
	CFrameWindowWnd* pFrame = new CFrameWindowWnd();
	if (pFrame == NULL) return 0;
	//pFrame->Create(NULL, _T("测试"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);//窗口可最大化
	pFrame->Create(NULL, _T("RemoteDestop"), UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE);//窗口不可最大化
	//LONG styleValue = ::GetWindowLong(*pFrame, GWL_STYLE);
	//styleValue &= ~WS_CAPTION;
	//::SetWindowLong(*pFrame, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

	//pFrame->ShowWindow(true);
	pFrame->CenterWindow();
	pFrame->ShowModal();
	CPaintManagerUI::MessageLoop();
	::CoUninitialize();
	return 0;
}


