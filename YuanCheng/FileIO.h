#pragma once
#include <fstream>
#include <iostream>
#include <string.h>
using namespace std;
class CFileIO
{
public:
	CFileIO(void);
	~CFileIO(void);
	bool write(string filename,string str);
	string readAll(string filename);
	int del(string filename);
};

