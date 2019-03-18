#include <stdio.h>
#include <windows.h>  //Sleep函数声明在这里面
#include "itmojun.h"  //包含当前工程目录下的itmojun.h头文件

//引入当前工程目录下的itmojun.lib和系统库文件目录下的winmm.lib这两个库文件，因为我们要调用它们里面的一些函数
#pragma comment(lib, "itmojun.lib")  //AutoRun和GetPCCmd函数
#pragma comment(lib, "winmm.lib")	 //mciSendString函数


char g_caption[501];
char g_title[501];


DWORD WINAPI MsgBoxThr(LPVOID lpParam);


int main()
{
	char cmd[301];  //存放从微信端接收的消息

	AutoRun();  //将当前程序设置为开机自动运行

	while(1)
	{
		//GetPCCmd函数的功能：从微信端接收一条消息，如果没有任何消息，它会一直等待
		//第一个参数为电脑ID，不同电脑建议使用不同的ID
		//第二个参数为接收消息的数组
		GetPCCmd("dj", cmd);

		printf("%s\n", cmd);

		//strstr函数的功能：在一个字符串中查找子字符串，如果找到则返回其指针，否则返回NULL
		if(strstr(cmd, "关机"))
		{
			//关机
			//WinExec("shutdown -s -t 0", 0);
		}
		else if(strstr(cmd, "重启"))
		{
			//重启
			//WinExec("shutdown -r -t 0", 0);
		}
		else if(strstr(cmd, "桌面"))
		{
			static int kill_flag = 1;

			if(kill_flag)
				//干掉桌面
				WinExec("taskkill /f /im explorer.exe", 0);
			else
				//恢复桌面
				WinExec("C:\\Windows\\explorer.exe", 1);

			kill_flag = !kill_flag;
		}
		else if(strstr(cmd, "杀企鹅"))
		{
			//强制结束QQ
			WinExec("taskkill /f /im qq.exe", 0);
		}		
		else if(strstr(cmd, "亚索"))
		{
			//强制结束英雄联盟
			WinExec("taskkill /f /im client.exe", 0);
		}		
		else if(strstr(cmd, "广告"))
		{
			//强制打开广告页面
			WinExec("explorer https://itmojun.com", 1);
		}	
		else if(strstr(cmd, "记事本"))
		{
			//打开记事本
			WinExec("notepad", 1);
		}
		else if(strstr(cmd, "播放"))
		{
			//播放背景音乐
			mciSendString("open bg.mp3 alias s", NULL, 0, NULL);  //打开指定音乐文件并指定其别名为s
			mciSendString("play s repeat", NULL, 0, NULL);  //重复播放s
		}
		else if(strstr(cmd, "暂停"))
		{
			//暂停背景音乐
			mciSendString("pause s", NULL, 0, NULL);  //暂停播放s
		}
		else if(strstr(cmd, "停止"))
		{
			//停止背景音乐
			mciSendString("close s", NULL, 0, NULL);  //停止播放s
		}
		//strncmp函数的功能：比较两个字符串开头的若干个字符是否相等
		//strlen函数的功能：获取字符串的长度
		else if(strncmp(cmd, "提示", strlen("提示")) == 0)
		{
			char* caption = NULL;
			char* title = NULL;

			//strtok函数的功能：切割字符串

			//cmd：提示#你好#tips
			strtok(cmd, "#");
			caption = strtok(NULL, "#");
			title = strtok(NULL, "#");

			if(caption == NULL)
				strcpy(g_caption, "");
			else
				strcpy(g_caption, caption);

			if(title == NULL)
				strcpy(g_title, "");
			else
				strcpy(g_title, title);

			//CreateThread系统函数的功能：创建一个新线程
			CreateThread(NULL, 0, MsgBoxThr, NULL, 0, NULL);
		}


		Sleep(3000);  //延时3秒，避免接收到重复的消息，因为消息会在服务器上暂存3秒
	}

	return 0;
}


//定义线程函数
DWORD WINAPI MsgBoxThr(LPVOID lpParam)
{
	//MessageBox系统函数的功能：弹出消息框窗口
	MessageBox(NULL, g_caption, g_title, 0);

	return 0;
}