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
	HOOKW32 hook("Direct3DWindowClass", NULL);
	hook.InjeceDLL("E:\\VS项目\\MFC01\\Debug\\FindCode特征码x32.dll");
	return 0;
}


