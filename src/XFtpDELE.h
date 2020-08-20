#pragma once
#include "XFtpTask.h"
class XFtpDELE : public XFtpTask
{
public:
	//Ω‚Œˆ–≠“È
	virtual void Parse(std::string type, std::string msg);
	XFtpDELE();
	~XFtpDELE();
};

