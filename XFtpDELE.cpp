#include "XFtpDELE.h"
#include <iostream>
using namespace std;
//����Э��
void XFtpDELE::Parse(std::string type, std::string msg)
{
	//�ļ��� S 123.txt
	int pos = msg.rfind(" ") + 1;
	string filename = msg.substr(pos, msg.size() - pos - 2);
	string path = cmdTask->rootDir;
	path += cmdTask->curDir;
	path += filename;
    remove(path.c_str());   
	ResCMD("200 File OK\r\n");
}


XFtpDELE::XFtpDELE()
{
}


XFtpDELE::~XFtpDELE()
{
}
