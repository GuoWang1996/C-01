// c++05.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#pragma once
#include <iostream>
#include "HOOKW32.h"
#include "string"
using namespace std;
#define ADRESS 0x00ED0000

/************************************
* 描 述 : 测试
* 入 参 :
* 返回值:
* 创建人: Simple
* 创建时间  : 2023年9月5日
************************************/
int main() {
	HOOKW32 hook("DIRECT3DWINDOWCLASS", NULL);
	if (hook.findProcess())
	{
		//申请内存
		char* adress=(char*)hook.allocMemory(200);
		if (!adress)
		{
			hook.logger.Log("分配内存失败");
			return -1;
		}
		//1.读取内存处数据
		char buffer[256] = { 0 };
		hook.readMemory((LPVOID)adress, buffer, 20, NULL);
		hook.logger.Log(buffer);
		std::cout << "更改属性：";
		DWORD old;

		//2.更改内存保护属性
		hook.memoryProtect((LPVOID)adress, 256, PAGE_EXECUTE_READWRITE, &old);
		std::cout << "请输入属性：";
		char buffer2[256] = { 0 };
		std::cin >> buffer2; // 将用户输入存储到input变量中
		
		//3.对内存写入
		if (!hook.writeMemory((LPVOID)adress, buffer2, strlen(buffer2), NULL))
		{
			hook.logger.Log("写入失败");
		}

		//4.还原内存属性
		hook.memoryProtect((LPVOID)adress, 256, PAGE_READONLY, &old);

		//5.再次读取内存处数据
		hook.readMemory((LPVOID)adress, buffer2, 20, NULL);


		//6.释放内存
		if (hook.freeMemory(adress, 200))
		{
			hook.logger.Log("释放内存成功");

		}
	}
	else {
		hook.logger.Log("findProcess失败");
	}
	return 0;
}


