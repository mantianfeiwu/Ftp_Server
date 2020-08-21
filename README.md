# 基于Libevent的简易C++多线程Ftp服务器
环境:Libevent2.1.8
已经实现的主要功能: 1.上传文件。 2.下载文件。  3.删除文件
大致流程：1.创建线程池（大小为10），初始化线程，并启动   2.监听到socket事件后，发生激活消息给线程，开始任务分发   3.线程执行任务   
## 程序框架
![image](https://github.com/mantianfeiwu/Ftp_Server/blob/master/Ftp_Server.png)

## 服务器测试
![image](https://github.com/mantianfeiwu/Ftp_Server/blob/master/test.gif)
