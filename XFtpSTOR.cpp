#include "XFtpSTOR.h"
#include <iostream>
#include <event2/bufferevent.h>
#include <event2/event.h>
using namespace std;

//上传文件
//解析协议 
void XFtpSTOR::Parse(std::string type, std::string msg)
{
	//文件名 STOR 123.txt
	int pos = msg.rfind(" ") + 1;
	string filename = msg.substr(pos, msg.size() - pos - 2);
	string path = cmdTask->rootDir;
	path += cmdTask->curDir;
	path += filename;
	fp = fopen(path.c_str(), "wb");  //从bufferevent读取文件，写入fp
	if (fp)
	{
		//1.连接数据通道
		ConnectPORT();

		//2.发送开始接收文件的指令
		ResCMD("125 File OK\r\n");
		//3.触发读取事件
		bufferevent_trigger(bev, EV_READ, 0);
	}
	else
	{
		ResCMD("450 file open failed!\r\n");
	}
}
void XFtpSTOR::Read(struct bufferevent *bev)
{
	if (!fp)return;
	for (;;)
	{
		int len = bufferevent_read(bev, buf, sizeof(buf));
		if (len <= 0)
			return;
		int size = fwrite(buf, 1, len, fp);
		cout << "<"<<len<<":"<<size << ">" << flush;
	}
}
void XFtpSTOR::Event(struct bufferevent *bev, short what)
{
	//如果对方网络断掉，或者机器死机有可能收不到BEV_EVENT_EOF数据
	if (what & (BEV_EVENT_EOF | BEV_EVENT_ERROR | BEV_EVENT_TIMEOUT))
	{
		cout << "XFtpSTOR BEV_EVENT_EOF | BEV_EVENT_ERROR |BEV_EVENT_TIMEOUT" << endl;
		if (fp)
		{
			fclose(fp);
			fp = 0;
		}
		Close();
		ResCMD("226 Transfer complete\r\n");
	}
	else if (what&BEV_EVENT_CONNECTED)
	{
		cout << "XFtpSTOR BEV_EVENT_CONNECTED" << endl;
	}
}