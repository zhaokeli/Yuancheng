#pragma once
#ifndef  _LISTIP_H_ 
#define  _LISTIP_H_
#include "../DuiLib/UIlib.h" 
#ifdef _DEBUG
#pragma comment(lib, "DuiLib.lib") 
#else
#pragma comment(lib, "DuiLib.lib") 
#endif
using namespace DuiLib;


struct ServerInfo
{
	string id,ip,port,uname,pwd;
	int index;

};

class CListIp:public CListUIEx
{
private:
	
public:
	CListIp();
    ~CListIp();
};

#endif // ! _SERVERINFO_STRCUT_