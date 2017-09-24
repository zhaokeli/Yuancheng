#include "MyString.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
CMyString::CMyString(string subject){
	this->subject=subject;
}

CMyString::CMyString(void)
{
}


CMyString::~CMyString(void)
{
}
string CMyString::replace(string search,string replace,string subject){
	if(subject=="")subject=this->subject;
	int start_pos=0,length=0;
	if (subject.find(search) != -1)
	{
		start_pos=subject.find(search);
		length=search.length();
		subject.replace(start_pos,length,replace);
		return subject;
	}else{
		return subject;
	}
}

string CMyString::enString(const char* src,const char* key)
{
	int KeyPos=-1;
	int SrcPos=0;
	int SrcAsc=0;
	time_t t;

	int KeyLen=strlen(key);
	if(KeyLen==0)return "";

	srand((unsigned)time(&t));
	int offset=rand()%255;

	char buff[3];
	sprintf(buff,"%1.2x",offset);
	string dest=buff;
	int a=strlen(src);
	for(int i=0;i<a;i++)
	{
		SrcAsc=(src[i]+offset)%255;
		if(KeyPos<KeyLen-1)
			KeyPos++;
		else
			KeyPos=0;

		SrcAsc=SrcAsc^key[KeyPos];

		memset(buff,0,sizeof(buff));
		sprintf(buff,"%1.2x",SrcAsc);
		dest=dest+(string)buff;
		offset=SrcAsc;
	}
	return dest;
}
string CMyString::deString(const char* src,const char* key)
{
	int KeyLen=strlen(key);
	if(KeyLen==0)
		return "";

	int KeyPos=-1;
	int offset=0;
	string dest="";
	int SrcPos=0;
	int SrcAsc=0;
	int TmpSrcAsc=0;

	char buff[5];
	sprintf(buff,"0x%s",substr(src,1,2));
	sscanf(buff,"%x",&offset);
	SrcPos=3;
	while (SrcPos<=strlen(src))
	{
		sprintf(buff,"0x%s",substr(src,SrcPos,2));
		sscanf(buff,"%x",&SrcAsc);
		if(KeyPos<KeyLen-1)
			KeyPos++;
		else
			KeyPos=0;

		TmpSrcAsc=SrcAsc^key[KeyPos];
		if(TmpSrcAsc<=offset)
			TmpSrcAsc=255+TmpSrcAsc-offset;
		else
			TmpSrcAsc=TmpSrcAsc-offset;
		dest+=char(TmpSrcAsc);
		offset=SrcAsc;
		SrcPos=SrcPos+2;
	}
	return dest;
}
char* CMyString::substr(const char* _str,int pos,int len){
	static char ptr[10];
	memcpy(ptr,_str+pos-1,len);
	ptr[len]='\0';
	return ptr;
}

//CString CMyString::Encryptt(CString S, WORD Key){
//	CString Result,str;
//	int i,j;
//
//	Result=S; // 初始化结果字符串
//	for(i=0; i<S.GetLength(); i++) // 依次对字符串中各字符进行操作
//	{
//		Result.SetAt(i, S.GetAt(i)^(Key>>8)); // 将密钥移位后与字符异或
//		Key = ((BYTE)Result.GetAt(i)+Key)*C1+C2; // 产生下一个密钥
//	}
//	S=Result; // 保存结果
//	Result.Empty(); // 清除结果
//	for(i=0; i<S.GetLength(); i++) // 对加密结果进行转换
//	{
//		j=(BYTE)S.GetAt(i); // 提取字符
//		// 将字符转换为两个字母保存
//		str="12"; // 设置str长度为2
//		str.SetAt(0, 65+j/26);//这里将65改大点的数例如256，密文就会变乱码，效果更好，相应的，解密处要改为相同的数
//		str.SetAt(1, 65+j%26);
//		Result += str;
//	}
//	return Result;
//}

//CString CMyString::Decryptt(CString S, WORD Key){
//	CString Result,str;
//	int i,j;
//
//	Result.Empty(); // 清除结果
//	for(i=0; i < S.GetLength()/2; i++) // 将字符串两个字母一组进行处理
//	{
//		 j = ((BYTE)S.GetAt(2*i)-65)*26;);//相应的，解密处要改为相同的数
//
//		j += (BYTE)S.GetAt(2*i+1)-65;
//		str="1"; // 设置str长度为1
//		str.SetAt(0, j);
//		Result+=str; // 追加字符，还原字符串
//	}
//	S=Result; // 保存中间结果
//	for(i=0; i<S.GetLength(); i++) // 依次对字符串中各字符进行操作
//	{
//		Result.SetAt(i, (BYTE)S.GetAt(i)^(Key>>8)); // 将密钥移位后与字符异或
//		Key = ((BYTE)S.GetAt(i)+Key)*C1+C2; // 产生下一个密钥
//	}
//	return Result;
//}