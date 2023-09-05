#pragma once
#include <Windows.h>
#include <tchar.h>

#include "Logger.h"


class HOOKW32
{
public:
	Logger logger; // 创建一个Logger对象作为成员变量
public:
	HOOKW32(TCHAR *className, TCHAR* titleName);
	~HOOKW32();
private:
	BOOL m_bInit;//是否初始化
	TCHAR m_className[126];
	TCHAR m_titleName[126];
	DWORD m_pid;// GetWindowThreadProcessId
	HWND m_hwnd;//窗口句柄  FindWindow
	HANDLE m_handle;//进程句柄  OpenProcess
public:

	/************************************
	* 方法名:    findProcess
	* 描 述 : 
	* 返回值:   BOOL
	* 创建人: Simple
	* 创建时间  : 2023年9月5日
	************************************/
	BOOL findProcess();
	
	
	/************************************
	* 方法名:    readMemory
	* 描 述 :读内存
	* 入 参 : LPVOID adress  指向要读取的内存地址
	* 入 参 : LPVOID buffer	 指向从指定进程的地址空间接收内容的缓冲区的指针。
	* 入 参 : DWORD readSize 要从指定进程读取的字节数。
	* 入 参 : DWORD returnSize 指向变量的指针，该变量接收传输到指定缓冲区的字节数
	* 入 参 : BOOL bRe
	* 返回值:   BOOL
	* 创建人: Simple
	* 创建时间  : 2023年9月5日
	************************************/
	BOOL readMemory(LPVOID adress,LPVOID buffer,DWORD readSize,DWORD* returnSize,BOOL bRe=FALSE);//


	/************************************
	* 方法名:    writeMemory
	* 描 述 :写内存
	* 入 参 : LPVOID adress 地址
	* 入 参 : LPVOID buffer 缓冲区
	* 入 参 : DWORD readSize 读大小
	* 入 参 : DWORD returnSize 返回读大小
	* 入 参 : BOOL bRe
	* 返回值:   BOOL
	* 创建人: Simple
	* 创建时间  : 2023年9月5日
	************************************/
	BOOL writeMemory(LPVOID adress, LPVOID buffer, DWORD readSize, DWORD* returnSize, BOOL bRe = FALSE);//
	
	

	/************************************
	* 方法名:    memoryProtect
	* 描 述 : 更改内存页面属性
	* 入 参 : LPVOID adress  指向要更改其访问保护属性的页区域的基址的指针。
	* 入 参 : DWORD size 访问保护属性已更改的区域的大小（以字节为单位
	* 入 参 : DWORD newFlAllocationType 新的页面属性
	* 入 参 : DWORD oldFlAllocationType 旧的页面属性
	* 返回值:   BOOL
	* 创建人: Simple
	* 创建时间  : 2023年9月5日
	************************************/
	BOOL memoryProtect(LPVOID adress, DWORD size, DWORD  newFlAllocationType, DWORD*  oldFlAllocationType, BOOL bRe = FALSE);

	/************************************
	* 方法名:    allocMemory
	* 描 述 : 分配内存
	* 入 参 : DWORD size 分配大小
	* 入 参 : BOOL bRe
	* 返回值:   LPVOID
	* 创建人: Simple
	* 创建时间  : 2023年9月5日
	************************************/
	LPVOID allocMemory(DWORD size, BOOL bRe = FALSE);

	/************************************
	* 方法名:    freeMemory
	* 描 述 : 释放内存
	* 入 参 : LPVOID adress 释放内存地址指针
	* 入 参 : DWORD size 释放内存大小
	* 入 参 : BOOL bRe 
	* 返回值:   BOOL
	* 创建人: Simple
	* 创建时间  : 2023年9月5日
	************************************/
	BOOL freeMemory(LPVOID adress, DWORD size, BOOL bRe = FALSE);


	BOOL InjeceDLL(TCHAR* fileName, BOOL bRe = FALSE);//远线程注入DLL

};	


