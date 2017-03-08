#include "FileIO.h"


CFileIO::CFileIO(void)
{
}


CFileIO::~CFileIO(void)
{
}
bool CFileIO::write(string filename,string str){
	ofstream ofile(filename);
	if (ofile.good())
	{
		ofile.write(str.c_str(),str.length());
		ofile.close();
		return false;
	}else{
		return true;
	}
	
}
string CFileIO::readAll(string filename){
	string str = "";
	char tmp;
	ifstream ifile(filename);
	if (ifile.good())
	{
		while (ifile.get(tmp))
		{
			str += tmp;
		}
		return str;
	}else{
		return "";
	}
}
int CFileIO::del(string filename){
	if(remove(filename.c_str())){
		return 0;
	}else{
		return -1;
	}
}
