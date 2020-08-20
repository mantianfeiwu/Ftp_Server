 
#pragma once
#include "XFtpTask.h"
class XFtpRETR :
	public XFtpTask
{
public:
	//Ω‚Œˆ–≠“È
	virtual void Parse(std::string type, std::string msg);
	virtual void Write(struct bufferevent *bev);
	virtual void Event(struct bufferevent *bev, short what);
private:
	char buf[1024] = { 0 };
	FILE * fp = 0;
};

