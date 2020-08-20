#include "XFtpFactory.h"
#include "XFtpServerCMD.h"
#include "XFtpUSER.h"
#include "XFtpLIST.h"
#include "XFtpPORT.h"
#include "XFtpRETR.h"
#include "XFtpSTOR.h"
#include "XFtpDELE.h"
XTask *XFtpFactory::CreateTask()
{
	XFtpServerCMD *x = new XFtpServerCMD(); //��ʱ���٣�

	//ע��ftp��Ϣ��������
	x->Reg("USER", new XFtpUSER());
	XFtpLIST * list = new XFtpLIST();
	x->Reg("PWD", list);
	x->Reg("LIST", list);
	x->Reg("CWD", list);
	x->Reg("CDUP", list);
	x->Reg("PORT", new XFtpPORT());
	x->Reg("RETR", new XFtpRETR());
	x->Reg("STOR", new XFtpSTOR());
	x->Reg("DELE", new XFtpDELE());
	
	return x;
}

XFtpFactory::XFtpFactory()
{
}

