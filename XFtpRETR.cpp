 
#include "XFtpRETR.h"
#include <iostream>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <string>
using namespace std;

void XFtpRETR::Write(struct bufferevent *bev)
{
	if (!fp)return;
	int len = fread(buf, 1, sizeof(buf), fp);
	if (len <= 0)
	{
		fclose(fp);
		fp = 0;
		ResCMD("226 Transfer complete\r\n");
		Close();
		return;
	}

	cout << "[" << len << "]" << flush;
	Send(buf, len);
}

void XFtpRETR::Event(struct bufferevent *bev, short what)
{
	//����Է�����ϵ������߻��������п����ղ���BEV_EVENT_EOF����
	if (what & (BEV_EVENT_EOF | BEV_EVENT_ERROR | BEV_EVENT_TIMEOUT))
	{
		cout << "BEV_EVENT_EOF | BEV_EVENT_ERROR |BEV_EVENT_TIMEOUT" << endl;
		Close();
		if (fp)
		{
			fclose(fp);
			fp = 0;
		}
	}
	else if (what&BEV_EVENT_CONNECTED)
	{
		cout << "XFtpRETR BEV_EVENT_CONNECTED" << endl;
	}
}
//����Э��
void XFtpRETR::Parse(std::string type, std::string msg)
{
	//�ļ��� RETR 123.txt
	int pos = msg.rfind(" ") + 1;
	string filename = msg.substr(pos, msg.size() - pos - 2);
	string path = cmdTask->rootDir;
	path += cmdTask->curDir;
	path += filename;
	fp = fopen(path.c_str(), "rb");  //��ȡ�������ļ�
	if (fp)
	{
		//1.��������ͨ��
		ConnectPORT();
		
		//2.���Ϳ�ʼ�����ļ���ָ��
		ResCMD("150 File OK\r\n");

		//3.����д���¼�
		bufferevent_trigger(bev, EV_WRITE, 0);
	}
	else
	{
		ResCMD("450 file open failed!\r\n");
	}
}