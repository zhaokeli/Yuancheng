//#include <windows.h> 

//#include <objbase.h>
//#include <string.h>
//#include "KLinet.h"
//#include "Db.h"
//#include "FrameWindowWnd.h"
#ifndef   _STDAFX_H_
#define   _STDAFX_H_
#ifndef   _WIN32_WINNT 
#define   _WIN32_WINNT   0x0501
#endif 
#ifndef _STDAFX_H
#define _STDAFX_H
#pragma warning(disable : 4996)
#include <stdio.h> 
#include <afx.h>
#include <fstream>
#include <iostream>
#include <string>

#include "MyLog.h"
#include "FileIO.h"
#include "MyString.h"
#include "wincrypt.h"
#include "lock.h"
#include "../DuiLib/UIlib.h" 
#ifdef _DEBUG
#pragma comment(lib, "DuiLib_d.lib") 
#else
#pragma comment(lib, "DuiLib.lib") 
#endif
using namespace DuiLib;


#pragma comment(lib,"c:\\Windows\\System32\\crypt32.dll")
#endif
#pragma comment(lib,"Crypt32.lib")

using namespace std;

#endif 